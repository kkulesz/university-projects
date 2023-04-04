# csv info here
GROUP = 'tbd-2022z-8'
SPARK_EXECUTORS = 8

CLUSTER = "dataproc"

LR_MODEL = "LR"
GBT_MODEL = 'GBT'

SPARK_ML_LIBRARY = "spark-ml"
H20_LIBRARY = 'h20'
SYNAPSE_LIBRARY = 'synapse-ml'

###############################
import pyspark
spark = pyspark.sql.SparkSession.builder.appName("tbd") \
    .master(f"local[{SPARK_EXECUTORS}]") \
    .config("spark.jars.packages", "com.microsoft.azure:synapseml_2.12:0.9.5") \
    .config("spark.jars.repositories", "https://mmlspark.azureedge.net/maven") \
    .config("spark.executor.cores", SPARK_EXECUTORS) \
    .getOrCreate()



###############################
# all other imports in one place so we dont miss anything
from pyspark.sql.functions import col, lit, explode, array
from pyspark.ml.feature import StringIndexer, OneHotEncoder, VectorAssembler
from pyspark.ml.feature import UnivariateFeatureSelector
from pyspark.ml import Pipeline
from pyspark.ml.classification import LogisticRegression

import time
import os.path as path

###############################
# reading data
raw_df = spark.read.csv(
    "gs://${staging_bucket}/data/ml/input/ds2-1e6.csv", 
    inferSchema="True", header="true", nullValue='NA', nanValue='NA',emptyValue='NA'
    )
df = raw_df.withColumn("label", raw_df.label.cast("float"))

###############################
# defining pipeline
categorical_columns = [
    "Light_Conditions", "Weather_Conditions", 
    "Urban_or_Rural_Area", "Carriageway_Hazards", "Did_Police_Officer_Attend_Scene_of_Accident", 
    "Road_Surface_Conditions", "Road_Type", "Special_Conditions_at_Site"
]
ordinal_columns = ["Speed_limit"] # quantative?
quantative_columns = ["Police_Force", "Number_of_Vehicles", "Number_of_Casualties"]
y_column = "label"

stringindexer_stages = [StringIndexer(inputCol=c, outputCol='stringindexed_' + c).setHandleInvalid("keep") for c in categorical_columns]
onehotencoder_stages = [OneHotEncoder(inputCol='stringindexed_' + c, outputCol='onehot_' + c) for c in categorical_columns]

extracted_columns = ['onehot_' + c for c in categorical_columns]
extracted_columns += ordinal_columns
extracted_columns += quantative_columns

selector=UnivariateFeatureSelector(featuresCol="features", outputCol="selectedFeatures", labelCol= "label")
selector=selector.setFeatureType("continuous").setLabelType("continuous")

final_columns = extracted_columns + ['features', 'label']  + ["selectedFeatures"]
vectorassembler_stage = VectorAssembler(inputCols=extracted_columns, outputCol='features') 

ready_df = Pipeline(
    stages=stringindexer_stages + \
    onehotencoder_stages + \
    [vectorassembler_stage] + \
    [selector]
).fit(df).transform(df).select(final_columns)
###############################

def lr_spark_ml(r_df):
    from pyspark.ml.classification import LogisticRegression
    lr = LogisticRegression(featuresCol='selectedFeatures', labelCol='label')
    simple_model = Pipeline(stages=[lr])

    start_time = time.time()
    _ = simple_model.fit(r_df)
    return time.time() - start_time

def lr_h20(r_df):
    from pysparkling import H2OContext
    import h2o
    hc = H2OContext.getOrCreate()

    from pysparkling.ml import H2OGLM
    from pyspark.ml import Pipeline, Transformer
    from pyspark.sql import DataFrame
    from pyspark.sql.functions import udf, round
    from pyspark.sql.types import ArrayType, DoubleType

    h2o_lr = H2OGLM(
        family="binomial",
        featuresCols=['selectedFeatures'],
        labelCol='label',
        computePValues=True,
        removeCollinearCols=True, # te parametry też nie zmieniają wyniku niestety - przy badaniu wydajności mogą trochę spowalniać więc można False dać
        balanceClasses=False, # wbudowane balansowanie klas też nic nie poprawia
        lambdaValue=[0]
        )    
    make_raw_prediction = udf(lambda col1: col1[-1][-1], DoubleType())
    class H2OResultTransformer(Transformer):
        def _transform(self, df: DataFrame) -> DataFrame:
            new_df = df.withColumn('rawPrediction', make_raw_prediction(df.detailed_prediction))
            new_df=new_df.withColumn("prediction", round(df.prediction))
            return new_df
    h2o_result_transformer = H2OResultTransformer()
    h2o_model = Pipeline(stages=[h2o_lr, h2o_result_transformer])

    start_time = time.time()
    _ = h2o_model.fit(r_df)
    return time.time() - start_time

def xgb_spark_ml(r_df):
    from pyspark.mllib.tree import GradientBoostedTrees
    categoricalFeaturesInfo = {}

    for idx, column in enumerate(categorical_columns):
        num_of_values = raw_df.select(column).distinct().count()
        categoricalFeaturesInfo[idx] = num_of_values

    from pyspark.mllib.regression import LabeledPoint
    from pyspark.sql.functions import col

    from pyspark.mllib import linalg as mllib_linalg
    from pyspark.ml import linalg as ml_linalg

    def as_old(v):
        if isinstance(v, ml_linalg.SparseVector):
            return mllib_linalg.SparseVector(v.size, v.indices, v.values)
        if isinstance(v, ml_linalg.DenseVector):
            return mllib_linalg.DenseVector(v.values)
        raise ValueError("Unsupported type {0}".format(type(v)))

    labeledPoints = \
        (r_df.select(col("label"), col("selectedFeatures"))
        .rdd
        .map(lambda row: LabeledPoint(row.label, as_old(row.selectedFeatures))))

    start_time = time.time()
    _ = GradientBoostedTrees.trainClassifier(
        labeledPoints, 
        categoricalFeaturesInfo=categoricalFeaturesInfo,
        numIterations=20
    )
    return time.time() - start_time
    
def xgb_h20(r_df):
    from pysparkling import H2OContext
    import h2o
    hc = H2OContext.getOrCreate()
    from pysparkling.ml import H2OXGBoostClassifier # H2OXGBoost
    xgb_h20_model = H2OXGBoostClassifier(labelCol = "label")

    start_time = time.time()
    _ = xgb_h20_model.fit(r_df)
    return time.time() - start_time

def xgb_synapse(r_df):
    from pyspark.ml.linalg import VectorUDT
    from pyspark.sql.functions import udf
    dummy_udf = udf(lambda z: z ,VectorUDT()) 
    synapse_ml_df = r_df.withColumn("selectedFeatures", dummy_udf(col("selectedFeatures")))
    from synapse.ml.lightgbm import LightGBMClassifier

    xgb_synapse_model = LightGBMClassifier(
        objective="binary", 
        featuresCol="selectedFeatures", 
        labelCol="label", 
        isUnbalance=True,
    )

    start_time = time.time()
    _ = xgb_synapse_model.fit(synapse_ml_df)
    return time.time() - start_time

###############################
def run_exp(model_func, r_df, model_type, library, dataframe):
    its_time = model_func(r_df)
    new_row = spark.createDataFrame(
        [(GROUP, CLUSTER, model_type, library, SPARK_EXECUTORS, its_time)], 
        schema)
    res = dataframe.union(new_row)
    res.show()
    return res

from pyspark.sql.types import StructType, StringType, StructField, IntegerType, FloatType
schema = StructType(
    [
        StructField('group', StringType(), True), 
        StructField('cluster', StringType(), True), 
        StructField('model', StringType(), True), 
        StructField('library', StringType(), True), 
        StructField('spark-executors', IntegerType(), True), 
        StructField('elapsed-time', FloatType(), True)
    ]
    )
results_df = spark.createDataFrame(data=[], schema=schema)
try:
    for _ in [0, 1, 2]:
        results_df = run_exp(lr_spark_ml,   ready_df, LR_MODEL,     SPARK_ML_LIBRARY,   results_df)
        results_df = run_exp(lr_h20,        ready_df, LR_MODEL,     H20_LIBRARY,        results_df)
        results_df = run_exp(xgb_spark_ml,  ready_df, GBT_MODEL,    SPARK_ML_LIBRARY,   results_df)
        results_df = run_exp(xgb_h20,       ready_df, GBT_MODEL,    H20_LIBRARY,        results_df)
        results_df = run_exp(xgb_synapse,   ready_df, GBT_MODEL,    SYNAPSE_LIBRARY,    results_df)

except Exception as e:
    print(e)
    raise e



###############################
# save result

output_file = "gs://${staging_bucket}/data/ml/output/results.csv"

results_df.coalesce(1).write.format("csv").mode("overwrite").option("header", True).save(output_file)

spark.stop()

import logging
from pyspark.sql import SparkSession
from pyspark.sql.functions import count
spark = SparkSession.builder.appName("GCSFilesReader").getOrCreate()
df=spark.read.csv("gs://${staging_bucket}/data/input.csv", header=False)
logger = logging.getLogger('driver_logger')
logger.info(f"===>Row count: {df.count()}")
df.select(count("*")).withColumnRenamed("count(*)","cnt").write.format("csv") \
.mode('overwrite').options(header="true").save("gs://${staging_bucket}/data/output-${service_sufix}.csv")
spark.stop()

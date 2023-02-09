import pandas as pd
from simpletransformers.classification import ClassificationModel

from models.abstract_classifier import TextBinaryClassifier


class BertWrapper(TextBinaryClassifier):
    def __init__(self, model: ClassificationModel):
        self.model: ClassificationModel = model

    def train(self, data):
        self.model.train_model(
            train_df=data,
            show_running_loss=False
        )

    def eval(self, data):
        return self.model.eval_model(data)

    def predict(self, inputs):
        predictions, raw_outputs = self.model.predict(inputs)
        return list(predictions)

    def prepare_training_data(self, raw_data: pd.DataFrame):
        data = raw_data.copy()

        # 'text' column already present, no need to do anything
        data['labels'] = data['sarcasm_label']
        data = data.astype({'text': str, 'labels': int})

        return data[['text', 'labels']]

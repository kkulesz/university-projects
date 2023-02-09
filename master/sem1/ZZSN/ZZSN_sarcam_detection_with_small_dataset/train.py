import pandas as pd
import torch
from simpletransformers.t5 import T5Model
from simpletransformers.classification import ClassificationModel

from models.t5 import T5Wrapper
from models.bert import BertWrapper
from trainer import OurTrainer
import consts
import utils

use_cuda = torch.cuda.is_available()


def prepare_t5(number_of_rows: int) -> T5Wrapper:
    t5_args = consts.T5_ARGS
    t5_args.output_dir = f"{consts.T5_OUTPUT}-{number_of_rows}"
    t5 = T5Model(
        t5_args.model_type,
        consts.T5_MODEL_NAME,
        args=t5_args,
        use_cuda=use_cuda
    )

    return T5Wrapper(t5)


def prepare_bert(number_of_rows: int) -> BertWrapper:
    bert_args = consts.BERT_ARGS
    bert_args.output_dir = f"{consts.BERT_OUTPUT}-{number_of_rows}"
    bert = ClassificationModel(
        consts.BERT_MODEL_TYPE,
        consts.BERT_MODEL_NAME,
        args=bert_args,
        use_cuda=use_cuda,
        weight=[4, 1]
    )
    return BertWrapper(bert)


if __name__ == '__main__':
    utils.prepare_environment()

    raw_train_data = pd.read_csv(consts.TEST_DATA)
    test_data = pd.read_csv(consts.TEST_DATA)
    test_inputs, test_labels = utils.prepare_evaluation_data(test_data)

    train_size = consts.INIT_TRAIN_SIZE
    while train_size <= consts.MAX_TRAIN_SIZE:
        torch.cuda.empty_cache()
        print("=" * 100)
        print(f"Training {consts.CURRENT_VARIANT} for nrows={train_size}")
        data = raw_train_data[0: train_size]

        if consts.CURRENT_VARIANT == consts.T5:
            model = prepare_t5(train_size)
        elif consts.CURRENT_VARIANT == consts.BERT:
            model = prepare_bert(train_size)
        else:
            raise Exception(f"Invalid variant={consts.CURRENT_VARIANT}!")

        trainer = OurTrainer(model)
        trainer.train(data)

        test_preds = trainer.model.predict(test_inputs)
        print(f" Number of positives: {sum(test_preds)}")

        train_size += consts.STEP

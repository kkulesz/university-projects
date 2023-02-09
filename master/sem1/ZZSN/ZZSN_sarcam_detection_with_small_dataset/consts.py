import os
from simpletransformers.t5 import T5Args
from simpletransformers.classification import ClassificationArgs

T5 = 't5'
BERT = 'bert'
CURRENT_VARIANT = T5
####################################################################
DATA_DIR = 'data'
TRAIN_DATA = os.path.join(DATA_DIR, 'train_preprocessed.csv')
TEST_DATA = os.path.join(DATA_DIR, 'test_preprocessed.csv')

T5_OUTPUT = 't5-output'
BERT_OUTPUT = 'bert-output'

INIT_TRAIN_SIZE = 500
MAX_TRAIN_SIZE = 2000
STEP = 500
SAVE_EVERY_N_EPOCHS = 10
NUM_OF_TRAIN_EPOCHS = 10
LEARNING_RATE = 1e-3
#####################################################################
T5_MODEL_TYPE = 't5'  # 't5', 'mt5', 'byt5'
T5_MODEL_NAME = 't5-small'
T5_ARGS = T5Args(
    model_type=T5_MODEL_TYPE,
    overwrite_output_dir=True,

    train_batch_size=3,  # CUDA out of memory if greater ;/
    num_train_epochs=NUM_OF_TRAIN_EPOCHS,
    save_model_every_epoch=False,
    save_steps=INIT_TRAIN_SIZE * SAVE_EVERY_N_EPOCHS,
    learning_rate=LEARNING_RATE
)
#####################################################################
BERT_MODEL_TYPE = 'roberta'  # bert, roberta, xlm, ...
BERT_MODEL_NAME = 'roberta-base'
BERT_ARGS = ClassificationArgs(
    train_batch_size=32,
    overwrite_output_dir=True,
    num_train_epochs=NUM_OF_TRAIN_EPOCHS,
    logging_steps=1,
    save_model_every_epoch=False,
    save_steps=INIT_TRAIN_SIZE * SAVE_EVERY_N_EPOCHS,
    learning_rate=LEARNING_RATE
)

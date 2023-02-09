import torch
import numpy as np
import os
import random
import warnings


def seed_torch(seed=2137):
    #  taken from: https://github.com/pytorch/pytorch/issues/7068
    random.seed(seed)
    os.environ['PYTHONHASHSEED'] = str(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)  # if you are using multi-GPU.
    torch.backends.cudnn.benchmark = False
    torch.backends.cudnn.deterministic = True


def turn_off_stupid_warnings():
    # ugly, but simpletransfomers.T5 throws some stupid
    # deprecation warnings if everything is done the way
    # the official tutorial says: https://simpletransformers.ai/docs/t5-model/
    warnings.filterwarnings("ignore", category=FutureWarning)


def prepare_environment():
    turn_off_stupid_warnings()
    seed_torch()


def prepare_evaluation_data(data):
    inputs = data['text'].astype(str).values.tolist()
    labels = data['sarcasm_label'].astype(int).values.tolist()

    return inputs, labels


def prepare_sarcasm_evaluation_data(data):
    inputs = data['text'].astype(str).values.tolist()
    labels = data['sarcasm_type'].astype(int).values.tolist()

    return inputs, labels

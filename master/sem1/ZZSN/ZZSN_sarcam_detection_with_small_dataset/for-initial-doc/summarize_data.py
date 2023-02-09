import pandas as pd

test_or_train = 'test'
data_dir = '../data'
raw_file = f'{data_dir}/isarcasm_{test_or_train}.csv'
downloaded_file = f'{data_dir}/{test_or_train}_downloaded.csv'
preprocessed_file = f'{data_dir}/{test_or_train}_ready.csv'


def summarize(df):
    sarcastic = len(df[df["sarcasm_label"] == "sarcastic"])
    not_sarcastic = len(df[df["sarcasm_label"] == "not_sarcastic"])

    print(f'size            = {len(df)}')
    print(f'sarcastic       = {sarcastic}')
    print(f'not_sarcastic   = {not_sarcastic}')
    print(f'sarcastic/non ratio = {sarcastic / not_sarcastic}')
    assert (sarcastic + not_sarcastic == len(df))


if __name__ == '__main__':
    raw_df = pd.read_csv(raw_file)
    downloaded_df = pd.read_csv(downloaded_file)
    preprocessed_df = pd.read_csv(preprocessed_file)
    print(test_or_train)
    print('=' * 50)
    print("RAW DATA")
    summarize(raw_df)

    print('=' * 50)
    print("DOWNLOADED DATA")
    summarize(downloaded_df)
    # print('=' * 50)
    # summarize_preprocessed(preprocessed_df)

import pandas as pd
import re
import preprocessor as p

import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.tokenize import TweetTokenizer

test_or_train = 'train'
input_file = f'../data/{test_or_train}_downloaded.csv'
output_file = f'../data/{test_or_train}_preprocessed.csv'

p.set_options(
    p.OPT.URL, p.OPT.EMOJI, p.OPT.MENTION, p.OPT.SMILEY, p.OPT.NUMBER, p.OPT.RESERVED
)  # remove everything instead of hashtags


def initial_preprocess(df: pd.DataFrame):
    df['text'] = df['text'].astype('string')

    # remove urls, mentions, emojis etc.
    for i, tweet_text in enumerate(df['text']):
        df.loc[i, 'text'] = p.clean(tweet_text)

    # remove digits
    df['text'] = df['text'].replace('\d+', '')

    # make everything lowercase
    df['text'] = df['text'].str.lower()

    # remove punctuation
    for i, tweet_text in enumerate(df['text']):
        df.loc[i, 'text'] = re.sub(r'[^\w\s#]', '', tweet_text)  # DO NOT REMOVE HASH

    # remove unnecessary whitespaces and newlines
    for i, tweet_text in enumerate(df['text']):
        df.loc[i, 'text'] = re.sub(" +", " ", tweet_text)
        df.loc[i, 'text'] = re.sub("\n", " ", df.loc[i, 'text'])
        df.loc[i, 'text'] = re.sub("\t", " ", df.loc[i, 'text'])

    # remove empty tweets
    # df = df[df.text != ""]

    # set labels as zeros and ones
    for i, label in enumerate(df['sarcasm_label']):
        df.loc[i, 'sarcasm_label'] = 0 if label == 'not_sarcastic' else 1

    return df


def handle_tokenization(df):
    # tokenize
    df['tokens'] = [[]] * len(df)
    tokenizer = TweetTokenizer()
    pd.options.mode.chained_assignment = None  # default='warn'
    for i, tweet_text in enumerate(df['text']):
        df['tokens'].loc[i] = tokenizer.tokenize(tweet_text)

    # remove english stop words eg. 'a', 'the', ...
    nltk.download('stopwords')
    stop_words = set(stopwords.words('english'))
    for i, tweet_tokens in enumerate(df['tokens']):
        df['tokens'].loc[i] = [token for token in tweet_tokens if token not in stop_words]

    # remove tweets without any token
    df = df[df['tokens'].map(lambda r: len(r)) > 0]

    return df


if __name__ == '__main__':
    df = pd.read_csv(input_file)
    df = initial_preprocess(df)
    # df = handle_tokenization(df)

    df = df[['sarcasm_label', 'text']]
    df.to_csv(output_file)

import tweepy
import pandas as pd
import numpy as np
import math

api_key = ''
api_secret_key = ''
bearer_token = ''

access_token = ''
access_token_secret = ''

test_or_train = 'train'
input_file = f'../data/isarcasm_{test_or_train}.csv'
output_file = f'../data/{test_or_train}_downloaded.csv'

if __name__ == '__main__':
    batch_size = 100  # tweepy's limit

    df = pd.read_csv(input_file)
    number_of_batches = math.ceil(len(df) / batch_size)
    print(f"Number of tweet batches = {number_of_batches}")
    batches = np.array_split(df, number_of_batches)

    client = tweepy.Client(bearer_token=bearer_token)

    ready_data = pd.DataFrame()
    fetched = 0
    for batch in batches:
        ids = list(batch['tweet_id'])
        client_response = client.get_tweets(ids)
        response_data = client_response.data

        tweets_list = list(map(
            lambda t: {'tweet_id': t.id, 'text': t.text},
            response_data
        ))
        fetched += len(tweets_list)
        tweets_df = pd.DataFrame(tweets_list)

        merged = batch.merge(tweets_df, on='tweet_id', how='inner')
        ready_data = ready_data.append(merged, ignore_index=True)

    print(f"Fetched tweets: {fetched}")
    ready_data.to_csv(output_file)

from matplotlib import pyplot as plt
import pandas as pd


def my_plot(title, x, y_t5, y_bert):
    fig, ax = plt.subplots(1, figsize=(8, 6))
    fig.suptitle(title)
    ax.plot(x, y_t5, color="red", label="T5")
    ax.plot(x, y_bert, color="green", label="ROBERTA")
    plt.legend(loc="lower right", title="Models", frameon=False)
    f1_plot = plt.gcf()
    plt.show()
    plt.draw()
    f1_plot.savefig(f'{title}.png')


if __name__ == '__main__':
    t5_results = pd.read_csv('T5_results.csv')
    bert_results = pd.read_csv('BERT_results.csv')

    x = t5_results['Learning dataset size']
    t5_f1 = t5_results['f1 value']
    bert_f1 = bert_results['f1 value']
    t5_recall = t5_results['recall']
    bert_recall = bert_results['recall']

    my_plot("F1", x, t5_f1, bert_f1)
    my_plot("Recall", x, t5_recall, bert_recall)

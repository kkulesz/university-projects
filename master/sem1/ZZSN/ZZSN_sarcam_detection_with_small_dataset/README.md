## 1. Set up environment
```
python -m venv ./venv
source venv/Scripts/activate
pip install -r requirements.txt
```

## 2. Set parameters in `consts.py` 
- which model to train: `T5` or `BERT`
- hyperparameters of chosen model
- directories naming
- experiment parameters
## 3. Run training script
```
python train.py
```
note: three directories will be created as result of running this script: `runs`, `cache_dir` and `{model-name}-{nrows}`.

## 4. Evaluate fine-tuned models
```
python evaluate.py
```
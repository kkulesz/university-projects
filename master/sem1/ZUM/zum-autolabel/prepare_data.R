source("params.R")

get_data <- function() {
  if (dataset == "spambase")
    data <- read.table("spambase.dat", header = FALSE, skip = 63, sep = ',')
  else if (dataset == "ring")
    data <- read.table("ring.dat", header=FALSE, skip=25, sep = ',')
  else if (dataset =="magic")
    data <- read.table("magic.dat", header=FALSE, skip=16, sep=',')
  else
    stop()
    
  n_rows = nrow(data)
  n_cols = ncol(data)
  
  # z-score normalization
  data[1:(n_cols - 1)] <- scale(data[1:(n_cols - 1)])
  if (is.factor(data[, n_cols]))
    data[, n_cols] <- as.numeric(data[, n_cols])
  data[, n_cols] <- data[, n_cols] - min(data[, n_cols])
  
  # splitting
  train_size                      = as.integer(n_rows * split_ratios[1])
  test_size                       = as.integer(n_rows * split_ratios[2])
  train_labelled_initial_size     = as.integer(train_size * split_train_ratios[1])
  train_unlabelled_initial_size   = as.integer(train_size * split_train_ratios[2])
  
  shuffled_data <-  data[sample(1:n_rows), ]
  test_set <-       shuffled_data[row.names(data) %in%
                                    1:test_size, ]
  labelled_set <-   shuffled_data[row.names(data) %in%
                                    (test_size + 1):(test_size + train_labelled_initial_size), ]
  unlabelled_set <- shuffled_data[row.names(data) %in%
                                    (test_size + train_labelled_initial_size + 1):(test_size + train_labelled_initial_size + train_unlabelled_initial_size), ]
  decision_set <-   shuffled_data[row.names(data) %in%
                                    (test_size + train_labelled_initial_size + train_unlabelled_initial_size + 1):n_rows, ]
  
  return(list(
    "test_set"=test_set,
    "labelled_set"=labelled_set,
    "unlabelled_set"=unlabelled_set,
    "decision_set"=decision_set,
    
    "n_cols"=n_cols,
    "train_labelled_initial_size"=train_labelled_initial_size
  ))
}
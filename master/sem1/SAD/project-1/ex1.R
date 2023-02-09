################### Prepare data
df <- read.csv('data/k_d_07_2021.csv', header = FALSE)
col_names <- c('station_code', 'station_name', 'year', 'month', 'day', 
               'T_MAX', 'status_T_MAX', 'T_MIN', 'status_T_MIN', 'T_AVG', 'status_T_AVG',
               'T_MIN_GROUND', 'status_T_MIN_GROUND', 'SUM_OF_PRECIPITATION', 'status_SUM_OF_PRECIPITATION',
               'TYPE_OF_RAINFALL', 'SNOW_COVER_HEIGHT', 'status_SNOW_COVER_HEIGHT')
colnames(df) <- col_names

# unique(raw_data$station_name)
our_stations = c('PSZCZYNA', 'PUŁTUSK', 'BIAŁOWIEŻA')
df <- df[df$station_name %in% our_stations, ]

# unique(df$status_T_MAX) # NA
# unique(df$status_T_MIN) # NA
# unique(df$status_T_AVG) # NA
#   => so every measurement was valid => we can get rid of these columns

useful_columns <- c('station_name', 'year', 'month', 'day', 'T_MAX', 'T_MIN', 'T_AVG')
df <- df[, useful_columns]


################### Do the exercise 
# a.1
boxplot(T_MAX ~ station_name, df, xlab="station", ylab="max. temp.", main="zad1 a1")

# a.2
df$DAILY_T_DIFF <- df$T_MAX - df$T_MIN
boxplot(DAILY_T_DIFF ~ station_name, df, xlab="station", ylab="temp. difference within day", main="zad1 a2")

# a.3
source("ex1_utils.R")

df$DATE <- as.Date(paste(df$year, df$month, df$day, sep = "-"), "%Y-%m-%d")
df <- subset(df, select = -c(year, month, day))
df <- count_diff_between_days_for_each_station(df)
boxplot(DIFF_MAX_T_BETWEEN_PREVIOUS_DAY ~ station_name, df, xlab="station", ylab="max. temp. diff. between days", main="zad1 a3")



# b.1
b1_data <- df[df$station_name == 'PUŁTUSK', ]
b1_data <-b1_data$DIFF_MAX_T_BETWEEN_PREVIOUS_DAY
b1_mean <- mean(b1_data, na.rm = TRUE)
b1_sd <- sd(b1_data, na.rm = TRUE)

hist(b1_data, prob=TRUE, xlab="max. temp. diff.", main="zad1 b", xlim=c(-10,10))
curve(dnorm(x, mean=b1_mean, sd=b1_sd), add=TRUE, yaxt="n")
###############################################################################
test_data <- rnorm(30, mean=b1_mean, sd=b1_sd)
hist(test_data, prob=TRUE, add=FALSE, col=rgb(0.5, 0, 0, alpha = 0.25))
hist(b1_data, prob=TRUE, add=TRUE, col=rgb(0, 0, 0.5, alpha = 0.25))
curve(dnorm(x, mean=b1_mean, sd=b1_sd), add=TRUE, yaxt="n")


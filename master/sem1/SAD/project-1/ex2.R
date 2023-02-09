if (!require(lubridate))
  install.packages('lubridate')
if (!require(dplyr))
  install.packages('dplyr')

library(lubridate) # for quarter function
library(dplyr)

raw_df <- read.csv('data/katastrofy.csv', header = TRUE)
number_of_flights_data <- read.csv('data/number-of-flights-from-2.csv', header = TRUE)
raw_df$Date <- as.Date(raw_df$Date,  format= "%m/%d/%Y")
raw_df <- raw_df[raw_df$Date >= "2004-01-01" & raw_df$Date < "2020-01-01", ]

raw_df


raw_df$Quarter <- quarter(raw_df$Date, with_year = TRUE)
grouped_by_quarter <- raw_df %>% group_by(Quarter) %>% tally()
str(grouped_by_quarter)
mean(grouped_by_quarter$n)

hist(raw_df$Quarter)

plot(grouped_by_quarter$Quarter, grouped_by_quarter$n, type='h')

require(ggplot2)

x <- 1:5
x
tibble(raw_df) -> dt
ggplot(dt, aes(x = Aboard, y = Fatalities)) + geom_point()
dpois(x = dt.Abroad, lambda = 1)
dt$Quarter <- quarter(dt$Date)
dt$Quarter
dt_by_quarter <- dt %>% group_by(Quarter)
dt_by_quarter
ggplot(dt_by_quarter, aes(Quarter)) + 
  geom_histogram() +
  ggtitle("Katastrofy w poszczególnych kwartałach") +
  xlab("Kwartał") +
  ylab("Liczba katastrof")

  
tibble(raw_df) -> dt
dt <- filter(dt, Date >= as.Date("2004-01-01"))
dt <- dt %>% group_by(year(Date))
dt
ggplot(dt, aes(year(Date))) + 
  geom_histogram()

dt
catastrophies <- dt %>% count(dt$`year(Date)`)
catastrophies

num_of_flights <- tibble(read.csv('data/number-of-flights-from-2.csv', header = TRUE, nrows=6))
num_of_flights


res <- merge(num_of_flights, catastrophies, by.x = "Category", by.y = "year(Date)")
res$Number.of.Flights.from.2004.to.2021 <- res$Number.of.Flights.from.2004.to.2021 * 1000000
res
res$percentage <- res$n / res$Number.of.Flights.from.2004.to.2021 * 100
res
ggplot(res, aes(x = Category, y = percentage)) +
  geom_line()

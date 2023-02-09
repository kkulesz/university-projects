if (!require(dplyr))
  install.packages('dplyr')
library(dplyr) # for mutate()

count_diff_between_days <- function(df){
  # make sure its sorted in ascending way
  sorted <- df[order(df$DATE), ]
  
  # calculate difference between this and previous day
  result <- mutate(sorted, DIFF_MAX_T_BETWEEN_PREVIOUS_DAY = T_MAX - lag(T_MAX))
  return(result)
}


count_diff_between_days_for_each_station <- function(df){
  station_dfs <- split(df, with(df, interaction(station_name)), drop = TRUE)
  result = data.frame()
  for(station_df in station_dfs){
    station_result <- count_diff_between_days(station_df)
    result <- rbind(result, station_result)
  }
  return (result)
}
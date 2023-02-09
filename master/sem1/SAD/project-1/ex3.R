require(ggplot2)
require(tidyverse)

setwd('./data/2021/')
getwd()

dt <- list.files(pattern = '*csv') %>%
  map_df(~read.csv(., header = F))

names(dt) <- c("kod stacji", "nazwa stacji", "rok", "miesiac", "dzien", 
               "TMAX", "status TMAX", "TMIN","status TMIN", 
               "STD", "status STD", "TMNG", "status TMNG", 
               "SMDB", "status SMDB", "rodzaj opadu",
               "PKSN", "status PKSN")

dt$amplituda <- dt$TMAX - dt$TMIN

dt <- dt %>% group_by(dt$miesiac) %>% summarise(mean_amp = mean(amplituda))

ggplot(dt, aes(x = `dt$miesiac`, y = mean_amp)) + geom_line()

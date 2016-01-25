#!/usr/bin/RScript
data <- read.table('lakebed.txt')
ml <- lm(data[,3] ~ data[,2] + data[,1])
print(ml)

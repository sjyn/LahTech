#!/usr/bin/RScript
source("batch.R")
lets <- c(19,20,5,22,5,14,1,12,1,14,18,15,19,5,14,4,1,8,12)
res <- batching(3,lets)
print(res)
# Produces
# [1] 14.666667 13.666667  4.666667 15.666667 12.666667  4.333333

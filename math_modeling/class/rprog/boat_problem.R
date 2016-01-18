# Example of problem 2
# Given a plane 2x + 3y = -4z
#
# x	  y     z
# 1   1   -1.25
# 1   2     -2
# 3   2   -2.98

lake <- read.table('lakebed.txt')
mlm <- lm(lake[,3] ~ lake[,2] + lake[,1])
print(mlm)

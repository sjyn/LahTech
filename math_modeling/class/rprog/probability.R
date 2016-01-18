#!/usr/bin/RScript

# binomial distributions
#
# _binom(search_prob,total_number,probability)
#
# several prefixes
# r - random distribution - random plot
# d - density distribution - finding value of function
# p - cumulative distribution - area up to a region

# What is the probability of finding one left handed person in a group
# 17, given that the probability of finding a left handed person is 1.7%.
bdist <- dbinom(1,1,0.1)
print(bdist)

# Doing a random distrubution is similar
rdist <- rbinom(1000,17,0.1)
print(rdist)

# _norm: normal distrubution
# _chisq: chi squared distribution

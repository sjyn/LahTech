# Example usage of c call

# age <- c(1,3,5,2,11,9,3)
# weight <- c(4.4,5.3,7.2,5.2,8.5,7.3,6)
# #linear model
# linMod <- lm(weight ~ age)
# print(linMod)
# #standard deviation
# print(sd(age))
# print(sd(weight))
# #plot age vs. weight
# plot(age, weight)

#Data frames
ages <- c(33,45,22,32,19,54)
diabetic <- c(TRUE,FALSE,FALSE,TRUE,TRUE,FALSE)
status <- c('poor','improved','excellent','poor','improved','poor')
frame <- data.frame(ages, diabetic, status)
print(frame)

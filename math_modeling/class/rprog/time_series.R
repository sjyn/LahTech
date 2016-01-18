#!/usr/bin/RScript

# Example Business Data
#
# 153 189 221 215 302 223 201 173 121 106 86 87 108
# 133 177 241 228 283 255 238 164 128 108 87 74 95
# 145 200 187 201 292 220 233 172 119 81 65 76 74
# 111 170 243 178 248 202 163 139 120 96 95 53 94

sales <- c(153, 189, 221, 215, 302, 223, 201, 173, 121, 106, 86, 87, 108,
			133, 177, 241, 228, 283, 255, 238, 164, 128, 108, 87, 74, 95,
			145, 200, 187, 201, 292, 220, 233, 172, 119, 81, 65, 76, 74,
			111, 170, 243, 178, 248, 202, 163, 139, 120, 96, 95, 53, 94)

# Create a time series out of the sales vector
# sales = the vector
# start: the start time (year: 2011, month: 1)
# end: the end time (year: 2014, month 12)
# frequency: occurance -- 13 x 4 = 52 in our case
series <- ts(sales, start=c(2011,1), end=c(2014,13), frequency=13)
print(series)
plot(series)

# try to smooth out the data set with a moving average
plot(ma(series, 3))
fit <- stl(series, s.window="period")
plot(fit)

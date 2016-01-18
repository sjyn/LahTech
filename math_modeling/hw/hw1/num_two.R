#!/usr/bin/RScript
if(require("forecast")){
    data <- scan("co2.txt")
    png("02data_plot.png")
    plot(data)
    dev.off()
    series <- ts(data, start=c(2000,1), end=c(2016,13), frequency=13)
    png("02seasonal.png")
    seasonal <- stl(series, s.window="period")
    plot(seasonal)
    dev.off()
}

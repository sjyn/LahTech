#!/usr/bin/RScript
if(require("forecast")){
    data <- scan("hmwk1.txt")        #read in the file
    png("01data_plot.png")           #plot to specified png
    plot(data)                       #plot data
    dev.off()
    png("01data_smoothed.png")       #plot to specified png
    plot(ma(data,4))                 #plot smoothed data
    dev.off()
}

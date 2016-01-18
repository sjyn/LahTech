if(require("forecast")){
	data <- scan("hmwk1.txt")
	plot(data)
	plot(ma(data,4))
}

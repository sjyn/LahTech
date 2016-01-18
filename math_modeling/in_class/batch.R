#	function name: batching
#	parameters:
#	    k   size of each batch
#           x   data
#       return value:
#           an array of the averages of each batch
# 	description: this function separates the data x into
#       floor(length(x)/k) batches and returns the array of
#       the averages of each batch
#	To run the code, type y<-batching(k,x) to place the consecutive
#       batch means of size k, of the data in the vector x, in the vector y
batching <- function(k,x)  {
    m <- floor(length(x)/k);
    result <- rep(0,m);
    for(i in 1:m) result[i] <- mean(x[(i-1)*k+(1:k)]);
    return(result);
}
#include <stdio.h>
#include <stdlib.h>

double myfunc (double x){
    return x*x;
}

void main(){
    int i;
    int total=0;
    double a = 4.;
    double b = 7.;
    double m = 100.;
    double frandinc1,frandinc2;

    for(i = 1; i <= 100000; i++){
        frandinc1 = a + (b - a) * (double)rand()/(double)RAND_MAX;
        frandinc2 = m * (double)rand()/(double)RAND_MAX;
        if(frandinc2 <= myfunc(frandinc1))
            total = total + 1;
    }

    printf("value is %f ", total*(b-a)*m/100000);
}

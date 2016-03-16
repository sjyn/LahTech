/**
This program attempts to solve the probability that a person lost in a forest will
return to a river bank whle doing a ranndom walk
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

int main(){
    //Generate random numbers with rand();
    //In order to return to the river, the man needs to follow
    // l * sin(theta1)
    // The next day is
    // l * sin(theta2)
    // The sum
    // lsin(theta1) + lsin(theta2) <= 0
    // sin(theta1) + sin(theta2) <= 0

    double theta1 = rand() * PI;
    double theta2 = rand() * 2 * PI;
    


    return 0;
}

/* Heres a comment for Dr. Martin's Math440 students!!!!!!!!!!!!!!!!!! */
/* Math440 student's -- u must compile with the line gcc crofton.c -lm */
/* Please notice the -lm in the above line                             */
/***********************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
  double pi;
  double theta1;
  double theta2;
  int i;
  int total = 0;
  double frandinc, frandexc;
  
  pi = 4.*atan(1.);
  
  for (i=1; i<=100000; i++){
    frandinc = (double)rand()/(double)RAND_MAX;
    frandexc = (double)rand()/((double)(RAND_MAX)+1);

    theta1 = pi * frandinc;
    theta2 = 2.*pi * frandexc;

    if( sin(theta1) + sin(theta2) <= 0)
      total = total + 1;
  }

  printf("probability is %f", total/100000.);
}

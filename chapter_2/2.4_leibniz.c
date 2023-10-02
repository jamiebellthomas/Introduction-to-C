#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
// Leibniz sequence is a way of approxomating pi, basically all numerators are 4
// Initial denominator is 1, add to denom each time and change sign and aggregate
int main(void){
   long it;
    float denominator = 1.0, pi_est = 4.0, next_value;
    for(it = 0; it<10000000; it++){
	// add 2 to denimator variable
	denominator +=2.0;
	// Calculate the absolute value of the next value
	next_value = 4.0/(denominator);
	// Every other iteration, flip the sign, then add next value on and print
	if(it%2 == 0){
	    next_value *= -1.0;
	}
	pi_est += next_value;
	printf("\r%.15g",pi_est);
    }
    print("\n");


}

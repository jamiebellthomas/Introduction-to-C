// Generate triangle numbers in 2 ways
// First via pattern (Adding successive numbers)
// Second via equation n(n+1)/2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SEQUENCE 10

int main(){
    // Init the t_number variable (this will increment), the euqation value and pattern value
    int t_number=1, T_n_eq, T_n_pat=0;
    // Init while loop, this will iteratively calculate successive triangle numbers
    while(t_number<=SEQUENCE){
	// Calculate T_n based of current triangle number using equation
	printf("Via Equation:\n");
	T_n_eq = t_number*(t_number + 1)/2;
	printf("%i\n",T_n_eq);
	// Add current t_number to total T_n to work out the next value
	T_n_pat += t_number;
	printf("Via Pattern:\n");
	printf("%i\n\n",T_n_pat);

	// Increment t_number for next iteration
	++t_number;
	}

}











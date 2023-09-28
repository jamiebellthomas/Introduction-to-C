// Create a hailstone sequence.
// In a hailstone sequence, if x_n is even, x_n+1 = x_n/2
// If x_n is odd, x_n+1 = 3x_n + 1
// Write a program that prints this sequence and terminates when it gets to 1

#include <stdio.h>
#include <stdlib.h>
int main(){
    // Initialise operator variable. This will be passed through the sequence
    int x;
    // Request an input and scan it in
    printf("Give an initial value (integer) for this hailstone sequence");
    scanf("%i",&x);
    // This loop will run until it reaches 1 (at which point it will start to repeat itself)
    while(x != 1){
	// If x%2 = 0, it is even, else it is odd. 
	// At the end of each iteration the current x value is displayed.
	if(x%2 == 0){
	    x = x/2;
	}
	else{
	    x = (3*x) + 1;
	}
	printf("%i\n",x);
    }
}

// Create a hailstone sequence.
// In a hailstone sequence, if x_n is even, x_n+1 = x_n/2
// If x_n is odd, x_n+1 = 3x_n + 1
// Write a program that prints this sequence and terminates when it gets to 1

#include <stdio.h>
#include <stdlib.h>
int main(){
    // Initialise operator variable. This will be passed through the sequence
    long x;
    // Request an input and scan it in
    printf("Give an initial value (integer) for this hailstone sequence");
    scanf("%li",&x);
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
	printf("%li\n",x);
    }
}


/*
This example was the first time we saw an integer overflow occur.

in C, an int is a 16-bit variable. Each bit corresponds to a power of 2 (Its binary)
The 16 bit signed variable sequence is composed of 15 2^x bits (the value of the number) and a signed bit
The largest number that can be processed by 15 bits is 32767. When you exceed this, the final signed bit is activated
This causes the sign of the number to flip

You can see to get around this we have used the long variable. A long is stored in 32 bits, meaning the range of values it can process is far higher.
Long variables have a new type hing (%li)

Similar errors can occur with all data types. 

*/

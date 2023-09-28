#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Because we're including math.h here we'll need a -lm at the end of out compile command. 

// This will be the same as 1.8 except this will only accept odd integers in the list of numbers (no floats or even integers)

int main(void){
    int value_max = -10000, value=0,input;
    printf("Please enter the number of numbers you'd like to compare (this program only accepts odd integers)");
    // Recap, this reads in the first value in the stdin and allocates it to input. The ampersand is an address (important)
    scanf("%d",&input);
    // This code will structurally be the same as the previous except this will have a check to see if the input is even
    for(int i=1;i<=input;++i){
	scanf("%d", &value);
	//Implement a check to see if value is even
	// If mod 2 is zerp, its even.
	// Rest of code is trivial
	if(value%2 == 0){
	    i--;
	    printf("Odd Integers Only");
	}
	else{
	    if(value > value_max){
		value_max = value;
	    }
	}

    }
    printf("%s %d\n","Max Value:",value_max);



}

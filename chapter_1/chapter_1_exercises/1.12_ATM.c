#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DIVISION 20

// We have an ATM that can only dispense £20 notes
// The user asks the program for a sum of money (integer)
// The program tells them the two nearest sums it can supply (multiples of 20)

int main(){
    // Initialise the amount reqested and the modulus variables
    int amount, remainder;
    // Init the boolean to see if change is required
    bool change = true;
    while(change == true){
	// This loop will run until the user requests a value that doesn't warrant change
	// Print request for withdrawl amount & scan the user's input in
	printf("How much money would you like? (Can only do denominations of %i)",DIVISION);
	scanf("%d",&amount);
	// Using mod function, see if any change is required
	remainder = amount%DIVISION;
	// If %20 yields 0, no change is required, this value can be dispensed and the loop can terminate
	if(remainder == 0){
	     printf("\nOK, dispensing £%i\n", amount);
	     change = false;
	}
	// If not, notify the user of the nearest value to their's that wouldn't require change
	else{
	    printf("\nI can give you %i or %i, try again.\n",(amount-remainder),(amount+(DIVISION-remainder)));
	}


    }



}
// Bit of an issue I ran into here was the idea that was covered in lectures today. 
// The stdbool headfile works off a typedef where true = 1 and false = 0
// When i was making this script I got the remainder and change variables mixed up.
// It was hard to spot this error because it compiled successfully as these integers are very interchangable from the copilers perspective.
// This lead to erroneous calculations being seen in the final line of code (It only changed the amount by 1 which was the corresponding integer value of the true boolean)


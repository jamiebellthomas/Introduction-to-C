// This program needs to print the first n primes. Its pretty simple but this time we're
// going to split this program into functions and test them (we haven't done this before)
// There will be a main function (this will not be tested)
// But there will be an underlying function that determines if a number is prime or not and returns a boolean. This function will be tested.


//In this script we'll see a simplified version of setting up a codebase
// Your programme MUST be split into its most granular components (units).
// These units are then tested using assert to make sure they're each performing as expected.
// These units are then combined to form sub-systems which in turn are combined to form the overall system.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
/*
This function takes in an integer
It returns a boolean describing if the integer is a prime number
*/
bool prime(int num){
    int div;
    if(num==1){
 	return false;
    }
    for(div = 2;div<num;++div){
 	if(num%div == 0){
 	return false;
 	}
    }
    return true;
}
// Let's test this function

void test(void){
    // Tests are as simple as comparing a function to the known output and making sure they produce the same thing
    assert(prime(5) == true);
    assert(prime(15) == false);
    // Throwing in some more complicated examples creates a more effective test
    assert(prime(277) == true);

}

int main(){
    // First thing in main is always to call the test function to make sure our units are performing as expected
    test();
    // Initialise n (desired number), found (number found) & current (current number being examined)
    int n,found=0, current=1;
    // Now we have the function, let's do the actual exercise. Print the first n primes (n is defined by user)
    // As seen previously, collect user input
    printf("This program prints the first n prime numbers where you define n");
    printf("How many prime numbers do you want to see?");
    scanf("%i",&n);
    // Set up a while loop which runs until it finds n prime numbers.
    while(found<n){
	// If a prime number is found, print it and update the number of primes found variable
	if(prime(current) == true){
	    ++found;
	    printf("Prime #%i : %i\n",found, current);
	}
	// Regardless of result, move onto next number at end of iteration
	++current;
    }

}

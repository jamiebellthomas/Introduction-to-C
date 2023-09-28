#include <stdio.h>
#include <stdlib.h>
#define MULTIPLIER 7
#define INCREMENT 5
#define MODULUS 11
#define LOOPS 20
/*
Make a linear congruent generator
An LCG has the forumla X_n+1 = (a*X_n + c)%m
Where m is the modulus
a is the multiplier and 0 < a < m
c is the increment and 0 < c < m
X_0 is the seed/start value and 0 <= X_0 < m

Once you know all this, this problem becomes very easy
*/

int main(){
    // LCG
    // Initialise variable and store initial value as seed
    int x = 0, seed = x;
    printf("%s %i", "Seed is:",seed);
    for(int i = 0; i<LOOPS; i++){
	// At the start of each loop, recalculate the new value and print it
        x = (MULTIPLIER*x + INCREMENT)%MODULUS;
	printf("\n%i",x);
	// If this value is the same as the seed, this is the end of the cycle.
	// Terminate loop and print period
	if(x==seed){
            printf("\n%s %d %s","Cyle completed in ",i+1,"iterations");
	    break;
        }
    }
    // If it hasn't found a repetition within the iterator, print a timeout error.
    printf("\n Iterator has timed out");
    return 0;
}

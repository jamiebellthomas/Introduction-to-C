// The computer selects a random number from 0-1000
// The user gets 10 attempts to guess if
// Each guess tell them if they are too high or too low. 
// Terminate if they run out of guesses or guess correctly
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(){
    // Initialise random value, the guess variable and guess counter
    int value = rand()%1000, guess,iterator = 10;
    // Initialise boolean for whether or not they've guesses correctly
    bool correct = false;
    // This can be done in a for loop with a loop counter, it may be better actually
    // but we've used a while loop and will track iterations outself
    while(correct == false){
	// If they're out of guesses, terminate the loop and print a failure message
	if(iterator == 0){
	    printf("\nYou are out of guesses");
	    break;
	}
	// If loop is still active, tell user what they have to do
	printf("\nGuess an integer (0-1000). You have %i guesses remaining", iterator);
	scanf("%i", &guess);
	// See where their guess lies and relay relevant information
	if(guess > 1000 || guess < 0){
	    printf("\nOut of range");
	}
	else if(guess > value){
	    printf("\nToo high");
	}
	else if(guess < value){
	    printf("\nToo low");
        }
	else{
	    printf("\n%i is correct!\n", guess);
	    correct = true;
	}
	// Take away one of their attempts.
	iterator-=1;
    }
}























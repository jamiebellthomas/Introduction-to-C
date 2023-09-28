//RAND_MAX is a built in constant that is #defined in the headerfile
#include <stdlib.h>
#include <stdio.h>
#define LOOP_COUNTER 500
int main(void){
    // Initialise median as the MAX/2, and the rnd selection as floats
    int median = RAND_MAX/2,rnd;
    // Init loop counter and the plus&minus counters as integers
    int i, minus_cnt = 0, plus_cnt = 0;
    // Start a for loop for LOOP_COUNTER iterations
    // This caused me issues initially. The second term is the condition that must
    // be satisfied for the loop to proceed. 
    // Initially I was doing i == LOOP_COUNTER. This is incorrect as the loop
    // was never starting as i initially wasn't = LOOP_COUNTER.
    // This will proceed now for as long as i <= LOOP_COUNTER
    for(i=0; i <= LOOP_COUNTER; i++){
	// Allocate a random  number for the loop and determine which bin it belongs in
	rnd = rand();
	if(rnd>median){
	    ++plus_cnt;
	}
	else{
	    ++minus_cnt;
	}
    }
    printf("%s %i %s %i\n", "Plus counter:", plus_cnt, "Minus Coutner", minus_cnt);
    printf("%s %i\n", "Difference is:",abs(plus_cnt-minus_cnt));
    return 0;
}


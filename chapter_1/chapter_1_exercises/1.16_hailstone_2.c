// This is an extension of 1.15, except now we want to know what initial value gives:
// 1) The highest number in its sequence
// 2) The longest sequence

#include <stdio.h>
#include <stdlib.h>
// If the number of sequences gets too high (over 10000ish), we run out of memory? (Program stops)
#define SEQ_MAX 10000000
int main(){
    // Not sure if is is necessary but we'll use sine typedef's to divide our variables into local ones (applied to each sequence) and global ones
    typedef long global;
    typedef long local;
    global longest_seq_global = 0, longest_seq_init=0, largest_num_global=0, largest_num_init=0;
    local x, x_init, largest_number_local, iterations;
    // What makes this code significant is its the while loop from 1.15 within a for loop that runs for a range of initial values
    for(x_init=1; x_init <= SEQ_MAX; ++x_init){
        x = x_init;
	largest_number_local = 0;
	iterations = 1;
    // So this is the main hailstone loop. Soo info will be extracted from here
        while(x != 1){
            // If x%2 = 0, it is even, else it is odd. 
            // At the end of each iteration the current x value is displayed.
            if(x%2 == 0){
                x = x/2;
            }
	    else{
                x = (3*x) + 1;
            }
	    if(x>largest_number_local){
		largest_number_local = x;
	    }
	    ++iterations;
	}
	// Records if this sequence was longer than the previous best and if it contains a larger value than previously seen
        if(largest_number_local > largest_num_global){
	    largest_num_global = largest_number_local;
	    largest_num_init = x_init;
	}
	if(iterations > longest_seq_global){
	    longest_seq_global = iterations;
	    longest_seq_init = x_init;
        }
    }
    printf("\nRANGE: 1-%i\n\n",SEQ_MAX);
    printf("LONGEST SEQUENCE\n");
    printf("Initial Value: %li\n",longest_seq_init);
    printf("Sequence Length: %li\n\n", longest_seq_global);
    printf("LARGEST VALUE\n");
    printf("Initial Value: %li\n",largest_num_init);
    printf("Value: %li\n", largest_num_global);
}


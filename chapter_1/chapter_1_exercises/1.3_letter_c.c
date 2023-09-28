// Write a script that prints a large letter C (not curved)
// Where the height of the letter is determined by a preprocessing directive (#define)

#include <stdio.h>
// This defines the macro HEIGHT, any time it appears now it will be set to 10
#define HEIGHT 10

int main(void){
    // Initialise i as 0
    int i=0;
    // Print the top of the "C"
    printf("\nIIIIIIIIII\n");
    // Print the back bone with a while loop, it adds a certain number of I's according to HEIGHT
    while(i<HEIGHT){
	// Standard while loop
    	i+=1;
    	printf("II\n");
    }
    // Print the bottom of the "C"
    printf("IIIIIIIIII\n");
    return 0;
}


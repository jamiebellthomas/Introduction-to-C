// This program will do 2 things:
// Firstly it will ask the user how many numbers it will be inputting. This will return a +e integer
// Then it will ask the user to input that many numbers and determine which of them is the largest (inputs can be +vie or +e and don't have to be integers

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    // Firstly let's ask the user how many numbers they'll be inputting
    // Initialise the integer variables - user input variable and the iteration varaiable
    int inputs,i;
    // Initialise the float variables - The current value being considered and the max_value (set to minus infinity so it is guaranteed to have been replaced by end of code) 
    float value, max_value=-INFINITY;

    printf("How many numbers do you wish to enter?\n");
    // Firstly request a single input from the user 
    scanf("%i", &inputs);
    printf("%s %i %s\n","Please input",inputs,"number(s)");
    for(i=1;i<=inputs;++i){
	// Then use a for loop to update the input "tray" however many times as defined by the input variable 
	scanf("%f", &value);
	// If a larger value is detected, replace max_value and proceed
	if(value > max_value){
	    max_value = value;
	}

    }
    printf("%s %f\n","Max value inputted:",max_value);
    return  0;

}
/*
scanf() Notes:

This has been causing me some issues but I understand it now

scanf() is NOT like input() in Python. When you run input() in Python it takes the user input and assigns the whole thing to a single variable

When you call scanf() in scans inputs from the input buffer zone (stdin). If the tray is empty, the code will sit there doing nothing.

Let's look at this code and explain how scanf() works here:

(Assuming correct usage) Initially scanf() is called to 'request' a single value. As the script has just commenced, the stdin is empty, therefore nothing happens.
This is why we print a message prompting the user to enter a value.
Once a value is entered, it is instantly called as scanf() is called for a single input.

Moving down, the script calls scanf() again in the for loop. The initial value given to the stdin has been processed and passed into the code, and has therefore left the buffer zone (its now empty)
What this loop is doing is reading in single values from the the buffer zone. When you use this code you SHOULD enter in as many value as defined in the previous inputs.
But 'mis-using' this code helps explain how it works:
If you enter a single integer at the start and then enter in fewer values than that in the for loop, the code will stop as the buffer is empty
Likewise if you enter too many numbers it will not consider the excess. THESE EXCESS VALUES REMAIN IN THAT BUFFER.
Knowing this you can bypass the second entry entirely. If you enter all the values initially, they will remain in the buffer and automatically be passed into the script when it is called in the for loop
For example:
5 1 2 3 4 6
5 will initially be passed in as 'input'
The next 5 values will then automatically be passed in at the for loop.

*/

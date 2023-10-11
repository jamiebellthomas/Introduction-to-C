#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#define ALPHA_SHIFT 25
//Prototypes
int alpha_position(int letter, bool upper);
int conversion(int position);
int ascii_position(int position, bool upper);

int alpha_position(int letter, bool upper){
/*
Will convert a letter of either case to its alphabet index 
*/
    unsigned pos;
    if (upper){
	pos = letter - 'A';
    }
    else{
        pos = letter - 'a';
    }
    return pos;
}


int secret(int position){
    // This function flips the alphabet indicies 
    unsigned new_pos;
    new_pos = ALPHA_SHIFT - position;
    return new_pos;
}

int ascii_position(int position, bool upper){
    /*
    This converts the alphabet index back into a letter
    */
    char new_letter;
    if(upper){
        new_letter = position + 'A';
    }
    else{
	new_letter = position + 'a';
    }
    return new_letter;
}

void test(){
    // Simple tests for each sub-function
    assert(alpha_position('a',false) == 0);
    assert(alpha_position('A',true) == 0);
    assert(alpha_position('x',false) == 23);
    assert(alpha_position('x',false) == alpha_position('X',true));
    assert(secret(5) == 20);
    assert(ascii_position(19,false) == 't');
    assert(ascii_position(19,true) == 'T');

}

int main(void){
    //Initialise variables and run tests
    char a;
    bool upper;
    test();
    // Collect inputs
    printf("Give us an expression and we'll flip the letters\n");
    // While there are characters in the buffer this will keep running
    while((a = getchar()) != '\n' && a != EOF){
	// It is important this is only run on the letters and not any spaces or punctuation
	if(isalpha(a)){
	    // Determine if its upper case then call the respective functions as appropriately 
	    upper = isupper(a);
	    a = alpha_position(a, upper);
	    a = secret(a);
	    a = ascii_position(a, upper);
	}
        // Return info
        printf("%c",a);
    }
    printf("\n");

}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
// ... prototype
bool isvowel(char a);

bool isvowel(char a){
    // Only 5 cases so a case by case basis switch is ok
    switch(a){
	case 'a':
	    return true;
	case 'e':
	    return true;
	case 'i':
	    return true;
	case 'o':
	    return true;
	case 'u':
	    return true;
    }
    return false;
}

void test(void){
    char vowel = 'a';
    char consonant = 'b';
    assert(isvowel(vowel) == true);
    assert(isvowel(consonant) == false);
}

int main(void){
    // run tests and initialise character variable that will be used
    test();
    char a;
    printf("Enter a string of characters and we'll convert any lower case vowels to upper");
    while((a = getchar())!= '\n' && a != EOF){
	if(isvowel(a) == true){
	    // This is a function built into <ctype.h>
	    a = toupper(a);
	}
	printf("%c",a);
    }
    printf("\n");
}

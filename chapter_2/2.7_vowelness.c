#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

bool isvowel(char a);

bool isvowel(char a){
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

char char_switch(char b){
    switch(b){
	case 'a':
	    b = 'A';
	    return b;
	case 'e':
	    b = 'E';
	    return b;
	case 'i':
	    b = 'I';
	    return b;
	case 'o':
	    b = 'O';
	    return b;
	case 'u':
	    b = 'U';
	    return b;
    }
    return b;
}

void test(void){
    char vowel = 'a';
    char consonant = 'b';
    assert(isvowel(vowel) == true);
    assert(isvowel(consonant) == false);
    assert(char_switch(vowel) == 'A');
    assert(char_switch(consonant) == 'b');
}

int main(void){
    test();
    char a;
    while((a = getchar())!= '\n' && a != EOF){
	printf("%c", a);
    }
}

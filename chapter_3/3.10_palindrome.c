#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
/*
The task is simple on the surface, take in a sentence (string)
and say if it's a palindrome, ignoring letter case and stripping punctuation

Method, initialise 2 arrays, append the raw input to one, and move a stripped
version to the other array. Then check this stipped version for symmetry.

Functions:
- main
- User input
- Stripping
- Palindrome checker
*/

#define STR_LEN 50
void user_input(char* original_string);
int strip(char* original, char* stripped);
int pal_check(int word_len, char* word);
void print_array(char* array);
void test();

int main(void){
    // Need to initialise original as zero or it'll have garbage it in, then when you run strip it'll probably 
    //find another int that isalpha in the array and pass that to stipped too.
    char original_string[STR_LEN] = {0}, stripped_string[STR_LEN];
    int word_len = 0, pal = 2;
    test();
    user_input(original_string);
    word_len = strip(original_string, stripped_string);
    pal = pal_check(word_len, stripped_string);
    if(pal){
	printf("is a palindrome\n");
    }
    if(!pal){
	printf("is not a palindrome\n");
    }
}

//fgets() is what you want for user input!
void user_input(char* original_string){
    printf("Enter a string and we'll tell you if it's a palindrome (not case sensitive and punctuation will be discarded)\n");
    fgets(original_string,STR_LEN,stdin);
}

int strip(char* original, char* stripped){
    int letter_count = 0;
    for(int i = 0;i < STR_LEN;i++){
	//printf("%c",(original[i]));
	if(isalpha(original[i])){
	    //printf("%c %i\n", original[i], i);
	    stripped[letter_count] = tolower(original[i]);
	    ++letter_count;
	}
    }
    stripped[letter_count] = '\0';
    return letter_count;
}

int pal_check(int word_len, char* word){
    int i, half = round(word_len/2);
    for(i = 0; i <= (half-1); i++){
	if(word[i] != word[(word_len-1)-i]){
	    return 0;
	}
    }
    return 1;
}

void print_array(char* array){
    char letter = 'a';
    int i = 0;
    while(letter != '\0'){
	letter = array[i];
	printf("%c", letter);
	++i;
    }
    printf("\n");
}

void test(){
    char test_original[STR_LEN] = "Race car!", test_stripped[STR_LEN]; //test_input[STR_LEN];
    int test_len = 0;
    test_len = strip(test_original, test_stripped);
    assert(test_len == 7);
    assert((test_stripped[0] == 'r')&&(test_stripped[2] == 'c')&&(test_stripped[3] == 'e')&&(test_stripped[6] == 'r'));
    assert(pal_check(test_len, test_stripped) == 1);
    //user_input(test_input);
    //print_array(test_input);
}

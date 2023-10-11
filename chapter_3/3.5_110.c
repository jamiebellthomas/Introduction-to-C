#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
So basically with this one were generating the line below based off the 3 values above it
Go on Wikipedia and look at Rule 110 for more details but basically:

111 -> 0
110 -> 1
101 -> 1
100 -> 0
011 -> 1
010 -> 1
001 -> 1
000 -> 0

I think the 5 main sub-functions that'll lead into main will be
1) User input (this may have sub-sub functions)
2) Extract the 3 bit code from the row above
3) Determine whether a 3 bit code returns a 1 or zero
4) Print array function so we can see successive lines
5) Moves shifts array from next to current
6) Tests
*/
#define ROW_WIDTH 50
#define PATTERN_WIDTH 3
#define ROW_NUMBER 50
void test();
int extraction(int pos, int* row, int* pattern);
int return_val(int* pattern);
void print_array(int* array);
int array_move(int* array1, int* array2);
int user_input(int* current_row);
void rand_fill(int* current_row);


int main(void){
    int current[ROW_WIDTH], next[ROW_WIDTH], patt[PATTERN_WIDTH];
    test();
    user_input(current);
    int i, j;
    for(i=0; i< ROW_NUMBER; i++){
	for(j=0;j<ROW_WIDTH;j++){
	    extraction(j, current, patt);
	    next[j] = return_val(patt);
	}
	print_array(next);
	array_move(next, current);
    }
    return 0;
}


int user_input(int* current_row){
    char in;
    printf("Would you like a randomised first row or a single starting 1?\n");
    printf("Enter 'r' for random 's' for single\n");
    scanf("%c", &in);
    if(in == 'r'){
	rand_fill(current_row);
	return 0;
    }
    else if(in == 's'){
        int col;
	printf("Which column would you like to be a 1, pick between 1 - %i\n", ROW_WIDTH);
        scanf("%i", &col);
	current_row[col-1] = 1;
	return 0;
    }

    else{
	printf("Invalid input, terminating programme\n");
        exit(0);
    }
}

void rand_fill(int* current_row){
    int i;
    for(i=0;i<ROW_WIDTH;i++){
	current_row[i] = rand()%2;
    }
}

int extraction(int pos, int* row, int* pattern){
    if(pos==0){
	pattern[0] = row[ROW_WIDTH-1];
	pattern[1] = row[0];
	pattern[2] = row[1];
    }
    else if(pos == (ROW_WIDTH-1)){
	pattern[0] = row[0];
        pattern[1] = row[ROW_WIDTH-1];
        pattern[2] = row[ROW_WIDTH-2];
    }
    else{
	pattern[0] = row[pos-1];
	pattern[1] = row[pos];
	pattern[2] = row[pos+1];
    }
    return 0;
}

int return_val(int* pattern){
    if((pattern[0] == 1)&&(pattern[1] == 1)&&(pattern[2] == 1)){return 0;}
    else if((pattern[0] == 1)&&(pattern[1] == 1)&&(pattern[2] == 0)){return 1;}
    else if((pattern[0] == 1)&&(pattern[1] == 0)&&(pattern[2] == 1)){return 1;}
    else if((pattern[0] == 1)&&(pattern[1] == 0)&&(pattern[2] == 0)){return 0;}
    else if((pattern[0] == 0)&&(pattern[1] == 1)&&(pattern[2] == 1)){return 1;}
    else if((pattern[0] == 0)&&(pattern[1] == 1)&&(pattern[2] == 0)){return 1;}
    else if((pattern[0] == 0)&&(pattern[1] == 0)&&(pattern[2] == 1)){return 1;}
    else{return 0;}
}

void print_array(int* array){
    int i;
    for(i=0;i<ROW_WIDTH;i++){
	printf("%i ", array[i]);
    }
    printf("\n");
}
int array_move(int* array1, int* array2){
// Set array2 to array1
// array2 is current arra1 is next
    int i;
    for(i=0;i<ROW_WIDTH;i++){
	array2[i] = array1[i];
    }
    return 0;
}

void test(){
    int test_row[ROW_WIDTH] = {0,1,1,0,1,0,1,0,0,1}, test_output[PATTERN_WIDTH];
    int test_move1[ROW_WIDTH] = {1,1,1,1,1,1,1,1,1,1}, test_move2[ROW_WIDTH] = {0,0,0,0,0,0,0,0,0,0};
    // These asserts were failing initially because they were getting confused comparing ints with shorts (failing the assertions)
    extraction(2, test_row, test_output);
    assert((test_output[0] == 1) && (test_output[1] == 1) && (test_output[2] == 0));//This is the only wat to run assertions on array outputs
    assert(return_val(test_output) == 1);

    extraction(7, test_row, test_output);
    assert((test_output[0] == 1) && (test_output[1] == 0) && (test_output[2] == 0));
    assert(return_val(test_output) == 0);

    array_move(test_move1, test_move2);
    assert((test_move1[0] == test_move2[0])&&(test_move1[1] == test_move2[1])&&(test_move1[2] == test_move2[2]));
}


/* 
Ok essay time, this went really horribly for a long time because I kept tripping over using lots of different types (ints, unsigned, const etc..)
And pointers were being a bitch. This script is now a good example of how to use pointers.
ALWAYS USE SQUARE BRACKETS WHEN REFERRING TO ARRAYS. NOT *(array + i), Niell likes it and it's just better and more readable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define ROW_WIDTH 10
#define PATTERN_WIDTH 3

int test_func(int* array1, int* array2);
void test();
void print_array(int* array);


int main(void){
    test();
}


void test(){
    int test_move1[PATTERN_WIDTH] = {1,0,1}, test_move2[PATTERN_WIDTH] = {0,1,0};
    test_func(test_move1, test_move2);
    assert((test_move1[0] == test_move2[0])&&(test_move1[1] == test_move2[1])&&(test_move1[2] == test_move2[2]));
}


int test_func(int* array1, int* array2){
// Set array2 to array1
// array2 is current arra1 is next
    int i=0;
    for(i=0;i<PATTERN_WIDTH;i++){
	array2[i] = array1[i];
    }
}

void print_array(int* array){
    int i;
    for(i=0;i<PATTERN_WIDTH;i++){
        printf("%i ", array[i]);
    }
    printf("\n");
}

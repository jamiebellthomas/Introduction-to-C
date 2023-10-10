// First part of this exercise is to take an integer (N) off the user and return a suffled array containing numbers 1-N
// Second part is to make the shuffle function O(n)
// We're not going to use pointers in this exercise as ARRAYS ARE ALREADY POINTERS
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LEN 100
//Prototypes
int input();
int create_array(int *array, int value);
void print_array(int *array, int value);
int shuffle_array(int *array, int value);

int main(void){
    int val = 1, songs[ARRAY_LEN];
    int *songs_p = songs;
    val = input();
    create_array(songs_p, val);
    shuffle_array(songs_p, val);
    print_array(songs_p, val);
}

int input(void){
    int choice = 0;
    printf("Input an integer and we'll return a shuffled array (MAX 100)\n");
    scanf("%i", &choice);
    return choice;
}

int create_array(int array[ARRAY_LEN], int value){
    int i;
    for(i=0;i<value;i++){
	array[i] = (i+1);
    }
}

void print_array(int array[ARRAY_LEN], int value){
    int i;
    for(i=0;i<value;i++){
        printf("%i ",array[i]);
    }
    printf("\n");
}

int shuffle_array(int array[ARRAY_LEN], int value){
    int i, temp, r_val;
    for(i = 0;i < value; i++){
	r_val = rand()%value;
	temp = array[r_val];
	array[r_val] = array[i];
	array[i] = temp;
    }
}



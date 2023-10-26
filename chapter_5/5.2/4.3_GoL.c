#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define WIDTH 15
#define HEIGHT 15
#define BASE_TEN 10
#include "neillsimplescreen.h"


void array_init(int** array);
void array_free(int** array);
void print_2D_array(int** array);
void read_in_data(FILE* fp, char* file_name);
int moore_neighbourhood_one_count(int** array, int row, int col);
int next_gen(int** array, int row, int col);
void random_fill(int** array);
void array_transfer(int** array_current, int** array_next);
void gol_iterator(int** array_current, int** array_next, int iterations);



int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Too many input arguments given (Expected 2 but got %i)", argc);
        exit(-1);
    }
    srand(time(NULL));

    char* p;
    long iterations = strtol(argv[2],&p,BASE_TEN);
    iterations = (int)iterations;
    // Use strtol to extract numeric values from argv. just doing (int) ony took the 
    // first digit (23 came out as 2) as argv is just a pointer 
    //FILE* fp = NULL;
    int** array_current = (int**)calloc(HEIGHT, sizeof(int*));
    int** array_next = (int**)calloc(HEIGHT, sizeof(int*));
    // When making fixed length arrays, calloc() is the more effective tool
    // As this allows you to specify the number of elements and the size of each
    // as opposed to just the overall size.
    if(array_current == NULL || array_next == NULL){
        fprintf(stderr,"** Memory Allocation Failed");
        exit(-1);
    }

    array_init(array_current);
    array_init(array_next);
    
    //read_in_data(fp, file_name);

    random_fill(array_current);
    gol_iterator(array_current, array_next, iterations);


    array_free(array_current);
    array_free(array_next);
    //fclose(fp);
}

void array_init(int** array){
    for(int i = 0;i < HEIGHT; i++){
        array[i] = (int*)calloc(WIDTH, sizeof(int));
        array[i][0] = 0;
        if(array[i] == NULL){
            fprintf(stderr,"* Memory Allocation Failed");
            exit(-1);
        }
    }
}

void array_free(int** array){
    for(int i = 0;i < HEIGHT;i++){
        free(array[i]);
    }
    free(array);
}

void print_2D_array(int** array){
    for(int i = 0; i<HEIGHT;i++){
        for(int j = 0;j<WIDTH;j++){
            if(array[i][j] == 1){
                neillfgcol(green);
            }
            else{
                neillfgcol(red);
            }
            
            printf("%i", array[i][j]);
        }
        printf("\n");
        
    }
    neillreset();
}

void read_in_data(FILE* fp, char* file_name){
    fp = fopen(file_name,"r");
    if(fp == NULL){
        fprintf(stderr, "Error in retrieving your file.");
    }
    // Im going to leave the file input for now because it
    // keeps going super weird, gonna focus on implementing the GoL rules
    // But basically this input needs to translate to inserting 1's in the correct coordinates
}

int next_gen(int** array, int row, int col){
    int count = moore_neighbourhood_one_count(array,row,col);
    if(array[row][col] == 1){
        if(count == 2 || count == 3){
            return 1;
        }
        return 0;
    }
    if(count == 3){
        return  1;
    }
    return 0;
    
}

int moore_neighbourhood_one_count(int** array, int row, int col){
    int counter = 0;
    for(int i = -1; i<=1 ;i++){
        for(int j = -1; j<=1; j++){
            if(((row+i)<HEIGHT) && ((col+j)<WIDTH) && ((col+j)>=0) && ((row+i)>=0) && (i!=0 || j!=0)){
                if(array[row+i][col+j] == 1){
                    ++counter;
                }
            }
        }
    }
    return counter;
}

void random_fill(int** array){
    for(int row = 0;row<HEIGHT;row++){
        for(int col = 0;col<WIDTH;col++){
            if(rand()%2 == 0){
                // This means 25% of the boxes should be set to 1. 
                array[row][col] = 1;
            }
        }
    }
}

void array_transfer(int** array_current, int** array_next){
    for(int row = 0;row<HEIGHT;row++){
        for(int col = 0;col<WIDTH;col++){
            array_current[row][col] = array_next[row][col];
        }
    }
}

void gol_iterator(int** array_current, int** array_next, int iterations){
    for(int i = 0;i<iterations;i++){
        print_2D_array(array_current);
        printf("--------------------\n");
        for(int row = 0;row<HEIGHT;row++){
            for(int col = 0;col<WIDTH;col++){
                array_next[row][col] = next_gen(array_current,row,col);
            }
        }
        array_transfer(array_current,array_next);
        neillbusywait(0.5);  
    }
}

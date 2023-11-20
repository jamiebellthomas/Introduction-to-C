#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define COLS 50

void swap(char* x, char* y);
void anagram_finder(char* a, int l, int r, char** db, char* original);
void word_checker(char** db, const char* str, char* original);
size_t line_counter(char* file_name);
// Write a function that takes in a string and lists all viable anagrams in the english
// language according to words_alpa.txt 
// First task is to write a function that lists all possible anagrams
// Second task is to check if each are in words_alpha.txt

/* Function to swap values at two pointers */
void swap(char* x, char* y) { 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void anagram_finder(char* a, int l, int r, char** db, char* original){ 
    int i; 
    if (l == r){ 
        word_checker(db,a,original);
    } 
    else { 
        for (i = l; i <= r; i++) { 
            swap((a + l), (a + i)); 
            anagram_finder(a, l + 1, r, db, original); 
            swap((a + l), (a + i)); // backtrack 
        } 
    } 
    // Recursion may not have been the best way to do this. Its very computationally expensive
    // Maybe a histogram would've been the way to go and then strcmp(). Any word over 6 letters takes too long to process. 
} 
  
void word_checker(char** db, const char* str, char* original){
    for(int i = 0;db[i];i++){
        if((strlen(str) == strlen(db[i])) && (strcmp(db[i],str) == 0) && (strcmp(str,original))){
            printf("%s\n",db[i]);
        }
    }
}

size_t line_counter(char* file_name){
    FILE *fp;
    size_t counter = 0;
    char c;
    fp = fopen(file_name, "r");
    if(fp == NULL){
        fprintf(stderr,"Cannot open file.\n");
    }
    while((c = fgetc(fp)) != EOF){
        if(c == '\n'){
            ++counter;
        }
    }
    return counter;
}

void user_input(char* inp){
    printf("Enter a word and we'll show you the anograms!\n");
    scanf("%s", inp);
    printf("---------\n");

}



int main(void) { 
    FILE *fp;
    size_t row_counter;
    char inp[COLS];


    user_input(inp);
    fp = fopen("words_alpha.txt","r");
    if(fp == NULL){
        fprintf(stderr,"Cannot open file.\n");
        exit(-1);
    }
    row_counter = line_counter("words_alpha.txt");
    // Come back later and tackle this without a row counter but instead using realloc()
    
    /* We looked at a new idea here - the double pointer (or the pointer to pointers)
       This allowed us to define an array of pointers and allocate memory for these pointers
       We could then go into each of these pointers and reallocate them to the respective values
       from the file input. */

    char** db = (char**)malloc(sizeof(char *) * (row_counter+1));
    if(db == NULL){
        fprintf(stderr, "** Memory Allocation Failed");
    }
    for (int i = 0; i < (int)(row_counter+1); i++){
        db[i] = (char*)malloc(sizeof(char)*COLS);
        if(db[i] == NULL){
            fprintf(stderr, "* Memory Allocation Failed");
        }
        fscanf(fp, "%s", db[i]);
    }

    int len = strlen(inp) - 1;
    char copy[COLS];
    strcpy(copy,inp);

    anagram_finder(inp,0,len,db,copy);
    printf("---------\n");

    fclose(fp);

    //We need to free up all allocated memory, only freeing the global pointer won't be enough
    for(int i = 0; i < (int)(row_counter+1); i++){
        free(db[i]);
    }
    free(db);

    return 0; 
}


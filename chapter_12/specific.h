#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAXTOKENS 100
#define MAXTOKENSIZE 20


/*
Here prog is going to be the series of words we're reading.
For this primative example, we're going to use a fixed size 2D array
and ensure these bounds aren't exceeded.

For the extension, we'll make this structure cooler :)
*/
struct prog
{
    char words[MAXTOKENS][MAXTOKENSIZE];
    int current_word;
};

typedef struct prog Program;

void Prog(Program* p);
void Code(Program* p);



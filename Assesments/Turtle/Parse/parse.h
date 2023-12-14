#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 50

struct prog {
    int current_word;
    char** word_array;
    int array_len;
};

typedef struct prog Program;

void test(void);
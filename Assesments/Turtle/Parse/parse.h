#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define MAXTOKENS 100
#define MAXTOKENLEN 50
#define ASCII_A 65
#define ASCII_Z 90

struct prog {
    int current_word;
    char** word_array;
    int array_len;
};

typedef struct prog Program;

void test(void);
Program* prog_init(void);
void free_prog(Program* prog);

bool valid_letter(Program* prog);
bool valid_variable(Program* prog);
bool valid_number(Program* prog);
bool varnum(Program* prog);
bool valid_word(Program* prog);
bool valid_item(Program* prog);
bool valid_op(Program* prog);
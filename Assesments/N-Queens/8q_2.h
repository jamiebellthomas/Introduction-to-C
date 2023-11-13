#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_GRID 10
#define MAX_SEARCH_SPACE 1000000
#define VERBOSE_FLAG "-verbose"
#define QUEEN 'Q'
#define QUEEN_COVERED 'X'
#define QUEEN_UNCOVERED 'O'
struct state {
    int queens;
    char board[MAX_GRID][MAX_GRID];
};

typedef struct state state;

void user_input(int argc, char* argv[], int* N, bool* verbose);
bool valid_number(char val[]);
void test();
void init_board(state* position, int size);
void print_board(state* position, int size);

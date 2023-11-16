#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define MAX_GRID 10
#define MIN_GRID 1
#define MAX_SEARCH_SPACE 1000000
#define VERBOSE_FLAG "-verbose"
#define QUEEN 'Q'
#define QUEEN_COVERED 'X'
#define QUEEN_UNCOVERED 'O'
#define TEST_SEARCH_SPACE 25
struct state {
    int queens;
    char board[MAX_GRID][MAX_GRID];
};

typedef struct state state;

void user_input(int argc, char* argv[], int* N, bool* verbose);
bool valid_number(char val[]);
void test();
state init_state(int size);
bool state_cmp(state state_one, state state_two, int size);
void cpy_state(state old_state, state* new_state, int size);
void row_explore(state* position, int row_index, int size);
void col_explore(state* position, int col_index, int size);
void diag_explore(state* position, int row_index, int col_index, int size);
void queen_adder(state* position,int row_index, int col_index, int size);
bool unique_state(state solution_space[MAX_SEARCH_SPACE], long frontier, state current_state, int size);
void next_gen(state solution_space[MAX_SEARCH_SPACE], long* frontier, long* index, int size, state* state_holder, bool verbose, long* solution_counter);
void verbose_output(state position, int size);


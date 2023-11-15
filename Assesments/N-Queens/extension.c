#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#define VERBOSE_FLAG "-verbose"
#define QUEEN 'Q'
#define QUEEN_COVERED 'X'
#define QUEEN_UNCOVERED 'O'
#define MIN_GRID 1
#define MAX_GRID 13
// 10x10 has 724 solutions, so this will be the solution space limit 
#define SOLUTION_LIMIT 73712
#define MEM_FACTOR 4

struct state {
    int queens;
    char board[MAX_GRID][MAX_GRID];
};
typedef struct state state;

// Prototypes:
void user_input(int argc, char* argv[], int* N, bool* verbose);
bool valid_number(char val[]);
state init_state(int size);
void row_explore(state* position, int row_index, int size);
void col_explore(state* position, int col_index, int size);
void diag_explore(state* position, int row_index, int col_index, int size);
void queen_adder(state* position,int row_index, int col_index, int size);
void queen_removal(state* position,int row_index, int col_index, int size);
void covered_reset(state* position, int size);
void queen_reset(state* position, int size);
void recursion(state solution_space[SOLUTION_LIMIT], int* solution_count, 
               state* state_holder, int col, int size, bool verbose);
void verbose_output(state position, int size);


void test();
void print_board(state* position, int size);


int main(int argc, char* argv[]){
    test();

    bool verbose = false;
    int size = 0, solution_count = 0, init_col = 0;
    user_input(argc, argv, &size, &verbose);

    state* solution_space = (state*)malloc(sizeof(state)*SOLUTION_LIMIT);
    if(solution_space == NULL){
        fprintf(stderr,"Memory Allocation Failed.\n");
         exit(EXIT_FAILURE);
    }

    state state_holder = init_state(size);
    recursion(solution_space, &solution_count, &state_holder, init_col, size, verbose);

    printf("%i solutions\n", solution_count);
    free(solution_space);
}


void print_board(state* position, int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            printf("%c",position->board[row][col]);
        }
        printf("\n");
    }
}

/*
----------
USER INPUT
----------
*/
void user_input(int argc, char* argv[], int* N, bool* verbose){
    if(argc < 2 || argc > 3){
        fprintf(stderr, "Program expects 1 or 2 arguments but recieved %i\n", (argc-1));
        fprintf(stderr, "Correct usage: ./8q N or ./8q -verbose N\n");
        exit(EXIT_FAILURE);
    }
    if(argc==2){
        if(valid_number(argv[1])){
            *N = atoi(argv[1]);
            return;
        }
        fprintf(stderr, "Numerical argument must be an integer between 1 and %i.\n", MAX_GRID);
        exit(EXIT_FAILURE);
    }

    else{
        if(!valid_number(argv[2])){
            fprintf(stderr, "Numerical argument must be an integer between 1 and %i.\n", MAX_GRID);
            exit(EXIT_FAILURE);
        }
        if(strcmp(argv[1],VERBOSE_FLAG)){
            fprintf(stderr,"Invalid flag (%s), did you mean -verbose?", argv[1]);
            exit(EXIT_FAILURE);
        }
    *N = atoi(argv[2]);
    *verbose = true;
    return;
    }

}

bool valid_number(char val[]){
    //First check is that all chars in argument are digits
    for(int i = 0; i < (int)strlen(val); i++){
        if(!isdigit(val[i])){
            return false;
        }
    }
    // Second check is to make sure the given number is between 1 and 10.
    if(atoi(val) <= MAX_GRID && atoi(val) >= MIN_GRID){
        return true;
    }
    return false;
}

/*
-----------------
INITIALISE STATES
-----------------
*/
state init_state(int size){
    state new_state = {.queens = 0,
                        .board = {{'\0'}}};
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            new_state.board[row][col] = QUEEN_UNCOVERED;
        }
    }
    return new_state;
}



/*
---------------
QUEEN ADDITIONS
---------------
*/

void row_explore(state* position, int row_index, int size){
    for(int col = 0;col<size; col++){
        if(position->board[row_index][col] == QUEEN_UNCOVERED){
            position->board[row_index][col] = QUEEN_COVERED;
        }
    }
}

void col_explore(state* position, int col_index, int size){
    for(int row = 0; row<size; row++){
        if(position->board[row][col_index] == QUEEN_UNCOVERED){
            position->board[row][col_index] = QUEEN_COVERED;
        }
    }
}

void diag_explore(state* position, int row_index, int col_index, int size){
    int size_index = size-1;
    for(int step = 1;step<size;step++){
        // Step NE
        if((row_index+step) <= size_index &&
           (col_index+step) <= size_index &&
           position->board[row_index+step][col_index+step] == QUEEN_UNCOVERED){
            position->board[row_index+step][col_index+step] = QUEEN_COVERED;
        }
        // Step SW
        if((row_index-step) >= 0 &&
           (col_index-step) >= 0 &&
           position->board[row_index-step][col_index-step] == QUEEN_UNCOVERED){
            position->board[row_index-step][col_index-step] = QUEEN_COVERED;
        }
        // Step SE
        if((row_index+step) <= size_index &&
           (col_index-step) >= 0 &&
           position->board[row_index+step][col_index-step] == QUEEN_UNCOVERED){
            position->board[row_index+step][col_index-step] = QUEEN_COVERED;
        }
        // Step NW
        if((row_index-step) >= 0 &&
           (col_index+step) <= size_index &&
           position->board[row_index-step][col_index+step] == QUEEN_UNCOVERED){
            position->board[row_index-step][col_index+step] = QUEEN_COVERED;
        }
    }
}

void queen_adder(state* position,int row_index, int col_index, int size){
    // Add a queen in coords given and, change all unexplored cells in range to explored
    // Only effects unexplored cells
    (position->queens)++;
    position->board[row_index][col_index] = QUEEN;
    row_explore(position, row_index, size);
    col_explore(position, col_index, size);
    diag_explore(position, row_index, col_index, size);

}

/*
-------------
QUEEN REMOVAL
-------------
*/



void covered_reset(state* position, int size){
    for(int row = 0; row<size; row++){
        for(int col =0; col<size; col++){
            if(position->board[row][col] == QUEEN_COVERED){
                position->board[row][col] = QUEEN_UNCOVERED;
            }
        }
    }
}

void queen_reset(state* position, int size){
    for(int row = 0; row<size; row++){
        for(int col =0; col<size; col++){
            if(position->board[row][col] == QUEEN){
                queen_adder(position, row, col, size);
                (position->queens)--;
            }
        }
    }
}

void queen_removal(state* position,int row_index, int col_index, int size){
    (position->queens)--;
    position->board[row_index][col_index] = QUEEN_UNCOVERED;
    covered_reset(position, size);
    queen_reset(position, size);

}

/*
-------------------
RECURSIVE BACKTRACK
-------------------
*/

void recursion(state solution_space[SOLUTION_LIMIT], int* solution_count, 
               state* state_holder, int col, int size, bool verbose){
    if(state_holder->queens == size){
        solution_space[*solution_count] = *state_holder;
        (*solution_count)++;
        if(verbose){
            verbose_output(*state_holder, size);
        }
        return;
    }
    for(int row = 0; row<size; row++){
        if(state_holder->board[row][col] == QUEEN_UNCOVERED){
            queen_adder(state_holder, row, col, size);
            recursion(solution_space, solution_count, 
                      state_holder, (col+1), size, verbose);
            queen_removal(state_holder, row, col, size);
        }
    }
}

/*
--------------
VERBOSE OUTPUT
--------------
*/
void verbose_output(state position, int size){
    for(int col = 0;col<size;col++){
        for(int row = 0;row<size;row++){
            if(position.board[row][col] == QUEEN){
                if(row == MAX_GRID-1){
                    printf("A");
                }
                else{
                    printf("%i",(row+1));
                }
            }
        }
    }
    printf("\n");
}
/*
-------
TESTING
-------
*/

void test(){

    // This test function will only test functions that were
    // not tested in 8q.c
    int test_size = 5;
    state test_state = init_state(test_size);

   for(int step = 0; step<test_size; step++){
        test_state.board[step][step]=QUEEN_COVERED;
    }

    covered_reset(&test_state, test_size);
    
    for(int row = 0; row<test_size; row++){
        for(int col =0; col<test_size; col++){
            assert(test_state.board[row][col] == QUEEN_UNCOVERED);
        }
    }

    test_state.board[0][0] = QUEEN;
    queen_reset(&test_state, test_size);
    
   for(int step = 1; step<test_size; step++){
        assert(test_state.board[step][step] == QUEEN_COVERED);
        assert(test_state.board[step][0] == QUEEN_COVERED);
        assert(test_state.board[0][step] == QUEEN_COVERED);
    }
   // Create a new board, add queens to top left and bottom right
   // Remove the one at the bottom right and the remaining board
   // should be the same as the original board
    state test_state_compare = init_state(test_size);
    queen_adder(&test_state_compare, 0, 0, test_size);
    queen_adder(&test_state_compare, (test_size-1), (test_size-1), test_size);

    queen_removal(&test_state_compare, (test_size-1), (test_size-1), test_size);

    for(int row = 0; row<test_size; row++){
        for(int col =0; col<test_size; col++){
            assert(test_state.board[row][col] == test_state_compare.board[row][col]);
        }
    }


}

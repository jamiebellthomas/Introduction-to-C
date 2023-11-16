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
#define SINGLE_DIGIT_LIMIT 9
#define MIN_GRID 1
#define MAX_GRID 20


struct state {
    int queens;
    char board[MAX_GRID][MAX_GRID];
};
typedef struct state state;

struct solution {
    state position;
    struct solution* previous;
};
typedef struct solution solution;



// Prototypes:
void user_input(int argc, char* argv[], int* N, bool* verbose);
bool valid_number(char val[]);
state init_state(int size);
void row_explore(state* position, int row_index, int size);
void col_explore(state* position, int col_index, int size);
void diag_explore(state* position, int row_index, int col_index, int size);
state queen_adder(state position,int row_index, int col_index, int size);
void recursion(solution** latest_solution, int* solution_count, 
               state state_holder, int col, int size, bool verbose);
void verbose_output(state position, int size);
void test();
void print_board(state* position, int size);
solution* add_solution(solution* previous_solution, state current_solution);
int solution_counter(solution* latest_solution);
void free_list(solution* latest_solution);

int main(int argc, char* argv[]){
    test();

    bool verbose = false;
    int size = 0, solution_count = 0, init_col = 0;
    user_input(argc, argv, &size, &verbose);

 


    
    solution* latest_solution = NULL;
    solution** ptr = &latest_solution;
    
    state state_holder = init_state(size);
    recursion(ptr, &solution_count, state_holder, init_col, size, verbose);

    printf("%i solutions\n", solution_count);


    solution_count = solution_counter(latest_solution);
    printf("%i solutions\n", solution_count);
    free_list(latest_solution);
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

state queen_adder(state position,int row_index, int col_index, int size){
    // Add a queen in coords given and, change all unexplored cells in range to explored
    // Only effects unexplored cells
    (position.queens)++;
    position.board[row_index][col_index] = QUEEN;
    row_explore(&position, row_index, size);
    col_explore(&position, col_index, size);
    diag_explore(&position, row_index, col_index, size);

    return position;

}

/*
-------------------
RECURSIVE BACKTRACK
-------------------
*/

void recursion(solution** latest_solution, int* solution_count, 
               state state_holder, int col, int size, bool verbose){
    
    if(state_holder.queens == size){
        *latest_solution = add_solution(*latest_solution, state_holder); 
        (*solution_count)++;
        if(verbose){
            verbose_output(state_holder, size);
        }
        return;
    }
    for(int row = 0; row<size; row++){
        if(state_holder.board[row][col] == QUEEN_UNCOVERED){
            state next_state = queen_adder(state_holder, row, col, size); 
            recursion(latest_solution, solution_count, 
                      next_state, (col+1), size, verbose);
            //queen_removal(state_holder, row, col, size);
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
                if(row >= SINGLE_DIGIT_LIMIT){
                    printf("%c",('A' + (row-SINGLE_DIGIT_LIMIT)));
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
---------------------
LINKED LIST FUNCTIONS
---------------------
*/

solution* add_solution(solution* previous_solution, state current_solution){
    solution* current_sol = (solution*)malloc(sizeof(solution));
    current_sol->position = current_solution;
    current_sol->previous = previous_solution;

    return current_sol; 
}

int solution_counter(solution* latest_solution){
    int counter = 0;
    while(latest_solution != NULL){
        counter++;
        latest_solution = latest_solution->previous;
    }
    return counter;
}

void free_list(solution* latest_solution){
    solution* next_ptr;
    while(latest_solution != NULL){
        next_ptr = latest_solution->previous;
        free(latest_solution);
        latest_solution = next_ptr;
    }
    free(latest_solution);
}
/*
-------
TESTING
-------
*/
void print_board(state* position, int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            printf("%c",position->board[row][col]);
        }
        printf("\n");
    }
}
void test(){
    solution* latest_solution = NULL;
    state test_state = init_state(8);
    int iterations = 3;
    for(int count = 0; count < iterations; count++){
        test_state.board[0][0] = 'A' + count;
        latest_solution = add_solution(latest_solution, test_state);
    }
    assert(solution_counter(latest_solution) == iterations);
    solution* tmp; 
    for(int count = 0; count < iterations; count++){

        assert(latest_solution->position.board[0][0] == ('A' + (iterations-count-1)));
        tmp = latest_solution->previous;
        free(latest_solution);
        latest_solution = tmp;
    }

    

    
    





}


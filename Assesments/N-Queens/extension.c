#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#define FUNDAMENTAL_FLAG "-fundamental"
#define VERBOSE_FLAG "-verbose"
#define QUEEN 'Q'
#define QUEEN_COVERED 'X'
#define QUEEN_UNCOVERED 'O'
#define SINGLE_DIGIT_LIMIT 9
#define MIN_GRID 1
#define MAX_GRID 15
#define ROTATIONS 4
#define FUNDAMENTAL_JUMP 11
#define CONTINUE 'y'


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

void user_input(int argc, char* argv[], int* N, bool* verbose, bool* fundamental);
bool user_continue();
bool valid_number(char val[]);
state init_state(int size);
void row_explore(state* position, int row_index, int size);
void col_explore(state* position, int col_index, int size);
void diag_explore(state* position, int row_index, int col_index, int size);
state queen_adder(state position,int row_index, int col_index, int size);
void queen_adder_ptr(state* position,int row_index, int col_index, int size);
void recursion(solution** latest_solution, int* solution_count, 
               state state_holder, int col, int size);
void verbose_output(state position, int size);
void verbose_output_loop(solution* solution_space, int size);
solution* add_solution(solution* previous_solution, state current_solution);
int solution_counter(solution* latest_solution);
void free_list(solution* latest_solution);
state rotate_clockwise(state* position, int size);
bool state_cmp(state state_one, state state_two, int size);
solution* fundamental_finder(solution* solution_space, solution* fundamenal_solution_space, 
                       int* fundamenal_solution_counter, int size);
bool geometric_comparison(state* solution, state* position, int size);
void test();


int main(int argc, char* argv[]){
    test();

    bool verbose = false, fundamental = false;
    int size = 0, solution_count = 0, 
        init_col = 0, fundamental_solution_count = 1;
    user_input(argc, argv, &size, &verbose, &fundamental);

    solution* latest_solution = NULL;
    solution** ptr = &latest_solution;
    
    state state_holder = init_state(size);
    recursion(ptr, &solution_count, state_holder, init_col, size);
    if(verbose){
        verbose_output_loop(latest_solution,size);
    }
    printf("%i solutions\n", solution_count);
    if(fundamental){
        // This conditional existes to prevent a seg fault
        // If a null poionter cannot be passed into fundamental_finder
        if(!solution_count){
            printf("\n0 fundamental solutions\n");
            return 0;
        }
        solution* latest_fundamental_solution = NULL;
        latest_fundamental_solution = add_solution(latest_fundamental_solution,latest_solution->position);
        latest_fundamental_solution = fundamental_finder(latest_solution, latest_fundamental_solution, 
                                                         &fundamental_solution_count, size);
        printf("----------\n");
        
        if(verbose){
            verbose_output_loop(latest_fundamental_solution,size);
        }   
        printf("%i fundamental solutions\n", fundamental_solution_count);
        free_list(latest_fundamental_solution);
    }
    printf("----------\n");
    printf("Board size: %ix%i\n",size,size);
    printf("Verbose: %s\n", verbose?"true":"false");
    printf("Fundamental Solutions: %s\n", fundamental?"true":"false");

    free_list(latest_solution);
    return 0;
}

/*
----------
USER INPUT
----------
*/
// User input was expanded from 8q.c, it now includes the -fundamental flag
// It also provides a warning when the user requests fundamenal solutions for
// a grid larger than 11x11 as this is very computationally demanding
void user_input(int argc, char* argv[], int* N, bool* verbose, bool* fundamental){

    
    if(argc < 2 || argc > 4){
        fprintf(stderr, "Program expects 1 to 3 arguments but recieved %i\n", (argc-1));
        fprintf(stderr, "Correct usage:\n./8q N\n./8q -verbose [N]\n./8q -fundamental [N]\n./8q -verbose -fundamental [N]\n");
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

    if(argc == 3){
        if(!valid_number(argv[2])){
            fprintf(stderr, "Numerical argument must be an integer between 1 and %i.\n", MAX_GRID);
            exit(EXIT_FAILURE);
        }

        if(!strcmp(argv[1],VERBOSE_FLAG)){
            *verbose = true;
            *N = atoi(argv[2]);
            return;

        }

        if(!strcmp(argv[1],FUNDAMENTAL_FLAG)){
            if(atoi(argv[2]) > FUNDAMENTAL_JUMP){
                if(!user_continue()){
                    fprintf(stderr,"Aborting...\n");
                    exit(EXIT_FAILURE);
                }
            }
            *fundamental = true;
            *N = atoi(argv[2]);
            return; 
        }
        
        fprintf(stderr,"Invalid flag detected (%s). Valid flags are -verbose or -fundamental\n", argv[1]);
        exit(EXIT_FAILURE);
        
    
}

    else{
        if(!valid_number(argv[3])){
            fprintf(stderr, "Numerical argument must be an integer between 1 and %i.\n", MAX_GRID);
            exit(EXIT_FAILURE);
        }
        if((!strcmp(argv[1],VERBOSE_FLAG) && !strcmp(argv[2],FUNDAMENTAL_FLAG)) ||
            (!strcmp(argv[2],VERBOSE_FLAG) && !strcmp(argv[1],FUNDAMENTAL_FLAG))){
            if(atoi(argv[3]) > FUNDAMENTAL_JUMP){
                if(!user_continue()){
                    fprintf(stderr,"Aborting...\n");
                    exit(EXIT_FAILURE);
                }
                
            }
            *N = atoi(argv[3]);
            *verbose = true;
            *fundamental = true;
            return;
 
        }
        fprintf(stderr,"Invalid flags detected, valid flags are -verbose and -fundamental\n");
        exit(EXIT_FAILURE);
    }
}

// This is a new simple user input function to collect a yes no response from the user. 
bool user_continue(){
    char cont;
    printf("Finding fundamental solutions for grids larger than 11x11 is very computationally expensive\n");
    printf("Do you wish to proceed? (y/n)\n");
    scanf("%c", &cont);
        
    if(cont==CONTINUE){
        printf("This may take a while...\n");
        return true;
    }
    return false;
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
    // This creates a modified version of the original board as a new state
    (position.queens)++;
    position.board[row_index][col_index] = QUEEN;
    row_explore(&position, row_index, size);
    col_explore(&position, col_index, size);
    diag_explore(&position, row_index, col_index, size);

    return position;
}

// This is the same as the queen_adder function, except this modifies 
// the original board located at the given pointer rather than making a copy
void queen_adder_ptr(state* position,int row_index, int col_index, int size){
    (position->queens)++;
    position->board[row_index][col_index] = QUEEN;
    row_explore(position, row_index, size);
    col_explore(position, col_index, size);
    diag_explore(position, row_index, col_index, size);
}
/*
-------------------
RECURSIVE BACKTRACK
-------------------
*/

// This recursively creates new states, by adding queens to uncovered squares
// and stores and encountered state where the number of queens =  board size. 

void recursion(solution** latest_solution, int* solution_count, 
               state state_holder, int col, int size){
    
    if(state_holder.queens == size){
        *latest_solution = add_solution(*latest_solution, state_holder); 
        (*solution_count)++;
        return;
    }
    for(int row = 0; row<size; row++){
        if(state_holder.board[row][col] == QUEEN_UNCOVERED){
            state next_state = queen_adder(state_holder, row, col, size); 
            recursion(latest_solution, solution_count, 
                      next_state, (col+1), size);
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

// This expands verbose output function so you can the first element of a solution
// space stack in , and it will print the whole stack.
void verbose_output_loop(solution* solution_space, int size){
    solution* ptr = solution_space;
    while (ptr != NULL){
        verbose_output(ptr->position, size);
        ptr = ptr->previous;
    }
    
}

/*
---------------
STACK FUNCTIONS
---------------
*/
// This creates a new solution instance using malloc, adds the state information
// to this solution and finally, links it to the previous state.
// This solution becomes the new head pointer of the stack and this is what is
// returned. 
solution* add_solution(solution* previous_solution, state current_solution){
    solution* current_sol = (solution*)malloc(sizeof(solution));
    if(current_sol == NULL){
        fprintf(stderr, "Memory Allocation Failed\n");
        free_list(previous_solution);
        exit(EXIT_FAILURE);
    }
    current_sol->position = current_solution;
    current_sol->previous = previous_solution;

    return current_sol; 
}

// This function counts the number of solution in the stack.
// in main() counters are tracked as solutions are found. This function
// is used in testing.
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
---------------------
FUNDAMENTAL SOLUTIONS
---------------------
*/

state rotate_clockwise(state* position, int size){
    // This functions simply takes a pointer to a state and rotates its board clockwise
    // and returns the new state
    state temp_state = init_state(size); 
    temp_state.queens = size;

    for(int row = 0; row<size ; row++){
        for(int col = 0; col<size; col++){
            if(position->board[row][col] == QUEEN){
                queen_adder_ptr(&temp_state, col, (size-1-row), size);
            }
        }
    }

    return temp_state;

}

state reflection(state* position, int size){
    // Reflection on horizontal axis
    // returns a new state
    state temp_state = init_state(size); 
    temp_state.queens = size;
    
    for(int row = 0; row<size ; row++){
        for(int col = 0; col<size; col++){
            if(position->board[row][col] == QUEEN){
                queen_adder_ptr(&temp_state, (size-1-row), col, size);
            }
                
        }
    }

    return temp_state;
}

bool state_cmp(state state_one, state state_two, int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            if(state_one.board[row][col] != state_two.board[row][col]){
                return false;
            }
        }
    }
    return true;
}


// Takes a state from solution space and compares all geometric permutations to an
// and element in the fundamental solution space. 
// If any permutations match this returns false (solution isn't fundamental)
bool geometric_comparison(state* fundamental_solution, state* solution, int size){
    
    state* state_holder = solution;
    for(int rotations = 0; rotations<ROTATIONS; rotations++){
        *state_holder = rotate_clockwise(state_holder, size);
        if(state_cmp(*fundamental_solution, *state_holder, size)){
            return false;
        }
        *state_holder = reflection(state_holder, size);
        if(state_cmp(*fundamental_solution, *state_holder, size)){
            return false;
        }
        *state_holder = reflection(state_holder, size);




    }
    return true;
}


 // This loops through the existing solution space aod for each element, compares it to
// The fundamental solution space. Each comparison consists of 3 rotations and 3 reflections
// so this will be done in a seperate function.
// This function returns a new stack head. 
solution* fundamental_finder(solution* solution_space, solution* fundamenal_solution_space, 
                       int* fundamenal_solution_counter, int size){
    // initialise current_sol and current_fund to track the current stack heads, while adding to the
    // original fundamental_solution_space stack when necessary.
    solution* current_sol = solution_space, *current_fund = fundamenal_solution_space;
    bool fundamental = false;

    // At the bottom of each stack is a NULL 'anchor' This is how we know where the stack ends
    while(current_sol != NULL){
        fundamental = true;
        current_fund = fundamenal_solution_space;

        while(current_fund != NULL){
            // If we find a match (one of the geometric permutations is already in the fundamental solution stack)
            // we break out of this search loop and move onto the next solution. 
            if(!geometric_comparison(&current_fund->position, &current_sol->position, size)){
                fundamental = false;
                break;
            }
            current_fund = current_fund->previous;
        }
        if(fundamental){
            (*fundamenal_solution_counter)++;
            fundamenal_solution_space = add_solution(fundamenal_solution_space, current_sol->position);
        }
        current_sol = current_sol->previous;
    }

    return fundamenal_solution_space;
}


/*
-------
TESTING
-------
*/


void test(){
    //Only functions unique to extension.c will be tested 



    int test_N = 0, test_argc;
    bool test_verbose = false, test_fundamental = false;
    char* test_args[] = {"program","-verbose","-fundamental","8"};
    user_input(test_argc=4,test_args,&test_N,&test_verbose, &test_fundamental);
    assert(test_N == 8);
    assert(test_verbose);
    assert(test_fundamental);

    
    solution* latest_solution = NULL;
    int test_size = 8;
    state test_state = init_state(test_size);
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
    // Add quens to the top left and bottom right corners and rotate it clockwise
    // This also provides us with the oppertunity to test both of the queen insertion functions.
    queen_adder_ptr(&test_state, 0, 0, test_size);
    test_state = queen_adder(test_state, (test_size-1), (test_size-1), test_size);

    assert(test_state.board[0][0] == QUEEN);
    assert(test_state.board[test_size-1][test_size-1] == QUEEN);
    assert(test_state.board[0][test_size-1] == QUEEN_COVERED);
    assert(test_state.board[0][test_size-1] == QUEEN_COVERED);


    test_state = rotate_clockwise(&test_state, test_size);

    // check these queens have moved to the top right and bottom left corners respectively
    assert(test_state.board[0][test_size-1] == QUEEN);
    assert(test_state.board[test_size-1][0] == QUEEN);
    assert(test_state.board[0][0] == QUEEN_COVERED);
    assert(test_state.board[test_size-1][test_size-1] == QUEEN_COVERED);

    // Same idea for the reflection. 
    test_state = reflection(&test_state, test_size);

    assert(test_state.board[0][test_size-1] == QUEEN_COVERED);
    assert(test_state.board[test_size-1][0] == QUEEN_COVERED);
    assert(test_state.board[0][0] == QUEEN);
    assert(test_state.board[test_size-1][test_size-1] == QUEEN);

    
   // Create a new state, add queens in the opposite corners and make sure
   // geometric_comparison() identifies them as related. (false)
    state new_test_state = init_state(test_size);
    new_test_state = queen_adder(new_test_state, 0, 0, test_size);
    new_test_state = queen_adder(new_test_state, (test_size-1), (test_size-1), test_size);

    assert(!geometric_comparison(&test_state, &new_test_state, test_size));
    
    // fundamental_finder() and recursion() produce the outputs of this script, so these were tested against
    // The known correct values found here: https://en.wikipedia.org/wiki/Eight_queens_puzzle

    // free_list() was tested using the sanatizer, no memory leaks were identified therefore this function
    // must be freeing the stacks in their entirety. 

    // verbose_output_loop() prints to screen, therefore this was tested via inspection. 

    // user_continue() direcrtly leads to program termination, so this was tested via command line. 





}


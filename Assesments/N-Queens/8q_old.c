#include "8q.h"

int main(int argc, char* argv[]){
    test();
    bool verbose = false;
    int N = 0;
    user_input(argc, argv, &N, &verbose);
    char board[MAX_GRID][MAX_GRID];
    char** ptr = (char**)board;

    init_board(ptr,N);
    state solution_space[MAX_SEARCH_SPACE];

}
/*
----------
USER INPUT
----------
*/
void user_input(int argc, char* argv[], int* N, bool* verbose){
    printf("Function");
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
        fprintf(stderr, "Numerical argument must be an integer between 1 and 10.\n");
        exit(EXIT_FAILURE);
    }

    else{
        if(!valid_number(argv[2])){
            fprintf(stderr, "Numerical argument must be an integer between 1 and 10.\n");
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
    if(atoi(val) <= 10 && atoi(val) >= 1){
        return true;
    }
    return false;
}

/*
--------------------
Unique Board Checker
--------------------
*/
/*
//BOTH OF THESE ARE UNTESTED!!!
bool unique_checker(state solution_space[MAX_SEARCH_SPACE], char board[MAX_GRID][MAX_GRID], int frontier){
    for(int i = 0;i<frontier;i++){
        if(grid_comparison(solution_space[i].grid,board){
            return false;
        }
    }
    return true;
}

bool grid_comparison(char board1[MAX_GRID][MAX_GRID], char board2[MAX_GRID][MAX_GRID], int size){
    for(int i = 0;i<size;i++){
        if(strcmp(board1[i],board2[i]){
            return false;
        }
    }
    return true;
}
*/
/*
-----------
QUEEN ADDER
-----------
*/

void queen_adder(state* old_position,int row_index, int col_index, int size){
    // Add a queen in coords given and, change all unexplored cells in range to explored, don't effect queen cells
    position->board[row_index][col_index] = QUEEN;
    row_explore(old_position, row_index, size);
    col_explore(old_position, col_index, size);
    diag_explore(old_position, row_index, col_index, size);

}

void row_explore(state* position, int row_index, int size){
    for(int col = 0;col<size; col++){
        if(position->board[row_index][col] == QUEEN_UNCOVERED){
            position->board[row_index][col] = QUEEN_COVERED;
        }
    }
}
void col_explore(state* position, int col_index, int size){
    for(int row = 0; row<size; row++){
        if(position->board[col_index][row] == QUEEN_UNCOVERED){
            position->board[col_index][row] = QUEEN_COVERED;
        }
    }
}
void diag_explore(state* position, int row_index, int col_index, int size){
    int size_index = size-1;
    for(int step = 1;step<size;step++){
        if((row_index+step) < size_index &&
           (col_index+step) < size_index &&
           position->board[row_index+step][col_index+step] == QUEEN_UNCOVERED){
            position->board[row_index+step][col_index+step] = QUEEN_COVERED;
        }
        if((row_index-step) > 0 &&
           (col_index-step) > 0 &&
           position->board[row_index-step][col_index-step] == QUEEN_UNCOVERED){
            position->board[row_index-step][col_index-step] = QUEEN_COVERED;
        }
        if((row_index+step) < size_index &&
           (col_index-step) > 0 &&
           position->board[row_index+step][col_index-step] == QUEEN_UNCOVERED){
            position->board[row_index+step][col_index-step] = QUEEN_COVERED;
        }
        if((row_index-step) > 0 &&
           (col_index+step) < size_index &&
           position->board[row_index-step][col_index+step] == QUEEN_UNCOVERED){
            position->board[row_index-step][col_index+step] = QUEEN_COVERED;
        }
    }
}

/*
---------------
Next Generation
---------------
pseudo:
inputs: solution space pointer, current index, current frontier, board size
process, looks at state at that index, generates new child states, asseses uniquness and adds to soution space if appropriate
returns: int, number of states added

for each cell
    if unexplored
        copy board over, add queen to square, recalculate it
        if unique
            add to solution_space
Functions:

- Adding queen to board effect
- Unique board in solution space (DONE)
- 2D board copy
- Add board to solution space
*/
/*
int next_gen(state* solution_space, int current_index, long current_frontier, int size){
    char temp_board[MAX_GRID][MAX_GRID];
// Going to be type errors using this in funtions w/ pointers ^^
    int additions = 0;
    for(int row = 0;row<size;row++{
        for(int col = 0;col<size;col++){
            if(solution_space[curren_index]->grid[row][col] == QUEEN_UNEXPLORED){
                board_copy(solution_space[current_index]->grid[row][col],temp_board);
                // ADD QUEEN FUNCTION on temp_board
                if(unique_checker(solution_space, temp_board, current_frontier)){
                    add_board(....);
                    additions++;
                }
            }
        }
    }
    return additions;
}

void board_copy(char* board_old, char* board_new, int size){
    for(int row = 0;row<size;row++){
        strcpy(board_new[row],board_old[row]);
    }
}
*/
/*
----------------
INITIALISE BOARD
----------------
*/
void init_board(char board[MAX_GRID][MAX_GRID], int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            board[row][col] = QUEEN_UNCOVERED;
        }
    }
}

void print_board(char** board, int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            printf("%c",board[row][col]);
        }
        printf("\n");
    }
}

/*
-------
TESTING
-------
*/
void test(){

    // First checks are making sure valid function stops bad inputs and
    // allows good ones
    assert(!valid_number("hello"));
    assert(!valid_number("123"));
    assert(!valid_number("10a"));
    assert(valid_number("5"));

    // Final user inpupt checks. Failuter messages already tested via program exits
    // Need to make sure valid inputs are allowed
    int test_N = 0, test_argc;
    bool test_verbose = false;

    char* test_args[] = {"program","8"};
    user_input(test_argc=2,test_args,&test_N,&test_verbose);
    printf("Size: %i, Verbose: %i", test_N, test_verbose);
    assert(test_N == 8);
    assert(!test_verbose);

    char* test_args_verbose[] = {"program","-verbose","8"};
    user_input(test_argc=3,test_args_verbose,&test_N,&test_verbose);
    printf("Size: %i, Verbose: %i", test_N, test_verbose);
    assert(test_N == 8);
    //assert(test_verbose);

    // Testing board initialisation (To a grid of uncovered squares)
    char test_board[MAX_GRID][MAX_GRID];
    char** test_ptr = (char**)test_board;
    init_board(test_ptr,test_N);
    for(int row = 0 ; row < test_N ; row++){
        for(int col = 0 ; col < test_N ; col++){
            assert(test_ptr[row][col] == QUEEN_UNCOVERED);
        }
    }

    // Test Queen Addition Functions
    char test_board2[MAX_GRID][MAX_GRID] = {{'O'}};
    char** ptr = (char**)test_board2;
    print_board(ptr,4);
}

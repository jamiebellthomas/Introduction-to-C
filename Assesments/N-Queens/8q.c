#include "8q.h"
int main(int argc, char* argv[]){
    test();


    bool verbose = false;
    int size = 0;
    user_input(argc, argv, &size, &verbose);

    state* solution_space = (state*)malloc(sizeof(state)*MAX_SEARCH_SPACE);
    if(solution_space == NULL){
        fprintf(stderr,"Memory Allocation Failed.\n");
         exit(EXIT_FAILURE);
    }
    
    long frontier = 1, index = 0, solution_counter = 0;
    state state_holder = init_state(size);
    solution_space[0] = state_holder;
    while(index<=frontier){
        next_gen(solution_space,&frontier, &index, size, 
                 &state_holder, verbose, &solution_counter);
    }
    printf("%li solutions\n", solution_counter);
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
------------------------------
INITIALISE/COPY/COMPARE STATES
------------------------------
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

void cpy_state(state old_state, state* new_state, int size){
    new_state->queens = old_state.queens;
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            new_state->board[row][col] = old_state.board[row][col];
        }
    }
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
    position->board[row_index][col_index] = QUEEN;
    row_explore(position, row_index, size);
    col_explore(position, col_index, size);
    diag_explore(position, row_index, col_index, size);

}


/*
---------------
NEXT GENERATION
---------------
*/

bool unique_state(state solution_space[MAX_SEARCH_SPACE], long frontier, state current_state, int size){
    for(int i = 0; i<frontier; i++){
        if(state_cmp(solution_space[i],current_state,size)){
            return false;
        }
    }
    return true;
}

void next_gen(state solution_space[MAX_SEARCH_SPACE], long* frontier, long* index, 
              int size, state* state_holder, bool verbose, long* solution_counter){
    cpy_state(solution_space[*index], state_holder, size);
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            if(state_holder->board[row][col] == QUEEN_UNCOVERED){
                queen_adder(state_holder, row, col, size); 
                (state_holder->queens)++;
                if(unique_state(solution_space,*frontier,*state_holder,size)){
                    solution_space[(int)(*frontier)] = *state_holder;
                    (*frontier)++;
                    if(state_holder->queens == size){
                        (*solution_counter)++;
                        if(verbose){
                            verbose_output(*state_holder, size);
                        }
                    }

                }
                cpy_state(solution_space[*index], state_holder, size);
            }
        }
    }
    (*index)++;
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

    // First checks are making sure valid_number only allows
    // numerical values from 1-10.
    assert(!valid_number("hello"));
    assert(!valid_number("123"));
    assert(!valid_number("10a"));
    assert(valid_number("5"));
    
    //Initialise a good set of non-verbose arguments and ensure
    // They are correctly translated to the relevant variable(s)
    int test_N = 0, test_argc;
    bool test_verbose = false;
    char* test_args[] = {"program","8"};
    user_input(test_argc=2,test_args,&test_N,&test_verbose);
    assert(test_N == 8);
    assert(!test_verbose);

    //Initialise a good set of verbose arguments and ensure
    // They are correctly translated to the relevant variable(s)
    char* test_args_verbose[] = {"program","-verbose","8"};
    user_input(test_argc=3,test_args_verbose,&test_N,&test_verbose);
    assert(test_N == 8);
    assert(test_verbose);
    // Bad arguments were tested via command line as they trigger a 
    // program exit.


    // Ensure the init_state function creates a state struct with an
    // empty board of the correct size. 
    state test_state = init_state(test_N);
    for(int row = 0 ; row < test_N ; row++){
        for(int col = 0 ; col < test_N ; col++){
            assert(test_state.board[row][col] == QUEEN_UNCOVERED);
        }
    }
    // Compare a state to itself and make sure they are marked as identical
    assert(state_cmp(test_state, test_state, test_N));

    test_state.board[0][0] = 'T';
    test_state.board[1][1] = 'E';
    test_state.board[2][2] = 'S';
    test_state.board[3][3] = 'T';
    //print_board(&test_state,test_N);

    
    state test_state_cpy = init_state(test_N);

    // Alter the original board, create a new board and ensure
    // these two boards are markes as different
    assert(!state_cmp(test_state, test_state_cpy, test_N));

    // Copy the old board to the new board and ensure these two boards are
    // now identical (this can be done with the new tested state_cmp function)
    cpy_state(test_state,&test_state_cpy,test_N);
    assert(state_cmp(test_state, test_state_cpy, test_N));


    // Insert a queen into the given index, apply each of the exploration
    // functions seperately, comparing the results with the known output. 
    int test_row = 4, test_col = 3;
    test_state.board[test_row][test_col] = QUEEN;
    row_explore(&test_state,test_row,test_N);
    assert(test_state.board[test_row][test_col] == QUEEN);
    for(int i=0;i<test_N;i++){
        if(i!=test_col){
            assert(test_state.board[test_row][i] == QUEEN_COVERED);
        }
    }

    col_explore(&test_state, test_col, test_N);
    assert(test_state.board[test_row][test_col] == QUEEN);
    for(int i=0;i<test_N;i++){
        if(i!=test_row){
            if(i == (test_row-1)){
                assert(test_state.board[i][test_col] == 'T');
            }
            else{
                assert(test_state.board[i][test_col] == QUEEN_COVERED);
            }
            
        }
        
    }

    test_state.board[1][0] = 'T';
    diag_explore(&test_state, test_row, test_col, test_N);
    
    state comparison_state = {.queens = 0,
                              .board = {{"TOOXOOOX"},
                                        {"TEOXOOXO"},
                                        {"OXSXOXOO"},
                                        {"OOXTXOOO"},
                                        {"XXXQXXXX"},
                                        {"OOXXXOOO"},
                                        {"OXOXOXOO"},
                                        {"XOOXOOXO"}}
    };
    assert(state_cmp(comparison_state, test_state, test_N));
    
    // Then apply the overall function that calls these 3 individual functions and
    // ensure this returns an identical result
    test_state_cpy.board[1][0] = 'T';
    queen_adder(&test_state_cpy,test_row,test_col,test_N);
    //print_board(&test_state_cpy,test_N);
    assert(state_cmp(comparison_state, test_state_cpy, test_N));


    // Initialise a dummy solution space with slightly varying boards within it
    state* test_solution_space = (state*)malloc(sizeof(state)*TEST_SEARCH_SPACE);
    for(int i = 1;i<TEST_SEARCH_SPACE;i++){
        test_solution_space[i] = init_state(test_N);
        test_solution_space[i].board[0][0] = (i-1)+'A';
    }
    
    // Initialise a new state which we know isn't in the dummy solution space
    // and a state that we know is in there
    // and verify the unique_state function can identify which one is contained within
    // the solution space and which is not. 
    state test_unique_state = init_state(test_N);
    test_unique_state.board[0][0] = TEST_SEARCH_SPACE+'A';
    state test_non_unique_state = init_state(test_N);
    test_non_unique_state.board[0][0] = 'A';
    assert(unique_state(test_solution_space, TEST_SEARCH_SPACE, test_unique_state, test_N));
    assert(!unique_state(test_solution_space, TEST_SEARCH_SPACE, test_non_unique_state, test_N));
    free(test_solution_space);


    // Initialise a new solution space, except this one will only have 1 black board at the start
    // (just like the real code will do)
    state* test_next_gen_space = (state*)malloc(sizeof(state)*TEST_SEARCH_SPACE);
    
    long test_frontier = 1, test_index = 0, test_solution_counter = 0;
    int test_size = 3;

    state test_state_holder = init_state(test_size);
    test_next_gen_space[0] = test_state_holder;

    // Call the next_gen function on this initial empty board and ensure what is returned is a series of boards
    // of length (size)^2 with each having a unique set of queen index coordinates. 
    next_gen(test_next_gen_space,&test_frontier, &test_index, test_size, 
             &test_state_holder, test_verbose, &test_solution_counter);

    assert(test_frontier == (test_size*test_size+1));
    int first_frontier = test_size*test_size+1;
    assert(test_index == 1);
    int test_counter = 1;
    for(int test_row = 0;test_row<test_size;test_row++){
        for(int test_col = 0;test_col<test_size;test_col++){
            assert(test_next_gen_space[test_counter].board[test_row][test_col] == QUEEN);
            test_counter++;

        }
    }
    // Run next_gen on the second entry and ensure the first value of the next generation is
    // the same as the known output. 
    next_gen(test_next_gen_space,&test_frontier, &test_index, test_size, 
             &test_state_holder, test_verbose, &test_solution_counter);


    state comparison_state_two = {.queens = 2,
                              .board = {{"QXX"},
                                        {"XXQ"},
                                        {"XXX"}}
    };
    assert(state_cmp(comparison_state_two, test_next_gen_space[first_frontier],test_size));

    free(test_next_gen_space);
}


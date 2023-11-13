#include "8q_2.h"
int main(int argc, char* argv[]){
    test();
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
----------------
INITIALISE BOARD
----------------
*/
void init_board(state* position, int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            position->board[row][col] = QUEEN_UNCOVERED;
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

    int test_N = 0, test_argc;
    bool test_verbose = false;

    char* test_args[] = {"program","8"};
    user_input(test_argc=2,test_args,&test_N,&test_verbose);
    //printf("Size: %i, Verbose: %i\n", test_N, test_verbose);
    assert(test_N == 8);
    assert(!test_verbose);

    char* test_args_verbose[] = {"program","-verbose","8"};
    user_input(test_argc=3,test_args_verbose,&test_N,&test_verbose);
    //printf("Size: %i, Verbose: %i\n", test_N, test_verbose);
    assert(test_N == 8);
    assert(test_verbose == true);

    state test_state = {.queens = 0,
                        .board = {{'\0'}}};
    init_board(&test_state,test_N);
    for(int row = 0 ; row < test_N ; row++){
        for(int col = 0 ; col < test_N ; col++){
            assert(test_state.board[row][col] == QUEEN_UNCOVERED);
        }
    }
    //print_board(&test_state,10);
    //print_board(&test_state,test_N);

    
    



    
    
    
   
}

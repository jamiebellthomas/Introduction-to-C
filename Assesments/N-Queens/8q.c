#include "8q.h"

int main(int argc, char* argv[]){
    test();
    bool verbose = false;
    int N = 0;
    user_input(argc, argv, &N, &verbose);
    char board[MAX_GRID][MAX_GRID];


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
void init_board(char* board, int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            board[row][col] = QUEEN_UNCOVERED;
        }
    }
}

void print_board(char* board, int size){
    for(int row = 0;row<size;row++){
        for(int col = 0;col<size;col++){
            printf("%s",board[row][col]);
        }
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
    int test_N = 0, argc;
    bool test_verbose = false;

    char* test_args[] = {"program","8"};
    user_input(argc=2,test_args,&test_N,&test_verbose);
    assert(test_N == 8);
    assert(!test_verbose);

    char* test_args_verbose[] = {"program","-verbose","8"};
    user_input(argc=3,test_args_verbose,&test_N,&test_verbose);
    assert(test_N == 8);
    assert(test_verbose);

    

}

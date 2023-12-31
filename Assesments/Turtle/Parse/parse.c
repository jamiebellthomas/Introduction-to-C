#include "parse.h"

Program* prog_init(void){

    Program* prog = (Program*)calloc(1, sizeof(Program));

    prog->array_len = MAXTOKENS;

    if(!prog){
        fprintf(stderr, "Error allocating program memory");
        exit(EXIT_FAILURE);
    }
    
    prog->word_array = (char**)calloc(MAXTOKENS,sizeof(char*));
    if(!prog->word_array){
        fprintf(stderr, "Error allocating row memory");
        exit(EXIT_FAILURE);
    }

    for(int row = 0; row<MAXTOKENS; row++){
        prog->word_array[row] = (char*)calloc(MAXTOKENLEN, sizeof(char));
        if(!prog->word_array[row]){
            fprintf(stderr, "Error allocating column memory");
            exit(EXIT_FAILURE);
        }
    }

    
    return prog;
}



void free_prog(Program* prog){
    
    for(int row = 0; row<prog->array_len; row++){
        free(prog->word_array[row]);
    }
    free(prog->word_array);
    free(prog);
}




bool valid_letter(Program* prog){
    // If string in this word is more than 1 long, more than a single
    // letter is present, return false.
    if(strlen(prog->word_array[prog->current_word]) != 1){
        return false;
    }


}


bool valid_variable(Program* prog){
    
}

bool valid_number(Program* prog){
    
}

bool varnum(Program* prog){
    
}

bool valid_word(Program* prog){
    
}

bool valid_item(Program* prog){
    
}

bool valid_op(Program* prog){
    
}



void test(void){
    Program* test_prog = prog_init();
    assert(!test_prog->current_word);
    assert(test_prog->array_len == MAXTOKENS);
    


    free_prog(test_prog);
}

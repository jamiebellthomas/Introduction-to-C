#include "specific.h"



bsa* bsa_init(void){

    bsa* init_bsa = (bsa*)malloc(sizeof(bsa));
    if(init_bsa == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    } 


    init_bsa->value_count=0;
    init_bsa->max_index=-1;
    init_bsa->row_array=(bsa_row*)malloc(BSA_ROWS*sizeof(bsa_row));

    for(int i = 0;i<BSA_ROWS;i++){
        init_bsa->row_array[i].row = NULL;
        init_bsa->row_array[i].value_count = 0;
    }

    return init_bsa;
}

bool bsa_free(bsa* b){
    for(int i = 0;i<BSA_ROWS;i++){
        if(b->row_array[i].row != NULL){
            free(b->row_array[i].row);
        }
    }

    free(b->row_array);
    free(b);
}


int pointer_idx(int idx){
    // This will take a given index and determine what row of the BSA it sits in
    int val = idx+1, row_idx = 0, range = 1;

    while(range<=val){
        row_idx++;
        range = range << 1;
    }

    // This loop intentially runs until it's overshot.
    // Therefore we need to backtrack 1 row
    row_idx-=1;

    if(row_idx>=BSA_ROWS){
        fprintf(stderr, "Index exceeds BSA bounds\n");
        exit(EXIT_FAILURE);
    }

    return row_idx;

}

void test(void){

    bsa* test_bsa = bsa_init();

    for(int i = 0;i<BSA_ROWS;i++){
        assert(test_bsa->row_array[i].row == NULL);
        assert(test_bsa->row_array[i].value_count == 0);
    }


    assert(pointer_idx(0) == 0);
    assert(pointer_idx(1) == 1);
    assert(pointer_idx(2) == 1);
    assert(pointer_idx(3) == 2);
    assert(pointer_idx(6) == 2);
    assert(pointer_idx(7) == 3);
    assert(pointer_idx(8) == 3);
    assert(pointer_idx(25) == 4);

    
}

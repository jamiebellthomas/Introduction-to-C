#include "specific.h"



bsa* bsa_init(void){

    bsa* init_bsa = (bsa*)malloc(sizeof(bsa));
    if(init_bsa == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    } 


    init_bsa->length=0;
    init_bsa->max_index=-1;
    init_bsa->pointer_array=(int**)malloc(BSA_ROWS*sizeof(int*));

    for(int i = 0;i<BSA_ROWS;i++){
        init_bsa->pointer_array[i] = NULL;
    }

    return init_bsa;
}

int pointer_idx(int idx){
    // This will take a given index and determine what row of the BSA it sits in
    int val = idx+1, row_idx = 0, range = 1;

    while(range<=val){
        row_idx++;
        range*=2;
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
    assert(pointer_idx(0) == 0);
    assert(pointer_idx(1) == 1);
    assert(pointer_idx(2) == 1);
    assert(pointer_idx(3) == 2);
    assert(pointer_idx(6) == 2);
    assert(pointer_idx(7) == 3);
    assert(pointer_idx(8) == 3);
    assert(pointer_idx(25) == 4);
}
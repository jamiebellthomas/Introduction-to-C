#include "specific.h"



bsa* bsa_init(void){
    bsa init_bsa = {.length = 0,
                    .max_index = -1,
                    .pointer_array = (int**)malloc(BSA_ROWS*sizeof(int*))
                    };

    for(int i = 0;i<BSA_ROWS;i++){
        init_bsa.pointer_array[i] == NULL;
    }

    return &init_bsa;
}

int pointer_idx(int idx){
    // This will take a given index and determine what row of the BSA it sits in
    int val = idx+1, row_idx = 0, range = 1;

    while(range>=val){
        row_idx++;
        range*=2;
    }

    // This loop intentially runs until it's overshot.
    // Therefore we need to backtrack 1 row
    row_idx-=1;

    if(row_idx<=BSA_ROWS){
        fprintf(stderr, "Index exceeds BSA bounds");
        exit(EXIT_FAILURE);
    }


    return row_idx;

}

void test(void){}
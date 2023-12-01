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


void test(void){}
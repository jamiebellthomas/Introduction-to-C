#include "specific.h"

int main(void){
    test();
}

/*
----------
INITIALISE
----------
*/
bsa* bsa_init(void){
    bsa* table = (bsa*)malloc(sizeof(bsa));
    if(!table){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    } 
    // We have initialised a 1D hash table with O(1), with all 
    // values set to zero (no initialising loops)
   
    table->array = (int*)calloc(INIT_SIZE, sizeof(int));
    table->occupied = (bool*)calloc(INIT_SIZE, sizeof(bool));

    if(!(table->array) || !(table->occupied)){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    } 

    table->max_index = -1;
    table->length = INIT_SIZE;
    table->elements = 0;

    
    return table;
}
/*
----
FREE
----
*/
bool bsa_free(bsa* b){
    free(b->array);
    free(b->occupied);
    free(b);
    return true;
}

int hash_function(bsa* b, int d){

    int hash = d%(b->length);
    return hash;
}

/*
We need functions to:
set
get
delete
maxindex
foreach

we'll also need a reallocate function, this will sit in the set function
*/

/*
---
GET
---
*/
int* bsa_get(bsa* b, int indx){
    if(!(b->occupied[indx])){
        return NULL;
    }

    return &(b->array[indx]);
}

/*
----------
REALLOCATE
----------
*/
bool bsa_reallocate(bsa* b){

}

/*
---
SET
---
*/

bool bsa_set(bsa* b, int indx, int d){

    indx = hash_function(b, d);

    if(b->occupied[indx]){
        assert(1);
    }


}


void test(void){

    bsa* test_table  = table_init();
    for(int i = 0; i<INIT_SIZE; i++){
        assert(!(test_table->array[i]));
        assert(!(test_table->occupied[i]));
    }
    assert(test_table->max_index == -1);
    assert(test_table->length == INIT_SIZE);
    assert(test_table->elements == 0);

    assert(hash_function(test_table, 3000) == 0);
    assert(hash_function(test_table, 3100) == 100);


    table_free(test_table);
}





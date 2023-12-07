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

int hash_function(int len, int d){

    int hash = d%(len);
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
    if((indx >= b->length) || !(b->occupied[indx])){
        return NULL;
    }

    return &(b->array[indx]);
}

/*
----------
REALLOCATE
----------
*/
// This changes the size of the hash table, returns true if ALL values were
// reallocated sucessfully, and false if not.
bool bsa_reallocate(bsa* b, int new_size){
    // THESE NEEDS MODULARISING
    int idx, max_idx = 0;
    
    
    int* new_array = (int*)calloc(new_size, sizeof(int));
    bool* new_occupied = (bool*)calloc(new_size, sizeof(bool));

    for(int i = 0; i<b->length; i++){
        if(bsa_get(b, i)){
            idx = hash_function(new_size, b->array[i]);
            // If this config doesnt work, return and pick a new size.
            if(new_occupied[idx]){
                free(new_array);
                free(new_occupied);
                return false;
            }

            if(idx > max_idx){
                max_idx = idx;
            }
            new_array[idx] = b->array[i];
            new_occupied[idx] = true;
        }
    }
    free(b->array);
    free(b->occupied);
    b->array = new_array;
    b->occupied = new_occupied;
    b->max_index = max_idx;
    b->length = new_size;

    

    return true;




}
// This function will use bsa_reallocate to find the closest
// feasible size above a given size (new_size)
void bsa_resize(bsa* b, int new_size){
    bool feasible = false;

    do
    {
        // Increment new size until feasible configuration found
        new_size++;
        feasible = bsa_reallocate(b, new_size);
    } while (!feasible);

}

/*
---
SET
---
*/

bool bsa_set(bsa* b, int indx, int d){

    bool used;

    do
    {
        indx = hash_function(b->length, d);
        used = b->occupied[indx];
        if(used){
            bsa_resize(b, b->length);
        }
    } while(used);


    b->array[indx] = d;
    b->occupied[indx] = true;
    (b->elements)++;

    if(indx>b->max_index){
        b->max_index = indx;
    }

    float load_factor = (float)(b->elements)/(float)b->length;
    if(load_factor>UPPER_LOAD_FACTOR){
        bsa_resize(b, (((b->length)*RESIZE_FACTOR)-1));
    }



    return true;


}


void test(void){

    bsa* test_table  = bsa_init();
    for(int i = 0; i<INIT_SIZE; i++){
        assert(!(test_table->array[i]));
        assert(!(test_table->occupied[i]));
    }
    assert(test_table->max_index == -1);
    assert(test_table->length == INIT_SIZE);
    assert(test_table->elements == 0);

    assert(hash_function(INIT_SIZE, 3000) == 0);
    assert(hash_function(INIT_SIZE, 3100) == 100);

    test_table->array[1] = 1;
    test_table->occupied[1] = true;
    assert(bsa_get(test_table, 1));
    assert(*(bsa_get(test_table, 1)) == 1);
    assert(!(bsa_get(test_table, 0)));


    // Make table bigger
    bsa_reallocate(test_table, INIT_SIZE*2);
    assert(bsa_get(test_table, 1));
    assert(*(bsa_get(test_table, 1)) == 1);
    assert(!(bsa_get(test_table, 0)));
    assert(test_table->length == INIT_SIZE*2);
    test_table->array[1500] = 1500;
    test_table->occupied[1500] = true;
    assert(bsa_get(test_table, 1500));
    assert(*(bsa_get(test_table, 1500)) == 1500);
    assert(!(bsa_get(test_table, 1499)));

    // Make table smaller (original size)
    bsa_reallocate(test_table, INIT_SIZE);
    assert(bsa_get(test_table, 1));
    assert(*(bsa_get(test_table, 1)) == 1);
    assert(!(bsa_get(test_table, 0)));
    assert(test_table->length == INIT_SIZE);
    //value 1500 should now be in cell 500...?
    assert(bsa_get(test_table, 500));
    assert(*(bsa_get(test_table, 500)) == 1500);
    assert(!(bsa_get(test_table, 499)));
    // Check out-of-bounds index
    assert(!(bsa_get(test_table, (INIT_SIZE))));
    // Resize should make it only 1 longer therefore
    //index 1000 (INIT_SIZE) should now be set to false.
    // with no sanitizer errors.
    bsa_resize(test_table, test_table->length);
    assert(!test_table->occupied[INIT_SIZE]);

    bsa_set(test_table, 0, 1751);
    assert(bsa_get(test_table, 750));
    assert(*(bsa_get(test_table, 750)) == 1751);
    assert(test_table->max_index == 750);
    assert(test_table->elements == 1);

    // Lets make sure this array can find the max_index again
    bsa_reallocate(test_table, INIT_SIZE*2);
    assert(test_table->max_index == 1751);
    assert(test_table->length == 2000);
    assert(test_table->elements == 1);
    












    bsa_free(test_table);
}





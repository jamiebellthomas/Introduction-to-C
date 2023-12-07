#include "specific.h"

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

    table->max_index = UNAVAILABLE;
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
init DONE + TESTED
free DONE + TESTED
has function DONE + TESTED
set DONE + TESTED
get DONE + TESTED
delete DONE + TESTED
maxindex DONE + TESTED
foreach DONE + TESTED

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
// feasible size ABOVE a given size (new_size)
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
        //printf("\n");
        //printf("Value: %i\n", d);
        //printf("Hash Index: %i\n", indx);
        used = b->occupied[indx];

        
        if(used){
            
            indx = neighbour_availability(b, indx);
            used = b->occupied[indx];
            //printf("Used Index: %i\n", indx);
            if(indx == UNAVAILABLE){
                //printf("Resizing (set)\n");
                bsa_resize(b, b->length);
            }
            
        }
        //printf("\n");
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

/*
---------
MAX INDEX
---------
*/

int bsa_maxindex(bsa* b){
    if(!b){
        return UNAVAILABLE;
    }

    return b->max_index;
}

/*
------
DELETE
------
*/

void next_maxindex(bsa* b, int idx){

    do{
        idx--;
    } while (!(bsa_get(b, idx)) &&
        idx >= 0);

    b->max_index = idx;
}

bool bsa_delete(bsa* b, int indx){

    indx = hash_function(b->length, indx);

    if(!(bsa_get(b,indx))){
        return false;
    }

    b->occupied[indx] = false;
    (b->elements)--;
    
    if(b->elements == 0){
        b->max_index = UNAVAILABLE;
        return true;
    }

    if(indx == b->max_index){
        next_maxindex(b,indx);
    }

    return true;


    

    
}

/*
--------
FOR EACH
--------
*/

void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){

    if(!b || !func){
        return;
    }
    int* val;
    for(int i = 0; i <= b->max_index; i++){
        val = bsa_get(b, i);
        if(val){
            func(val, acc);
        }          
    }
}

void count_elem(int* p, int* n){
    (*n)++;
    (*p)=2;
}

/*
---------------
NEIGHBOUR CHECK
---------------
*/
/*
This function goes +-3 either side of an index, if/when
it finds an avaiable cell it returns its index
If it doesnt find one, it returns -1
*/
int neighbour_availability(bsa* b, int indx){

    for(int i = 1; i<=NEIGHBOURHOOD; i++){
        if(((indx+i) < b->length) && !(b->occupied[indx+i])){
            return indx+1;
        }

        if(((indx-i) >= 0) && !(b->occupied[indx-i])){
            return indx-1;
        }
    }

    return UNAVAILABLE;
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

    assert(bsa_maxindex(test_table) == 1751);
    // Manually update the element count as the first 2
    // elements weren't added via bsa_set().
    test_table->elements = 3;
    bsa_delete(test_table, test_table->max_index);
    assert(test_table->elements == 2);
    assert(test_table->max_index == 1500);

    int acc = 0;
    // count_elem() is trivial, no need to test.
    bsa_foreach(count_elem, test_table, &acc);

    assert(acc = test_table->elements);
    assert(test_table->array[1] == 
           test_table->array[test_table->max_index]);
           
    // Tried testing against sieve, fibmemo and isfactoria,
    // the last 2 put non-unique values into the list,
    // this triggers an infinite loop in bsa_set with current
    // implementation. 

    // Going to set up a neighbours system

    assert(neighbour_availability(test_table, 1) == 2);
    


    bsa_free(test_table);
}





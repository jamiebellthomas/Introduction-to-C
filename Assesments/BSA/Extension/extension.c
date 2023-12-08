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
   
    table->array = (bsa_cell*)calloc(INIT_SIZE, sizeof(bsa_cell));
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
---
GET
---
*/
int* bsa_get(bsa* b, int indx){

    int hash_index = hash_function(b->length, indx);

    if(!(b->occupied[hash_index])){
        return NULL;
    }

    return &(b->array[hash_index].value);
}

/*
----------
REALLOCATE
----------
*/
// This changes the size of the hash table, returns true if ALL values were
// reallocated sucessfully, and false if not.
bool bsa_reallocate(bsa* b, int new_size){

    printf("Realloc function call (%i)\n", new_size);
    int idx, max_idx = 0;
    
    
    bsa_cell* new_array = (bsa_cell*)calloc(new_size, sizeof(bsa_cell));
    bool* new_occupied = (bool*)calloc(new_size, sizeof(bool));

    for(int i = 0; i<b->length; i++){
        if(bsa_get(b, i)){
            idx = hash_function(new_size, b->array[i].original_index);
            // If this config doesnt work, return and pick a new size.
            if(new_occupied[idx]){
                idx = neighbour_availability(b, idx);
                if(idx == -1){
                    printf("Reallocation Failed (%i)\n", new_size);
                    free(new_array);
                    free(new_occupied);
                    return false;
                }
                
            }

            if(idx > max_idx){
                max_idx = idx;
            }
            new_array[idx].value = b->array[i].value;
            new_array[idx].original_index = b->array[i].original_index;   
            new_occupied[idx] = true;
        }
    }
    printf("Reallocation Successful (%i)\n", new_size);
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
        // this isnt accounting for duplicate inputs 
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
    int hash;

    do
    {
        hash = hash_function(b->length, indx);

        used = b->occupied[hash];

        
        if(used){
            
            hash = neighbour_availability(b, hash);
            
            if(hash == UNAVAILABLE){
                printf("No avaialble cell.\n");
                bsa_resize(b, b->length);
                hash = neighbour_availability(b, hash);
            }
            used = b->occupied[hash];
            
        }
        //printf("\n");
    } while(used);


    b->array[hash].value = d;
    b->array[hash].original_index = indx;
    b->occupied[hash] = true;
    (b->elements)++;

    if(hash>b->max_index){
        b->max_index = hash;
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
        assert(!(test_table->array[i].value));
        assert(!(test_table->array[i].original_index));
        assert(!(test_table->occupied[i]));
    }
    assert(test_table->max_index == -1);
    assert(test_table->length == INIT_SIZE);
    assert(test_table->elements == 0);

    assert(hash_function(INIT_SIZE, INIT_SIZE) == 0);
    assert(hash_function(INIT_SIZE, (INIT_SIZE+100)) == 
          (INIT_SIZE+100)%INIT_SIZE);

    test_table->array[1].value = 1;
    test_table->array[1].original_index = 1;
    test_table->occupied[1] = true;
    assert(bsa_get(test_table, 1));
    assert(*(bsa_get(test_table, 1)) == 1);
    assert(!(bsa_get(test_table, 0)));


    // Make table bigger
    bsa_reallocate(test_table, 2000);
    assert(bsa_get(test_table, 1));
    assert(*(bsa_get(test_table, 1)) == 1);
    assert(!(bsa_get(test_table, 0)));
    assert(test_table->length == 2000);
    test_table->array[1500].value = 1500;
    test_table->array[1500].original_index = 1500;
    test_table->occupied[1500] = true;
    assert(bsa_get(test_table, 1500));
    assert(*(bsa_get(test_table, 1500)) == 1500);
    assert(!(bsa_get(test_table, 1499)));

    // Make table smaller & see if hashing updates
    bsa_reallocate(test_table, 1000);
    assert(bsa_get(test_table, 1));
    assert(*(bsa_get(test_table, 1)) == 1);
    assert(!(bsa_get(test_table, 0)));
    assert(test_table->length == 1000);
    //value 1500 should now be in cell 500...?
    assert(bsa_get(test_table, 500));
    assert(*(bsa_get(test_table, 500)) == 1500);
    assert(!(bsa_get(test_table, 499)));
    // Check out-of-bounds index
    assert(!(bsa_get(test_table, (1000))));
    // Resize should make it only 1 longer therefore
    //index 1000 (INIT_SIZE) should now be set to false.
    // with no sanitizer errors.
    bsa_resize(test_table, test_table->length);
    assert(!test_table->occupied[1000]);

    bsa_set(test_table, 1751, 1751);
    assert(bsa_get(test_table, 750));
    assert(*(bsa_get(test_table, 750)) == 1751);
    assert(test_table->max_index == 750);
    assert(test_table->elements == 1);

    // Lets make sure this array can find the max_index again
    bsa_reallocate(test_table, 2000);
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
    assert(test_table->array[1].value == 
           test_table->array[test_table->max_index].value);
           
    // Tried testing against sieve, fibmemo and isfactoria,
    // the last 2 put non-unique values into the list,
    // this triggers an infinite loop in bsa_set with current
    // implementation. 

    // Going to set up a neighbours system

    assert(neighbour_availability(test_table, 1) == 2);
    


    bsa_free(test_table);
}





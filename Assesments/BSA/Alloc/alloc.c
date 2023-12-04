#include "specific.h"

/*
--------------
INITIALISATION
--------------
*/

bsa* bsa_init(void){

    bsa* init_bsa = (bsa*)malloc(sizeof(bsa));
    if(init_bsa == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    } 


    init_bsa->value_count=0;
    init_bsa->max_index=UNUSED;
    init_bsa->row_array=(bsa_row*)malloc(BSA_ROWS*sizeof(bsa_row));


    if(init_bsa->row_array == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    } 

    for(int i = 0;i<BSA_ROWS;i++){
        init_bsa->row_array[i].row = NULL;
        init_bsa->row_array[i].value_count = 0;
    }

    return init_bsa;
}

/*
-----------
FREE MEMORY
-----------
*/

bool bsa_free(bsa* b){
    for(int i = 0;i<BSA_ROWS;i++){
        if(b->row_array[i].row != NULL){
            free(b->row_array[i].row);
        }
    }

    free(b->row_array);
    free(b);

    return true;
}

/*
----------
SET VALUES
----------
*/
bool bsa_set(bsa* b, int indx, int d){

    if(d == UNUSED){
        bsa_delete(b, indx);
        return true;
    }

    int row_idx = pointer_index(indx);
    if(row_idx>=BSA_ROWS){
        fprintf(stderr, "Index exceeds BSA bounds\n");
        return false;
    }

    if(b->row_array[row_idx].row == NULL){
        b->row_array[row_idx].row = (int*)calloc((1 << row_idx),sizeof(int));
        for(int i = 0; i <= ((1 << row_idx)-1); i++){
            b->row_array[row_idx].row[i] = UNUSED;
        }
        if(b->row_array[row_idx].row == NULL){
            fprintf(stderr, "Memory allocation failed.\n");
            bsa_free(b);
            exit(EXIT_FAILURE);
        }
    }

    int col_idx = col_index(indx);

    if(b->row_array[row_idx].row[col_idx] == UNUSED){
        (b->row_array[row_idx].value_count)++;
        (b->value_count)++;
    }

    if(indx > b->max_index){
        b->max_index = indx;
    }

    b->row_array[row_idx].row[col_idx] = d;


    return true;

}


/*
----------
MAX INDEX
----------
*/
int bsa_maxindex(bsa* b){

    if(b == NULL){
        return UNUSED;
    }
    return b->max_index;
}

/*
----------
GET VALUES
----------
*/

int* bsa_get(bsa* b, int indx){

    int row_idx = pointer_index(indx), col_idx = col_index(indx);

    if(!used_cell(b, row_idx, col_idx)){
        return NULL;
    }
    
    return &(b->row_array[row_idx].row[col_idx]);
}

/*
-------------
DELETE VALUES
-------------
*/



bool bsa_delete(bsa* b, int indx){

    int row_idx = pointer_index(indx), col_idx = col_index(indx);

    if(!used_cell(b, row_idx, col_idx)){
        return false;
    }
    // At this point we know the cell is in use.
    // Set value to zero and local values count.
    b->row_array[row_idx].row[col_idx] = UNUSED;
    (b->row_array[row_idx].value_count)--;

    // If the row is now empty, free the memory.
    // Reset pointer to NULL. (Marked for reallocation)
    if(b->row_array[row_idx].value_count == 0){
        free(b->row_array[row_idx].row);
        b->row_array[row_idx].row = NULL;
    }

    // Decrement values in array, if there is nothing in the array
    // reset max index to -1 (UNUSED) and return
    (b->value_count)--;
    if(b->value_count == 0){
        b->max_index = UNUSED;
        return true;
    }

    // If there are still values in the array we need to
    // determine the new max_index
    // go back 1-by-1 until we find the next value
    
    // If the array was empty max index would've already been set to 1
    // so 

    do{

        indx--;
        row_idx = pointer_index(indx);
        col_idx = col_index(indx);
    
    } while (!(used_cell(b, row_idx, col_idx)) &&
             indx >= 0);

    b->max_index = indx;

    return true;

}
/*
-------------
BSA to string
-------------
*/
// Returns stringified version of structure
// Each row has its elements printed between {}, up to the maximum index.
// Rows after the maximum index are ignored.
bool bsa_tostring(bsa* b, char* str){

    if(b == NULL){
        return false;
    }

    str[0] = '\0';
    int max_row = pointer_index(b->max_index), global_index, added;

    for(int i = 0; i <= max_row; i++){
        strcat(str, "{");

        for(int j = 0; j <= ((1 << i)-1); j++){
            added = 0;
            if(used_cell(b, i, j)){
                global_index = ((1 << i)-1) + j;
                // Add a little conditional that adds a space
                // if there is more than one entry in a row
                if(added != 0){
                    strcat(str, " ");
                }
                snprintf((str + strlen(str)), (MAX_STRING - strlen(str)), "[%i]=%i", global_index, b->row_array[i].row[j]);
                added++;
            }
        }
        strcat(str, "}");


    }
    return true;
}

/*
---------------------
ADDITIONAL FUNCTIONS
---------------------
*/


int pointer_index(int idx){
    // This will take a given index and determine what row of the BSA it sits in
    int val = idx+1, row_idx = 0, range = 1;

    while(range<=val){
        row_idx++;
        range = range << 1;
    }

    // This loop intentially runs until it's overshot.
    // Therefore we need to backtrack 1 row
    row_idx-=1;

    return row_idx;

}

int col_index(int idx){
    int row_idx = pointer_index(idx);
    // col index = global index - start of row index
    int col_idx = idx - ((1 << row_idx)-1);

    return col_idx;
}

bool used_cell(bsa* b, int row_idx, int col_idx){

    if(b->row_array[row_idx].value_count == 0 || 
       b->row_array[row_idx].row[col_idx] == UNUSED ||
       row_idx >= BSA_ROWS){
        return false;
    }

    return true;

}
/*
-------
TESTING
-------
*/

void test(void){

    bsa* test_bsa = bsa_init();

    for(int i = 0;i<BSA_ROWS;i++){
        assert(test_bsa->row_array[i].row == NULL);
        assert(test_bsa->row_array[i].value_count == 0);
    }

    assert(pointer_index(0) == 0);
    assert(pointer_index(1) == 1);
    assert(pointer_index(2) == 1);
    assert(pointer_index(3) == 2);
    assert(pointer_index(6) == 2);
    assert(pointer_index(7) == 3);
    assert(pointer_index(25) == 4);

    assert(col_index(1) == 0);
    assert(col_index(9) == 2);
    assert(col_index(14) == 7);


    // Set some values
    assert(bsa_set(test_bsa, 0, 4));
    assert(bsa_maxindex(test_bsa)==0);
    assert(test_bsa->row_array[0].row[0] == 4);
    assert(test_bsa->row_array[0].value_count == 1);
   
    assert(bsa_set(test_bsa, 15, 15));
    assert(test_bsa->row_array[4].row[0] == 15);
    assert(test_bsa->row_array[4].value_count == 1);


    assert(test_bsa->value_count == 2);
    assert(bsa_maxindex(test_bsa) == 15);

    int test_row = pointer_index(15), test_col = col_index(15);
    assert(used_cell(test_bsa, test_row, test_col));
    test_row = pointer_index(14); 
    test_col = col_index(14);
    assert(!used_cell(test_bsa, test_row, test_col));

    assert(bsa_get(test_bsa, 0));
    assert(bsa_get(test_bsa, 15));
    assert(*(bsa_get(test_bsa, 0)) == 4);
    assert(*(bsa_get(test_bsa, 15)) == 15);
    assert((bsa_get(test_bsa, 1)) == NULL);
    assert((bsa_get(test_bsa, 14)) == NULL);

    // Remove index 15 and make sure everything 
    // is in check
    bsa_delete(test_bsa, 15);
    // NULL pointer returned to this index
    assert(bsa_get(test_bsa, 15) == NULL);
    // New max value is index 0
    assert(test_bsa->max_index == 0);
    // One value fewer
    assert(test_bsa->value_count == 1);
    // Row is now empty ...
    assert(test_bsa->row_array[4].value_count == 0);
    // ... Therefore no memory stored here.
    assert(test_bsa->row_array[4].row == NULL);

    // Same procedure for the remaining value
    bsa_delete(test_bsa, 0);
    // Now we need to make sure max index is reset to unused.
    assert(bsa_get(test_bsa, 15) == NULL);
    assert(test_bsa->max_index ==UNUSED);
    assert(test_bsa->value_count == 0);
    assert(test_bsa->row_array[0].value_count == 0);
    assert(test_bsa->row_array[0].row == NULL);

    // Test that setting the last active cell to unused sets max_index
    // to -1 (UNUSED)
    bsa_set(test_bsa, 0, 1);
    assert(test_bsa->max_index == 0);
    bsa_set(test_bsa, 0, UNUSED);
 


    assert(test_bsa->max_index ==UNUSED);
    // Running this with a sanitizer proves it has
    // freed up all memory.
    bsa_free(test_bsa);

    
}

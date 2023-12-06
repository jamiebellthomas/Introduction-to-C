#include "specific.h"

/*
--------------
INITIALISATION
--------------
*/

bsa* bsa_init(void){

    bsa* init_bsa = (bsa*)malloc(sizeof(bsa));
    if(!init_bsa){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    } 

    init_bsa->value_count=0;
    init_bsa->max_index=UNUSED;
    init_bsa->row_array=(bsa_row*)malloc(BSA_ROWS*sizeof(bsa_row));

    if(!(init_bsa->row_array)){
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
        if(b->row_array[i].row){
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

    int row_idx = pointer_index(indx);

    if(row_idx>=BSA_ROWS){
        fprintf(stderr, "Index exceeds BSA bounds\n");
        return false;
    }

    if(!(b->row_array[row_idx].row)){
        bsa_row_create(b, row_idx);
    }

    int col_idx = col_index(indx);

    bsa_append(b, indx, row_idx, col_idx, d);
    
    return true;

}


/*
----------
MAX INDEX
----------
*/
int bsa_maxindex(bsa* b){

    if(!b){
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
    
    return &(b->row_array[row_idx].row[col_idx].value);
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
    // Set value to unused and decrement local values count.

    if(bsa_remove(b, row_idx, col_idx)){
        // If this returns true, array is empty and
        // we don't can return true here.
        return true;
    }
   

    // If there are still values in the array we need to
    // determine the new max_index
    // go back 1-by-1 until we find the next value
    
    // If the array was empty max index would've already been set to 1
    // so 
    if(indx == b->max_index){
        next_maxindex(b, indx);
        }

    return true;

}
/*
-------------
BSA TO STRING
-------------
*/
// Returns stringified version of structure
// Each row has its elements printed between {}, up to the maximum index.
// Rows after the maximum index are ignored.
bool bsa_tostring(bsa* b, char* str){

    if(!b){
        return false;
    }
    // Reset string by setting first char to null.
    str[0] = '\0';
    int max_row = pointer_index(b->max_index);
    // max_row tells us how many sets of curly braces we'll need,
    // so this'll be the range of our loop

    for(int i = 0; i <= max_row; i++){
        row_str(b, str, i);
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

    // If idx = -1 (unused), returned value is -1, also unused
    return row_idx;

}

int col_index(int idx){
    int row_idx = pointer_index(idx);
    // col index = global index - start of row index
    int col_idx = idx - ((1 << row_idx)-1);

    return col_idx;
}

void bsa_row_create(bsa* b, int row_idx){
    b->row_array[row_idx].row = (bsa_cell*)calloc((1 << row_idx),sizeof(bsa_cell));
    for(int i = 0; i <= ((1 << row_idx)-1); i++){
        b->row_array[row_idx].row[i].set = false;
    }
    if(!(b->row_array[row_idx].row)){
        fprintf(stderr, "Memory allocation failed.\n");
        bsa_free(b);
        exit(EXIT_FAILURE);
    }
}

void bsa_row_free(bsa* b, int row_idx){
    // Free row memory
    free(b->row_array[row_idx].row);
    // Set row pointer to NULL (marked for reallocation)
    b->row_array[row_idx].row = NULL;
}

void bsa_append(bsa* b, int idx, int row_idx, int col_idx, int d){
    // If the current cell isn't set, set it and add to the respective values
    if(!(b->row_array[row_idx].row[col_idx].set)){
        (b->row_array[row_idx].value_count)++;
        (b->value_count)++;
        b->row_array[row_idx].row[col_idx].set = true;
    }
    // If the new index is greater than the current max - update.
    if(idx > b->max_index){
        b->max_index = idx;
    }
    // Finally, set the value. 
    b->row_array[row_idx].row[col_idx].value = d;
}

bool bsa_remove(bsa* b, int row_idx, int col_idx){
    // At this point we know the cell is in use... 

    // Set boolean to false and decrement no 
    // of values in the row
     b->row_array[row_idx].row[col_idx].set = false;
    (b->row_array[row_idx].value_count)--;

    // If the row is now empty, free the memory.
    // Reset pointer to NULL. (Marked for reallocation)
    if(b->row_array[row_idx].value_count == 0){
        bsa_row_free(b, row_idx);
    }

    // Decrement values in array, if there is nothing in 
    // the array reset max index to -1 (UNUSED) and return
    (b->value_count)--;
    if(b->value_count == 0){
        b->max_index = UNUSED;
        // reutrn true if BSA is now empty.
        return true;
    }
    return false;
}

bool used_cell(bsa* b, int row_idx, int col_idx){

    if(b->row_array[row_idx].value_count == 0 || 
       !(b->row_array[row_idx].row[col_idx].set) ||
       row_idx >= BSA_ROWS){
        return false;
    }
    return true;
}

void next_maxindex(bsa* b, int idx){
    int row_idx = pointer_index(idx), col_idx = col_index(idx);

    do{
        idx--;
        row_idx = pointer_index(idx);
        col_idx = col_index(idx);
    } while (!(used_cell(b, row_idx, col_idx)) &&
        idx >= 0);

    b->max_index = idx;


}

void row_str(bsa* b, char* str, int row){
    strcat(str, "{");
    int added = 0, global_index;
    // Next loop is the range of indicies in a given row
    for(int i = 0; i <= ((1 << row)-1); i++){
        // If the cell is in use, append it to the string
        if(used_cell(b, row, i)){
            global_index = ((1 << row)-1) + i;
            // Add a little conditional that adds a space
            // if there is more than one entry in a row
            if(added != 0){
                strcat(str, " ");
            }
            snprintf((str + strlen(str)), (MAX_STRING - strlen(str)), 
                    "[%i]=%i", global_index, b->row_array[row].row[i].value);
            added++;
        }
    }
    strcat(str, "}");
}

void count_elem(int* p, int* n){
    (*n)++;
    (*p)=2;
}

/*
-------
TESTING
-------
*/

void test(void){

    bsa* test_bsa = bsa_init();
    // Test initial column vector of pointers initialised
    // succesfully (all NULL and value counter = 0)
    for(int i = 0;i<BSA_ROWS;i++){
        assert(!(test_bsa->row_array[i].row));
        assert(test_bsa->row_array[i].value_count == 0);
    }

    //  Test that global -> row and column index
    // calculators are correct
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

    // Create and remove row tests.

    bsa_row_create(test_bsa, 0);
    assert(test_bsa->row_array[0].row[0].set == false);
    bsa_row_free(test_bsa, 0);
    assert(test_bsa->row_array[0].row == NULL);

    // Add and remove values to specific row and column
    // indicies
    // Create a row, add 2 values to it
    // remove one and make sure removing 1 sets the set
    // flag to false.
    bsa_row_create(test_bsa, 1);
    bsa_append(test_bsa, 1, 1, 0, 5);
    assert(test_bsa->row_array[1].row[0].value == 5);
    assert(test_bsa->row_array[1].row[0].set == true);
    bsa_append(test_bsa, 1, 1, 1, 5);

    bsa_remove(test_bsa, 1, 0);
    assert(test_bsa->row_array[1].row[0].set == false);
    bsa_remove(test_bsa, 1, 1);
    assert(test_bsa->max_index == UNUSED);

    // Set some values
    assert(bsa_set(test_bsa, 0, 4));
    assert(bsa_maxindex(test_bsa)==0);
    assert(test_bsa->row_array[0].row[0].value == 4);
    assert(test_bsa->row_array[0].row[0].set == true);
    assert(test_bsa->row_array[0].value_count == 1);
   
    assert(bsa_set(test_bsa, 15, 15));
    assert(test_bsa->row_array[4].row[0].value == 15);
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
    assert(!(bsa_get(test_bsa, 1)));
    assert(!(bsa_get(test_bsa, 14)));

    // Make sure we can find the next used index before making
    // deletion function
    assert(bsa_maxindex(test_bsa) == 15);
    next_maxindex(test_bsa, test_bsa->max_index);
    assert(bsa_maxindex(test_bsa) == 0);

    test_bsa->max_index = 15;

    // Remove index 15 and make sure everything 
    // is in check
    bsa_delete(test_bsa, 15);
    // NULL pointer returned to this index
    assert(!(bsa_get(test_bsa, 15)));
    // New max value is index 0
    assert(test_bsa->max_index == 0);
    // One value fewer
    assert(test_bsa->value_count == 1);
    // Row is now empty ...
    assert(test_bsa->row_array[4].value_count == 0);
    // ... Therefore no memory stored here.
    assert(!(test_bsa->row_array[4].row));

    // Same procedure for the remaining value
    bsa_delete(test_bsa, 0);
    // Now we need to make sure max index is reset to unused.
    assert(!(bsa_get(test_bsa, 15)));
    assert(test_bsa->max_index == UNUSED);
    assert(test_bsa->value_count == 0);
    assert(test_bsa->row_array[0].value_count == 0);
    assert(!(test_bsa->row_array[0].row));

    char test_str[MAX_STRING] = "";
    bsa_set(test_bsa, 1, 1);
    row_str(test_bsa, test_str, 1);
    assert(!strcmp(test_str, "{[1]=1}"));
    test_str[0] = '\0';
    bsa_set(test_bsa, 2, 1);
    row_str(test_bsa, test_str, 1);
    assert(!strcmp(test_str, "{[1]=1 [2]=1}"));
    test_str[0] = '\0';
    bsa_tostring(test_bsa, test_str);
    assert(!strcmp("{}{[1]=1 [2]=1}", test_str));

    int acc = 0;
    // count_elem() is trivial, no need to test.
    bsa_foreach(count_elem, test_bsa, &acc);
    assert(acc = 2);

    // Running this with a sanitizer/valgrid proves it has
    // freed up all memory.
    bsa_free(test_bsa);

    
}

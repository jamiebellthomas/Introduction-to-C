#include "../bsa.h"
#define MAX_STRING 1000
#define UNUSED -1


// Prototypes
int pointer_index(int idx);
int col_index(int idx);
void bsa_row_create(bsa* b, int row_idx);
void bsa_row_free(bsa* b, int row_idx);
void bsa_append(bsa* b, int idx, 
                int row_idx, int col_idx, int d);
bool bsa_remove(bsa* b, int row_idx, int col_idx);
bool used_cell(bsa* b, int row_idx, int col_idx);
void row_str(bsa* b, char* str, int row);


struct bsa_cell{
    int value;
    bool set;
};

typedef struct bsa_cell bsa_cell;

struct bsa_row{
    int value_count;
    bsa_cell* row;
};

typedef struct bsa_row bsa_row;

struct bsa{
    int max_index;
    int value_count;
    bsa_row* row_array;
};

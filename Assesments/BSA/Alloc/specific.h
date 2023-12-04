#include "../bsa.h"
#define UNUSED -1
#define MAX_STRING 1000


// Prototypes
int pointer_index(int idx);
int col_index(int idx);
bool used_cell(bsa* b, int row_idx, int col_idx);



struct bsa_row{
    int value_count;
    int* row;
};

typedef struct bsa_row bsa_row;

struct bsa{
    int max_index;
    int value_count;
    bsa_row* row_array;
};

#include "../bsa.h"
#define UNUSED_CELL -1


// Prototypes
int pointer_idx(int idx);



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

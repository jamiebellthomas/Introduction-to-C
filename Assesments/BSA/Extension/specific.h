#include "../bsa.h"
#define INIT_SIZE 50
#define RESIZE_FACTOR 1.5
#define UPPER_LOAD_FACTOR 0.75
#define NEIGHBOURHOOD 3
#define UNAVAILABLE -1

struct bsa_cell
{
    int value;
    int original_index;
};

typedef struct bsa_cell bsa_cell;

struct bsa
{
    bsa_cell* array;
    bool* occupied;
    int max_index;
    int length;
    int elements;
};

int hash_function(int len, int d);
bool bsa_reallocate(bsa* b, int new_size);
void bsa_resize(bsa* b, int new_size);
void count_elem(int* p, int* n);
int neighbour_availability(bsa* b, int indx);
void test(void);




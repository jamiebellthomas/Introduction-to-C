#include "../bsa.h"
#define INIT_SIZE 1000
#define RESIZE_FACTOR 1.5
#define UPPER_LOAD_FACTOR 0.75
#define NEIGHBOURHOOD 3


struct bsa
{
    int* array;
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




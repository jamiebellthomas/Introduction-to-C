#include "../bsa.h"
#define INIT_SIZE 1000
#define RESIZE_FACTOR 1.5


struct bsa
{
    int* array;
    bool* occupied;
    int max_index;
    int length;
    int elements;
};

int hash_function(bsa* h, int d);
void test(void);




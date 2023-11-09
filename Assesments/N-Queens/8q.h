#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_GRID 10
#define MAX_SEARCH_SPACE 1000000
struct state {
    int queens;
    char board[MAX_GRID][MAX_GRID];
};

typedef struct state state;


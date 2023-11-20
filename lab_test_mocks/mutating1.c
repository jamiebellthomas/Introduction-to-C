#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#define N 20
#define RAND_FACTOR 10

void fill_board(int board[N][N]);
void mutate_board(int board[N][N]);


int main(void){
    int board[N][N];
    fill_board(board);
    printf("----------\n");
    mutate_board(board);

}

void fill_board(int board[N][N]){
    for(int row = 0;row<N;row++){
        for(int col = 0; col<N;col++){
            board[row][col] = rand()%RAND_FACTOR;
            printf("%i",board[row][col]);
        }
        printf("\n");
    }
}

void mutate_board(int board[N][N]){
    int rnd_row, rnd_col, temp, h_s=0, v_s=0;
    long loops = (N*N*N);
    for(long i = 0;i<loops;i++){
        rnd_row = rand()%N;
        rnd_col = rand()%N;
        if((rnd_col != (N-1)) && (board[rnd_row][rnd_col]>board[rnd_row][rnd_col+1])){
            temp = board[rnd_row][rnd_col];
            board[rnd_row][rnd_col] = board[rnd_row][rnd_col+1];
            board[rnd_row][rnd_col+1] = temp;
        }
        rnd_row = rand()%N;
        rnd_col = rand()%N;
        if((rnd_row != (N-1)) && (board[rnd_row][rnd_col]>board[rnd_row+1][rnd_col])){
            temp = board[rnd_row][rnd_col];
            board[rnd_row][rnd_col] = board[rnd_row+1][rnd_col];
            board[rnd_row+1][rnd_col] = temp;
        }

    }

    for(int row = 0;row<N;row++){
        for(int col = 0; col<N;col++){
            printf("%i",board[row][col]);
        }
        printf("\n");
    }
    printf("h:%i\n",h_s);
    printf("v: %i\n",v_s);
}


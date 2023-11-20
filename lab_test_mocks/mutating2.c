#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define N 21
#define RAND_FACTOR 10
#define TWO 2.0

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
    int rnd_row1, rnd_col1, temp, rnd_col2, rnd_row2;
    long loops = (N*N*N*N);
    float centre = N/TWO, dist1, dist2;
    for(int i = 0;i<loops;i++){
        rnd_col1 = rand()%N;
        rnd_col2 = rand()%N;
        rnd_row1 = rand()%N;
        rnd_row2 = rand()%N;

        dist1 = pow((pow((rnd_col1-centre),2)+pow((rnd_row1-centre),2)),0.5);
        dist2 = pow((pow((rnd_col2-centre),2)+pow((rnd_row2-centre),2)),0.5);

        if(!(((dist2 < dist1) && (board[rnd_row2][rnd_col2] < board[rnd_row1][rnd_col1]))
         || ((dist2 > dist1) && (board[rnd_row2][rnd_col2] > board[rnd_row1][rnd_col1])))){
            temp = board[rnd_row1][rnd_col1];
            board[rnd_row2][rnd_col2] = board[rnd_row1][rnd_col1];
            board[rnd_row2][rnd_col2] = temp;
         }

    }


    for(int row = 0;row<N;row++){
        for(int col = 0; col<N;col++){
            printf("%i",board[row][col]);
        }
        printf("\n");
    }
}





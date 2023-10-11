#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
/*
Basically what this script wants to do is look at different configs of dart boards to look
for the best (lowest) configuration. If we find a better config, keep it and move on
else discard it and move on

Between each iteration we randomly shuffle 2 numbers

Key functions:
1) Generate board (1-20)
2) Randomly shuffling 2 numbers
3) Score calculations
4) Updating dart board config

After writing this I'm really happe with how it went, I wrote all the functions before I touched main
And I made assertion tests for each function and tested them as I went along! Testing code modules
as you go along makes everything so so much easier!

*/
#define DART_BOARD 20
#define ITERATIONS 5000000


int generate_board(int* board);
int single_shuffle(int* board);
int random_number(int lim);
int score_calcs(int* board);
int update_board(int* old_board, int* new_board);
void print_array(int* array);
void test();

int main(void){
    test();
    int current_board[DART_BOARD], new_board[DART_BOARD], score_current, score_new, lowest_score;
    generate_board(current_board);
    generate_board(new_board);
    for(long iterations = 0;iterations < ITERATIONS; iterations++){
	single_shuffle(new_board);
	score_current = total_score_calcs(current_board);
	score_new = total_score_calcs(new_board);
	if(score_new < score_current){
	    update_board(current_board, new_board);
 	    lowest_score = score_new;
	}
	else{
	    update_board(new_board, current_board);
	}
    }

    printf("Optimal configuration found was:\n");
    print_array(current_board);
    printf("This gave a score of %i\n", lowest_score);

}

int generate_board(int* board){
    int i;
    for(i=0;i<DART_BOARD;i++){
	board[i] = i+1;
    }
    return 0;
}

int single_shuffle(int* board){
    int i1 = 0, i2 = 0, temp;
    while(i1 == i2){
	i1 = random_number(DART_BOARD);
	i2 = random_number(DART_BOARD);
    }
    temp = board[i1];
    board[i1] = board[i2];
    board[i2] = temp;
    return 0;
}

int random_number(int lim){
    int rand_num;
    rand_num = rand()%lim;
    return rand_num;
}

int total_score_calcs(int* board){
    int sum = 0;
    // Sum needs to be initialised as zero here ^
    for(int i = 1 ; i < DART_BOARD-1 ; i++){
	sum += pow((board[i-1] + board[i] + board[i+1]),2);
    }
    sum += front_end_score_calcs(board);
    sum += back_end_score_calcs(board);
    return sum;
}

int front_end_score_calcs(int* board){
    int sum, total;
    sum = board[0] + board[1] + board[DART_BOARD-1];
    total = pow(sum,2);
    return total;
}

int back_end_score_calcs(int* board){
    int sum, total;
    sum = board[0] + board[DART_BOARD-2] + board[DART_BOARD-1];
    total = pow(sum,2);
    return total;
}

int update_board(int* old_board, int* new_board){
    for(int i = 0;i < DART_BOARD;i++){
	old_board[i] = new_board[i];
    }
    return 0;
}

void print_array(int* array){
    int i;
    for(i=0;i<DART_BOARD;i++){
        printf("%i ", array[i]);
    }
    printf("\n");
}

void test(){
    int test_board1[DART_BOARD], test_board2[DART_BOARD], count = 0;
    generate_board(test_board1);
    generate_board(test_board2);
    assert((test_board1[0] == 1) && (test_board1[9] == 10) && (test_board1[DART_BOARD-1] == DART_BOARD));
    single_shuffle(test_board2);
    for(int i = 0;i < DART_BOARD;i++){
	if(test_board1[i] != test_board2[i]){
	    ++count;
	}
    }
    assert(count == 2);
    assert(front_end_score_calcs(test_board1) == 529);
    assert(back_end_score_calcs(test_board1) == 1600);
    assert(total_score_calcs(test_board1) == 24350);
    update_board(test_board1, test_board2);
    for(int i = 0; i < DART_BOARD; i++){
	assert(test_board1[i] == test_board2[i]);
    }
}


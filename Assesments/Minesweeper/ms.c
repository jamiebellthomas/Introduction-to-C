#include "ms.h"
#define LEGAL_CHAR_COUNT 11
/*
#define MAXSQ 10
typedef struct board {
   int grid[MAXSQ][MAXSQ];
   int w;
   int h;
   int totmines;
} board;

#define UNK  '?'
#define MINE 'X'
*/





// Maybe some of your own function prototypes here
// REMOVE THIS LATER - PRINT ISNT BEING SUBMITTED - ONLY THERE FOR DEBUG PURPOSES LALLALALALALALALALALALALALALALALALALALALALALALLALAALAL
//void print_2D_array(int array[MAXSQ][MAXSQ], int height, int width);

int is_char_in_string(char c, char string);
int legal_char_checker(char inp[MAXSQ*MAXSQ+1]);
int correct_no_of_mines(char inp[MAXSQ*MAXSQ+1], unsigned totmines);
int correct_str_len(unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]);

board solve_board(board b)
{
}

void board2str(char s[MAXSQ*MAXSQ+1], board b)
{
}

bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]){
    if(legal_char_checker(inp)&&
       correct_no_of_mines(inp, totmines)&&
       correct_str_len(width, height, inp)){
        return true;
    }
    return false;
}

int legal_char_checker(char inp[MAXSQ*MAXSQ+1]){
    const char legal_chars[LEGAL_CHAR_COUNT+1] = "012345678?X";
    for(int c = 0 ; c<(int)strlen(inp) ; c++){
        if(strchr(&legal_chars, inp[c]) == NULL){
            return 0;
        }
    }
    return 1;
}

int correct_no_of_mines(char inp[MAXSQ*MAXSQ+1], unsigned totmines){
    unsigned mine_counter = 0;
    for(int c = 0 ; c<(int)strlen(inp) ; c++){
        if(inp[c] == MINE){
            ++mine_counter;
        }
    }
    if(mine_counter <= totmines){
        return 1;
    }
    return 0;
}

int correct_str_len(unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]){
    unsigned len;
    len = strlen(inp);
    if(len == (width*height)){
        return 1;
    }
    return 0;
}

board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]){
    board new_board;
    new_board.w = width;
    new_board.h = height;
    new_board.totmines = totmines;
    short str_cell_index;
    for(int i = 0;i < height;i++){
        for(int j = 0;j < width;j++){
	    // Translates a 2-dimensional index to 1-dimensional space
	    str_cell_index = j + width*i;
	    new_board.grid[i][j] = inp[str_cell_index];
        }
    }
    return new_board;
}
/*
void print_2D_array(int array[MAXSQ][MAXSQ], int height, int width){
    for(int row = 0;row < height;row++){
        for(int col = 0;col < width;col++){
            printf("%c", array[row][col]);
        }
	printf("\n");
    }
}
*/

void test(void){
    unsigned test_totmines = 1, test_width = 5, test_height = 5; 
    char test_inp[MAXSQ*MAXSQ+1] = "000000111001X100111000000";
    char test_inp_bad[MAXSQ*MAXSQ+1] = "0000001l1001XX0011100000";
    board test_board = make_board(test_totmines, test_width, test_height, test_inp);
    //print_2D_array(test_board.grid, test_board.h, test_board.w);
    for(unsigned row = 0;row < test_height;row++){
        for(unsigned col = 0;col < test_width;col++){
	    // Assert that each value in the new
	    // grid is the same as its positional
	    // counter-part in the input string.
            assert(test_board.grid[row][col] == test_inp[col + row*test_width]);
        }
    }
    assert(legal_char_checker(test_inp) == 1);
    assert(legal_char_checker(test_inp_bad) == 0);
    assert(correct_no_of_mines(test_inp, 1) == 1);
    assert(correct_no_of_mines(test_inp_bad, 1) == 0);
    assert(correct_str_len(test_width, test_height, test_inp) == 1);
    assert(correct_str_len(test_width, test_height, test_inp_bad) == 0);
    assert(syntax_check(test_totmines, test_width, test_height, test_inp) == true);
    assert(syntax_check(test_totmines, test_width, test_height, test_inp_bad) == false);
}

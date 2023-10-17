#include "ms.h"
#define LEGAL_CHAR_COUNT 11
#define MAX_ADJACENT 8

// Maybe some of your own function prototypes here


// REMOVE THIS LATER - PRINT ISNT BEING SUBMITTED - ONLY THERE FOR DEBUG PURPOSES LALLALALALALALALALALALALALALALALALALALALALALALLALAALAL
void print_2D_array(int array[MAXSQ][MAXSQ], int height, int width);


struct cell {char adjacent[MAX_ADJACENT+1]; char value;};
typedef struct cell cell;


int is_char_in_string(char c, char string);
int legal_char_checker(char inp[MAXSQ*MAXSQ+1]);
unsigned mine_counter(char inp[MAXSQ*MAXSQ+1]);
int correct_str_len(unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]);
board init_board(int totmines, int width, int height);
cell cell_info(board b, int row, int col);
char replacement_value(cell c);

/* -----------
 Board Solver
----------------*/

board solve_board(board b){
    /*
	This function neeeds to be able to apply rule#1 % #2 and return the solved board if possible.
	If not possible it needs to return the partially solved board in grid format so it can be
	be coverted by board2str to a string.

	We need to work out what each rull will do and how they'll be applied.

	I'm thinking that initially we make 2 functions, solve_rule_1 and solve_rule_2 and see what effect these have on input grids

	Thes functions will need to be called repeatedly until there are no more changes to the boards
    */
}

board solve_rule_1(){
    /*This rule simply says if all the mines have been discovered then you
    can fill in the remaining values based off the mines with its proximity*/
    // This function requires a sub function that determines the number of discovered mines,
    // this could potentially be linked into the correct_no_of_mines checker

    // We'll also need a function that can determines corret number to go into unknown squares based off neighbouring squares

    // This is a boardwide function therefore it should only be applied twice, once at the start and once at the end. If it doesn't solve it
    // in either of these calls, its not solveable with these rules
    
}


board solve_rule_2(){
    /*This is a tad more complicated. For a KNOWN square, if the number of known mines + number of unknown mines = number on tile
    you can fill in those unknown squares as mines*/
    // We need to devise a method of looking at adjacent cells, considering edge and corner cells. Central squares will 8 neighbours
    // Edges have 5 and corners have 3.
    // This function is applied on a cell by cell basis, apply it iteratively until there is no difference between iterations.
}

cell cell_info(board b, int row, int col){
    cell current_cell = {.value = b.grid[row][col],
                       .adjacent = {'0'}};
    int i,j, neighbours = 0;
    for(i = -1;i <= 1;i++){
        for(j = -1;j <= 1;j++){
            if((row+i)<b.h && (row+i)>=0 && (col+j)<b.w && (col+j)>=0 && ((i != 0) || (j != 0))){
                current_cell.adjacent[neighbours++] = b.grid[row+i][col+j];
            }
        }
    }
    return current_cell;
}

char replacement_value(cell c){
    unsigned mine_count;
    mine_count = mine_counter(c.adjacent);
    mine_count += '0';
    return mine_count;
}


/* -----------
 BOARD -> STRING
----------------*/
void board2str(char s[MAXSQ*MAXSQ+1], board b){
    short str_cell_index;
    for(short row = 0;row < b.h ;row++){
	for(short col = 0; col<b.w ; col++){
            str_cell_index = col + (b.w)*row;
            s[str_cell_index] = b.grid[row][col];
        }
    }
}

/* -----------
 SYNTAX CHECKER
----------------*/
bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]){
    if(legal_char_checker(inp) && correct_str_len(width, height, inp)){
        unsigned mine_count;
        mine_count = mine_counter(inp);
        if(mine_count <= totmines){
            return true;
        }
    }
    return false;
}

int legal_char_checker(char inp[MAXSQ*MAXSQ+1]){
    char legal_chars[LEGAL_CHAR_COUNT+1] = "012345678?X";
    for(int c = 0 ; c<(int)strlen(inp) ; c++){
        if(strchr(legal_chars, inp[c]) == NULL){
            return 0;
        }
    }
    return 1;
}

unsigned mine_counter(char inp[MAXSQ*MAXSQ+1]){
    unsigned mine_count = 0;
    for(int c = 0 ; c<(int)strlen(inp) ; c++){
        if(inp[c] == MINE){
            ++mine_count;
        }
    }
    return mine_count;
}

int correct_str_len(unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]){
    unsigned len;
    len = strlen(inp);
    if(len == (width*height)){
        return 1;
    }
    return 0;
}
/* -----------
 GRID CREATION
----------------*/
board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]){
    board new_board = init_board(totmines,width,height);
    short str_cell_index;
    for(int row = 0;row < height;row++){
        for(int col = 0;col < width;col++){
	    // Translates a 2-dimensional index to 1-dimensional space
	    str_cell_index = col + width*row;
	    new_board.grid[row][col] = inp[str_cell_index];
        }
    }
    return new_board;
}

board init_board(int totmines, int width, int height){
    board new_board = {.w = width,
                       .h = height,
                       .totmines = totmines,
                       .grid = {{0}}};
    return new_board;
}

void print_2D_array(int array[MAXSQ][MAXSQ], int height, int width){
    for(int row = 0;row < height;row++){
        for(int col = 0;col < width;col++){
            printf("%c", array[row][col]);
        }
	printf("\n");
    }
}



/* -----------
 TESTING
----------------*/
void test(void){
    // Test variables initialisation
    unsigned test_totmines = 1, test_width = 5, test_height = 5, row, col;
    char test_inp[MAXSQ*MAXSQ+1] = "000000111001X100111000000";
    char test_inp_bad[MAXSQ*MAXSQ+1] = "0000001l1001XX0011100000";

    // Board creation tests

    board test_board = init_board(test_totmines, test_width, test_height);
    assert(test_board.totmines == 1);
    assert(test_board.w == 5);
    assert(test_board.h == 5);
    // Check all values in te initialised grid are zero
    for(row = 0;row < test_height;row++){
        for(col = 0;col < test_width;col++){
            assert(test_board.grid[row][col] == 0);
        }
    }

    test_board = make_board(test_totmines, test_width, test_height, test_inp);
    for(row = 0;row < test_height;row++){
        for(col = 0;col < test_width;col++){
	    // Assert that each value in the new
	    // grid is the same as its positional
	    // counter-part in the input string.
            assert(test_board.grid[row][col] == test_inp[col + row*test_width]);
        }
    }

    // Syntax checker tests

    assert(legal_char_checker(test_inp) == 1);
    assert(legal_char_checker(test_inp_bad) == 0);
    assert(mine_counter(test_inp) == 1);
    assert(mine_counter(test_inp_bad) == 2);
    assert(correct_str_len(test_width, test_height, test_inp) == 1);
    assert(correct_str_len(test_width, test_height, test_inp_bad) == 0);
    assert(syntax_check(test_totmines, test_width, test_height, test_inp) == true);
    assert(syntax_check(test_totmines, test_width, test_height, test_inp_bad) == false);

    // board2str check.

    board2str(test_inp_bad, test_board);
    assert(strcmp(test_inp_bad,test_inp) == 0);

    // Cell struct and replacement values

    cell test_cell;
    test_cell = cell_info(test_board,0,0);
    assert(strcmp(test_cell.adjacent, "001") == 0);

    test_cell = cell_info(test_board,0,1);
    //printf("%s",test_cell.adjacent);
    assert(strcmp(test_cell.adjacent, "00011") == 0);

    test_cell = cell_info(test_board,0,2);
    assert(strcmp(test_cell.adjacent, "00111") == 0);

    test_cell = cell_info(test_board,1,1);
    assert(strcmp(test_cell.adjacent, "0000101X") == 0);
    char test_replacement;
    test_replacement = replacement_value(test_cell);
    assert(test_replacement == '1');
}

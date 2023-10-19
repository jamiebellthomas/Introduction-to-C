#include "ms.h"
#include <stdlib.h>
#define LEGAL_CHAR_COUNT 11
#define MAX_ADJACENT 8
#define LEGAL_CHARS "012345678?X"
// Maybe some of your own function prototypes here

typedef struct cell {char adjacent[MAX_ADJACENT+1]; char value;} cell;

void solve_rule_1(board* b);
void solve_rule_2(board* b);
bool check_solve(board b);
cell cell_info(board b, int row, int col);
char replacement_value(cell c);
board unk_replacement(board b, int row, int col);
bool legal_char_checker(char inp[MAXSQ*MAXSQ+1]);
unsigned char_counter(char* inp, char c);
bool correct_str_len(unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]);
board init_board(int totmines, int width, int height);

/* -----------
 Board Solver Functions
----------------*/

/* The main board solve function passes board pointers to solve_rule_1
   and solve_rule_2 to prevent large numbers of copies from being made
   
   solve_rule_1 is called initially as this would be the optimal way of solving
   if it's applicable. If it doesn't solve it, solve_rule_2 is called until the delta
   between iterations becomes zero. At this point we check if it's solved. If not we 
   reapply rule 1 to see if this can solve it and return whatever the result is. */
board solve_board(board b){
    solve_rule_1(&b);
    if(check_solve(b)){
        return b;
    }

    bool fixed = false;
    char previous_iter[MAXSQ*MAXSQ+1], current_iter[MAXSQ*MAXSQ+1];
    board2str(previous_iter,b);
    while(!fixed){
        solve_rule_2(&b);
        board2str(current_iter,b);
        if((strcmp(current_iter,previous_iter))==0){
            fixed = true;
        }
        else{
            strcpy(previous_iter,current_iter);
        }
    }
    if(check_solve(b)){
        return b;
    }
    solve_rule_1(&b);
    return b;
}
/* This function implements Rule 1 where if 
   all mines have been discovered, the remaining
   unknowns can be filled in as numbers */
void solve_rule_1(board* b){
    unsigned mine_count;
    char flat_grid[MAXSQ*MAXSQ+1];
    board2str(flat_grid, *b);
    mine_count = char_counter(flat_grid, MINE);
    if((int)mine_count == b->totmines){
        for(int row = 0;row < b->h;row++){
            for(int col = 0;col < b->w;col++){
 		if(b->grid[row][col] == UNK){
                    cell cell_details = cell_info(*b,row,col);
                    b->grid[row][col] = replacement_value(cell_details);
                }
            }
        }
    }
}

/* This function implements Rule 2 where if the sum of 
   unknowns and mines around a numeric cell is equal to
   the cell's value, the unknowns can be marked as mines */
void solve_rule_2(board* b){
    for(int row = 0;row<b->h;row++){
        for(int col = 0;col<b->w;col++){
            if(isdigit(b->grid[row][col])){
                unsigned unknown_plus_mine = 0;
                cell cell_details = cell_info(*b,row,col);
                unknown_plus_mine = char_counter(cell_details.adjacent, UNK) + char_counter(cell_details.adjacent, MINE);
                if((int)unknown_plus_mine == (cell_details.value-'0')){
                    *b = unk_replacement(*b,row,col); 
                }
            }
        }
    }
}

bool check_solve(board b){
    for(int row = 0;row<b.h;row++){
        for(int col = 0;col<b.w;col++){
            if(b.grid[row][col] == UNK){
                return false;
            }
        }
    }
    return true;
}
/* This function returns a cell struct for a given board struct 
   and index coordinates, ensuring no overflow errors occur.
   Part of the cell struct is an array containing the Moore's
   Neighbourhood, which is used in both Rules 1&2 */
cell cell_info(board b, int row, int col){
    cell current_cell = {.value = b.grid[row][col],
                       .adjacent = {'0'}};
    int i,j, neighbours = 0;
    // This nested for loop looks at the 3x3 grid surrounding a cell
    for(i = -1;i <= 1;i++){
        for(j = -1;j <= 1;j++){
            // This conditional clause ensures the adjacent cells
            // being considered are both within the array bounds and
            // not the original cell itself.
            if((row+i)<b.h &&
               (row+i)>=0  &&
               (col+j)<b.w &&
               (col+j)>=0  &&
               ((i != 0) || (j != 0))){
                current_cell.adjacent[neighbours++] = b.grid[row+i][col+j];
            }
        }
    }
    return current_cell;
}

/* This counts the number of mines in a cell's Moore's
   Neighbourhood and returns the correct value for that
   cell as a char so it can be easily inserted into a grid */
char replacement_value(cell c){
    unsigned mine_count;
    mine_count = char_counter(c.adjacent,MINE);
    //Converts numeric value to a char
    mine_count += '0';
    return mine_count;
}


/* unk_replacement takes in a board and a cell's index coodinates 
   and replaces all unknowns in the Moore's Neigbourhood
   of that cell with mines. */
board unk_replacement(board b, int row, int col){
    int i,j;
        for(i = -1;i <= 1;i++){
            for(j = -1;j <= 1;j++){
                if((row+i)<b.h && (row+i)>=0 &&
                   (col+j)<b.w && (col+j)>=0){
                    if(b.grid[row+i][col+j] == UNK){
                        b.grid[row+i][col+j] = MINE;
		            }
                }
            }
        }
    return b;
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
    s[b.h*b.w] = '\0';
}

/* -----------
 SYNTAX CHECKER
----------------*/
bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]){
    if(legal_char_checker(inp) && correct_str_len(width, height, inp)){
        unsigned mine_count;
        mine_count = char_counter(inp,MINE);
        if(mine_count <= totmines){
            return true;
        }
    }
    return false;
}

bool legal_char_checker(char inp[MAXSQ*MAXSQ+1]){
    char legal_chars[LEGAL_CHAR_COUNT+1] = LEGAL_CHARS;
    for(int c = 0 ; c<(int)strlen(inp) ; c++){
        if(strchr(legal_chars, inp[c]) == NULL){
            return false;
        }
    }
    return true;
}
/* Counts the number of a certain char (c) in a given string (inp)
   This will be used to count the number of mines and unknowns in various
   strings.*/
unsigned char_counter(char* inp, char c){
    unsigned counter = 0;
    for(int i = 0 ; i<(int)strlen(inp) ; i++){
        if(inp[i] == c){
            ++counter;
        }
    }
    return counter;
}

bool correct_str_len(unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]){
    unsigned len;
    len = strlen(inp);
    if(len == (width*height)){
        return true;
    }
    return false;
}
/* -----------
 GRID CREATION
----------------*/
board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]){
    board new_board = init_board(totmines,width,height);
    for(int row = 0;row < height;row++){
        for(int col = 0;col < width;col++){
	    // Translates a 2-dimensional index to 1-dimensional space
	    new_board.grid[row][col] = inp[col + width*row];
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

/* -----------
 TESTING
----------------*/
void test(void){

    unsigned test_totmines = 1, test_width = 5, test_height = 5, row, col;
    char test_inp[MAXSQ*MAXSQ+1] = "000000111001X100111000000";
    char test_inp_bad[MAXSQ*MAXSQ+1] = "0000001l1001XX0011100000";

    // The make board function has 1 sub-function, the board initialisation.

    // First test ensures that the board structs are being initialised as expected,
    // With the correct width, height and totmines values.
    // The nested for loop ensures all values in the 2D array are initialised as zero 
    board test_board = init_board(test_totmines, test_width, test_height);
    assert(test_board.totmines == 1);
    assert(test_board.w == 5);
    assert(test_board.h == 5);
    for(row = 0;row < test_height;row++){
        for(col = 0;col < test_width;col++){
            assert(test_board.grid[row][col] == 0);
        }
    }

    
    // The final make board test looks at the over all make_board function
    // The only additional piece of functionality here is inserting the input string
    // as a 2D array into the struct. To test this a nested for loop can be used and to
    // compare the board.grid to the input string on a char by char basis.
    test_board = make_board(test_totmines, test_width, test_height, test_inp);
    for(row = 0;row < test_height;row++){
        for(col = 0;col < test_width;col++){
            assert(test_board.grid[row][col] == test_inp[col + row*test_width]);
        }
    }

    // Syntax checker sub function tests ensure that the legal char checker,
    // the char counter (for the currect number of mines) and the correct 
    // input string length are being validated using both good and bad inputs

    assert(legal_char_checker(test_inp));
    assert(legal_char_checker(test_inp_bad) == 0);
    assert(char_counter(test_inp,MINE) == 1);
    assert(char_counter(test_inp_bad,MINE) == 2);
    assert(correct_str_len(test_width, test_height, test_inp));
    assert(correct_str_len(test_width, test_height, test_inp_bad) == 0);

    // Main syntax_checker tests ensure all the sub-functions are working together
    // To produce the correct results for both the good and bad inputs

    assert(syntax_check(test_totmines, test_width, test_height, test_inp));
    assert(syntax_check(test_totmines, test_width, test_height, test_inp_bad) == false);

    // board2str test: to test this, the .grid for the good input was written
    // to the bad input string. This is then compared to the good input string
    // to ensure the 2D array was correctly translated
    board2str(test_inp_bad, test_board);
    assert(strcmp(test_inp_bad,test_inp) == 0);

    // Cell struct creation and
    // replacement value calculation tests

    // The cell struct is used in both rule 1 and rule 2 and has 
    // multiple edge cases

    // Let's start with a basic case (a central cell). This should return 
    // the 8 cells in its Moore's Neighbourhood
    cell test_cell;
    test_cell = cell_info(test_board,1,1);
    assert(strcmp(test_cell.adjacent, "0000101X") == 0);
    assert(test_cell.value == '1');

    // Now each of the 4 corners need to be examined to ensure all parts of the
    // Overflow catching clause are working:
    test_cell = cell_info(test_board,0,0);
    assert(strcmp(test_cell.adjacent, "001") == 0);
    assert(test_cell.value == '0');

    test_cell = cell_info(test_board,0,4);
    assert(strcmp(test_cell.adjacent, "010") == 0);
    assert(test_cell.value == '0');

    test_cell = cell_info(test_board,4,0);
    assert(strcmp(test_cell.adjacent, "010") == 0);
    assert(test_cell.value == '0');

    test_cell = cell_info(test_board,4,4);
    assert(strcmp(test_cell.adjacent, "100") == 0);
    assert(test_cell.value == '0');

    // One final thing to look at for this funtion is to run an adjacency calculation on
    // A max sized grid (10x10) and check for any overflow sanitisation warnings.
    char large_inp[MAXSQ*MAXSQ+1] = "0100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    board large_board = make_board(0, 10, 10, large_inp);
    test_cell = cell_info(large_board,0,0);
    assert(strcmp(test_cell.adjacent, "100") == 0);
    // No sanitisation errors detected which means areas outside the designated array 
    // size aren't being considered

   // One other edge case was for a cell on the edge of the board. This should return
   // A string of length 5. If all 4 corners are working it is safe to assume at this point
   // that all edges should be working, so not all edges will be tested
    test_cell = cell_info(test_board,0,2);
    assert(strcmp(test_cell.adjacent, "00111") == 0);
    assert(test_cell.value == '0');

    

    // The replacement value takes a cell, looks at the adjacent squares and returns
    // The value that should be in that cell. This is used as a sub-function in Rule 1
    // Therefore the number should equal the number of adjacent mines
    // Even though this would only be appled to unknown cells, the best way to test it
    // is by applying it to a known cell and ensuring it arrives at the same value as
    // the one present
    char test_replacement;
    test_cell = cell_info(test_board,1,1);
    test_replacement = replacement_value(test_cell);
    assert(test_replacement == '1');

    // Overall solve rule 1 tests.
    // Rule 1 calles board2str, char_counter, cell_info and replacement_value.
    // All of these functions have been tested individually so all that is left is to
    // Test the over all function to ensure it can solve suitably simple boards.
    // This board will be an unsolved verison of test_inp.
    char test_inp2[MAXSQ*MAXSQ+1] = "000000?11001X100?1?000000";
    test_board = make_board(1, 5, 5, test_inp2);
    solve_rule_1(&test_board);
    board2str(test_inp2, test_board);
    assert(strcmp(test_inp2,test_inp) == 0);

    // Solve rule 2 sub-function tests:

    // Firstly the char_counter needs to be tested for counting
    // the number of unknowns.
    // For this a case will be chosen with more than 1 unknown to
    // ensure the sub-function is working exactly as expected 
    char test_inp3[MAXSQ*MAXSQ+1] = "000000?11001X100?1?0";
    test_board = make_board(1, 5, 4, test_inp3);
    test_cell = cell_info(test_board,3,2);
    assert(char_counter(test_cell.adjacent, UNK) == 2);

    // The second additional function is replacing adjacent
    // unknowns with mines. For this a simple example with multiple
    // mines, unknowns and numeric chars will be chosen. The output should convert
    // unknowns to mines and leave the remaning chars untouched.
    char test_unkr_input[MAXSQ*MAXSQ+1] = "??2X6X??2";
    test_board = make_board(6,3,3,test_unkr_input);
    test_board = unk_replacement(test_board, 1, 1);
    board2str(test_unkr_input,test_board);
    assert(strcmp(test_unkr_input,"XX2X6XXX2") == 0);

    // We also need to test an edge case for the unknown replacement
    // function to ensure we don't experience any out of bounds errors
    // For this a similar example will be used except the cell being 
    // considered will be in the top left corner.
    char test_unkr_input2[MAXSQ*MAXSQ+1] = "3X2X?2221";
    test_board = make_board(3,3,3,test_unkr_input2);
    test_board = unk_replacement(test_board, 0, 0);
    board2str(test_unkr_input2,test_board);
    assert(strcmp(test_unkr_input2,"3X2XX2221") == 0);

    // Rule 2 calls cell_info, char_counter, unk_counter & unk_replacement.
    // All these functions have been appropriately tested so all that is
    // left is to apply the solve_rule_2 function to a suitably challenging
    // grid to ensure it is working as anticipated.
    // This will also be a good place to test the check_solve function which
    // Is the only other function that will be called in solve_board.
    char test_inp4[MAXSQ*MAXSQ+1] = "2XX102?53112??10122100000";
    test_board = make_board(1, 5, 5, test_inp4);
    assert(check_solve(test_board) == 0);
    solve_rule_2(&test_board);
    board2str(test_inp4,test_board);
    assert(strcmp(test_inp4,"2XX102X53112XX10122100000") == 0);
    assert(check_solve(test_board));

    // solve_board will now be tested on the same examples that its sub-functions 
    // (solve_rule_1 and solve_rule_2) were tested on to ensure these rules are being
    // called appropriately.

    char test_inp5[MAXSQ*MAXSQ+1] = "000000?11001X100?1?000000";
    test_board = make_board(1, 5, 5, test_inp5);
    test_board = solve_board(test_board);
    board2str(test_inp5, test_board);
    assert(strcmp(test_inp5,test_inp) == 0);

    char test_inp6[MAXSQ*MAXSQ+1] = "2XX102?53112??10122100000";
    test_board = make_board(1, 5, 5, test_inp6);
    test_board = solve_board(test_board);
    board2str(test_inp6,test_board);
    assert(strcmp(test_inp6,"2XX102X53112XX10122100000") == 0);
    // We need to add tests to ensure the solve function (and by extension, rule 1 and rule 2 functions) 
    // only act where applicable.

    // The first test will be an erroneous input (unsolvable)
    // (The central number needs to be 8 for rule 2 to apply)
    // It should return an identical board
    char error_inp[MAXSQ*MAXSQ+1] = "?XXX7XX??";
    board error_board = make_board(8,3,3,error_inp);
    error_board = solve_board(error_board);
    board2str(error_inp,error_board);
    assert(strcmp(error_inp,"?XXX7XX??") == 0);

    // The second will be a perfectly valid input, but the solve function doesn't
    // have enough info to act on it
    // This should also return an identical board
    char hard_inp[MAXSQ*MAXSQ+1] = "1X?12?0??";
    board hard_board = make_board(2,3,3,hard_inp);
    hard_board = solve_board(hard_board);
    board2str(hard_inp,hard_board);
    assert(strcmp(hard_inp,"1X?12?0??")==0);

    // The final example board will be a board that can only be partially solved using these rules
    // (rule 2 is applicable on certain areas and rule 1 is never applicable)
    // solve_board should return the partially solved board.
    char partial_inp[MAXSQ*MAXSQ+1] = "001X?0013?11011X2100???00";
    board partial_board = make_board(5,5,5,partial_inp);
    partial_board = solve_board(partial_board);
    board2str(partial_inp,partial_board);
    assert(strcmp(partial_inp, "001XX0013X11011X2100???00")==0);




}

/* We need to read in a maze's dimensions and the Maze itself from maze.txt. It is in the format 
rows cols
MAZE
The rows and cols need to be read in so we know how much space to allocate 
Then the maze needs to be converted to a 2D array in this space
The start point is the gap in the outer wall closest to the top corner
This will use a method of recursion

Initial thoughts of needed functions:
void test()
maze import_maze()
coordinates start_point()
coordinates next_step() (this'll need to make sure we can't move backwards)
bool completed()

For now let's just start with reading in the data
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define WALL 'X'
#define UNEXPLORED 'O'
#define EXPLORED 'I'
#define CORNER_SHIFT 2

typedef int coordinates[2];

struct maze {
    coordinates size;
    char** grid;
    coordinates start_state;
};
typedef struct maze maze;

void maze_init(maze* maze , char* file_name);
char** grid_memory_allocation(char** start, int rows, int cols, FILE* file);
void print_2D_array(char** array, int rows, int cols);
void maze_free(char** maze, int rows);
void exit_counter_and_entry_point(maze* maze);
int maze_search(maze* maze, int current_row, int current_col);
bool check_solve(maze* maze, int current_row, int current_col);
bool is_safe(maze* maze, int current_row, int current_col);
void remove_o(maze* maze);

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Incorrect usage.\n");
        printf("Correct usage: ./maze file_name.txt\n");
    }
    maze maze = {.size = {0},
                 .grid = NULL,
                 .start_state = {0}};
    maze_init(&maze, argv[1]);
    print_2D_array(maze.grid, maze.size[0],maze.size[1]);
    exit_counter_and_entry_point(&maze);
    assert(maze.start_state[0] == 1);
    assert(maze.start_state[1] == 0);

    int outcome = maze_search(&maze,maze.start_state[0],maze.start_state[1]);
    if(outcome == 1){
        printf("-------------------\n");
        printf("Succesfully Solved:\n");
        printf("-------------------\n");
        remove_o(&maze);
        print_2D_array(maze.grid, maze.size[0],maze.size[1]);
    }
    
    else{
        printf("-------------------\n");
        printf("No feasible route through maze\n");
        printf("-------------------\n");
    }

    maze_free(maze.grid,maze.size[0]);

}

void maze_init(maze* maze , char* file_name){
    // We need to read in the first row, use that to malloc/calloc correct amount of memory
    int rows, cols;
    FILE *file = fopen(file_name, "r");
    if (file == NULL){
        printf("Failed to open this file.\n");
        exit(0);
    }
    int items_read = fscanf(file, "%i %i", &rows, &cols);
    // At this point the scanf 'cursor is on the right of the two numbers at the top
    if(items_read != 2){
        printf("Failed to read the number of rows and columns.\n");
        fclose(file);
        exit(0);
    }
    maze->size[0] = rows;
    maze->size[1] = cols;
    maze->grid = grid_memory_allocation(maze->grid, 
                                        maze->size[0], 
                                        maze->size[1], 
                                        file);
    fclose(file);
    

    

}

char** grid_memory_allocation(char** start, int rows, int cols, FILE* file){
    start = (char**)malloc(sizeof(char*)*(rows));
    if(start == NULL){
        fprintf(stderr, "**Memory Allocation Failed\n");
    }
    for(int i = 0;i<rows;i++){
        start[i] = (char*)malloc(sizeof(char)*(cols+1));
        if(start[i] == NULL){
            fprintf(stderr, "*Memory Allocation Failed\n");
        }
        fscanf(file, "%s",start[i]);
    }
    return start;
}


void print_2D_array(char** array, int rows, int cols){
    for(int i = 0;i<rows;i++){
        for(int j = 0;j<cols;j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
}

void maze_free(char** maze, int rows){
    for(int i = 0;i<rows;i++){
        free(maze[i]);      
    }
    free(maze);
}

// Now we've sorted out the reading in of the data, we need to design
// The recursion that's going to take us through this maze
// The first thing to do is to design something that'll tell us starting index coordinates



void exit_counter_and_entry_point(maze* maze){
    int counter = 0, closest = maze->size[0] + maze->size[1];
    char near, far;
    for(int i = 1; i<=(maze->size[1]-CORNER_SHIFT);i++){
        near = maze->grid[0][i];
        far = maze->grid[(maze->size[0]-1)][i];
        if(near != WALL){
            counter++;
            if(i<closest){
                closest = i;
                maze->start_state[0] = 0;
                maze->start_state[1] = i;
            }
        }
        if(far != WALL){
            counter++;
            if(i+(maze->size[0]-1)<closest){
                closest = i+(maze->size[0]-1);
                maze->start_state[0] = maze->size[0]-1;
                maze->start_state[1] = i;
            }
        }
    }

    for(int i = 1; i<=(maze->size[0] - CORNER_SHIFT); i++){
        near = maze->grid[i][0];
        far = maze->grid[i][(maze->size[1]-1)];
        if(near != WALL){
            counter++;
            if(i<closest){
                closest = i;
                maze->start_state[0] = i;
                maze->start_state[1] = 0;
            }
        }
        if(far != WALL){
            counter++;
            if(i+(maze->size[1]-1)<closest){
                closest = i+(maze->size[1]-1);
                maze->start_state[0] = i;
                maze->start_state[1] = maze->size[1]-1;
            }
        }
    }
    if(counter != 2){
        fprintf(stderr,"There are %i entrances to the maze, there should only be 2!\n",counter);
        exit(0);
    }    
}

int maze_search(maze* maze, int current_row, int current_col){
    //printf("Current State: %i, %i\n",current_row,current_col);
    if(current_col < 0 || current_row < 0){
        return 0;
    }
    
    if(is_safe(maze, current_row, current_col)){
        maze->grid[current_row][current_col] = EXPLORED;

        if(check_solve(maze, current_row, current_col)){
            return 1;
        }

        if(maze_search(maze,current_row+1,current_col) ||
           maze_search(maze,current_row,current_col+1) ||
           maze_search(maze,current_row-1,current_col) ||
           maze_search(maze,current_row,current_col-1)){
            return 1;
           }
        
        maze->grid[current_row][current_col] = WALL;
    }

    return 0;

}

bool check_solve(maze* maze, int current_row, int current_col){
    if((current_row == 0 || current_row == (maze->size[0]-1) ||
       current_col == 0 || current_col == (maze->size[1]-1)) &&
       (current_row != maze->start_state[0] ||  current_col != maze->start_state[1])){
        return true;
    }
    return false;
}

bool is_safe(maze* maze, int current_row, int current_col){
    if(maze->grid[current_row][current_col] != UNEXPLORED){
        return false;
    }
    return true;
}

void remove_o(maze* maze){
    for(int i = 0;i<maze->size[0];i++){
        for(int j = 0;j<maze->size[1];j++){
            if(maze->grid[i][j] == UNEXPLORED){
                maze->grid[i][j] = WALL;
            }
        }
    }
}

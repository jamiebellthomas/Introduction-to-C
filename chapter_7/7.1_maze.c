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

typedef int coordinates[2];

struct maze {
    coordinates size;
    char** grid;
    coordinates current_state;
};
typedef struct maze maze;

void maze_init(maze* maze , char* file_name);
char** grid_memory_allocation(char** start, int rows, int cols, FILE* file);
void print_2D_array(char** array, int rows, int cols);
void maze_free(char** maze, int rows);

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Incorrect usage.\n");
        printf("Correct usage: ./maze file_name.txt\n");
    }
    maze maze = {.size = {0},
                 .grid = NULL,
                 .current_state = {0}};
    maze_init(&maze, argv[1]);
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
    print_2D_array(maze->grid, maze->size[0],maze->size[1]);

    

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

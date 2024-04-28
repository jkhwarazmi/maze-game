/**
 * @file maze.h
 * @author Jamil Khwarazmi
 * @brief ADD BRIEF DESCRIPTION HERE
 */

#ifndef MAZE_H 
#define MAZE_H

// Define the max and min permitted dimensions
#define MIN_DIM 5
#define MAX_DIM 100

/**
 * @brief Struct to hold maze data, includes integer rows and columns, an
 *        integer array for start and end positions and a 2D array to store the
 *        maze, with a buffer of 10 to account for newlines and invalid mazes.
 *
*/
typedef struct 
{   
    char **map;
    int rows;
    int cols;
    int start[2]; // Which coord is which?
    int end[2]; // Same here
    
} Maze;

// Always have same order of maze/file throughout code
void load_maze(FILE *file, Maze *maze);
int check_maze_dimensions(int dimension, char *type);
int check_maze_exits(int quantity, char *type);
int validate_file(FILE *file, Maze *maze);
int create_maze(Maze *maze);
void free_maze(Maze *maze);
int read_maze(Maze *maze, FILE *file);

#endif /* MAZE_H */

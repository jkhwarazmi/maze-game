/**
 * @file maze.h
 * @author Jamil Khwarazmi
 * @brief Maze header file - Used to create a maze from a file, validate and free it
 */

#ifndef MAZE_H
#define MAZE_H

// Define the min and max permitted dimensions
#define MIN_DIM 5
#define MAX_DIM 100

/**
 * @struct Maze
 * @brief Struct to hold maze data, includes a 2D array to store the maze, integer numbers of rows
 *        and columns, and integer arrays for start and end positions ordered [row value, col value].
 *
 */
typedef struct
{
    char **map;
    int rows;
    int cols;
    int start[2];
    int end[2];

} Maze;

void init_maze(Maze *maze);
int check_maze_dimensions(int dimension, const char *type);
int validate_file(FILE *file, Maze *maze);
void print_maze_error(int error_code);
int create_maze(Maze *maze);
int read_maze(FILE *file, Maze *maze);
void free_maze(Maze *maze);

#endif /* MAZE_H */

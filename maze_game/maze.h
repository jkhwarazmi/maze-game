#ifndef MAZE_H 
#define MAZE_H

// The minimum and maximum dimensions of the maze
#define MIN 5
#define MAX 100

/**
 * @brief Struct to hold maze data, includes integer rows and columns, an
 *        integer array for start and end positions and a 2D array to store the
 *        maze, with a buffer of 10 to account for newlines and invalid mazes.
 *
*/
typedef struct {
    int rows;
    int cols;
    int start[2];
    int end[2];
    char map[MAX + 10][MAX + 10];
} Maze;

void load_maze(FILE *file, Maze *maze);
void check_maze_dimensions(int dimension, char *type);
void check_maze_exits(int quantity, char *type);
void validate_maze(Maze *maze);

#endif /* MAZE_H */
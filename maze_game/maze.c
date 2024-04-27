#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

/**
 * @brief Loads the maze from a file into a 2D array
 * 
 * @param file The file to load the maze from
 * @param maze The maze struct to store the maze in
*/
void load_maze(FILE *file, Maze *maze) {

    // Set buffer to slightly over MAX to account for newlines and invalid mazes
    int buffer = MAX + 10;
    char line[buffer];
    int lines = 0;

    // Read each line of the file and store it in the maze map
    while (fgets(line, buffer, file)) {
        lines++;

        for (int i = 0; i < buffer; i++) {
            maze->map[lines - 1][i] = line[i];
        }
    }

    // Close the file and set the number of rows in the maze
    fclose(file);
    maze->rows = lines;
}

/**
 * @brief Checks that the maze is within the required dimensions
 * 
 * @param dimension The dimension to check
 * @param type The type of dimension, either "height" or "width"
*/
void check_maze_dimensions(int dimension, char *type) {

    // Exits if the maze is too small or too large
    if (dimension < MIN) {
        printf("Error: Maze must have minimum %s of %d\n", type, MIN);
        exit(1);
    }

    if (dimension > MAX) {
        printf("Error: Maze must have maximum %s of %d\n", type, MAX);
        exit(1);
    }
}

/**
 * @brief Checks that the maze has exactly one start and one end
 * 
 * @param quantity The quantity of starts or ends
 * @param type The type of exit, either "start" or "end"
*/
void check_maze_exits(int quantity, char *type) {

    // Exits if the maze has too many or too few starts or ends
    if (quantity != 1) {
        printf("Error: Maze must have exactly one %s\n", type);
        exit(1);
    }
}

/**
 * @brief Checks that the maze is valid
 * 
 * @param maze The maze struct the maze is stored in
*/
void validate_maze(Maze *maze) {

    // Set cols to -1 so it only changes for first line
    maze->cols = -1;

    // Set number of start and end points to 0
    int starts = 0;
    int ends = 0;

    // Set maze_over to 0, used to check if the maze has empty lines
    int maze_over = 0;

    // Iterate over all rows in the maze
    for (int i = 0; i < maze->rows; i++) {
        char *line = maze->map[i];
        
        // If any line is empty, any otherwise valid characters become invalid and reduce the number of rows by 1
        if (line[0] == '\n') {
            maze_over = 1;
            maze->rows--;
            continue;
        }

        // Manually calculate line length to account for invisible characters but also use strlen for inner loop
        int line_length = 0;
        int length = strlen(line);

        for (int j = 0; j < length; j++) {
            
            // If any character is not a valid maze character, print error and exit
            if ((line[j] != '#' && line[j] != ' ' && line[j] != 'S' && line[j] != 'E' && line[j] != '\n') || maze_over) {
                printf("Error: Invalid characters in maze\n");
                exit(1);
            }

            // Increment line length for each character that is not a newline or set cols to first line length
            if (line[j] != '\n') {
                line_length++;
            } else if (maze->cols == -1) {
                maze->cols = line_length;
            }

            // Increment number of starts and ends and set their positions in the maze
            if (line[j] == 'S') {
                starts++;
                maze->start[0] = i;
                maze->start[1] = j;
            }

            if (line[j] == 'E') {
                ends++;
                maze->end[0] = i;
                maze->end[1] = j;
            }
        }

        // If the line length is not equal to the first line length, print error and exit
        if (line_length != maze->cols) {
            printf("Error: Maze must have constant width\n");
            exit(1);
        }
    }

    // Check number of rows, columns and exits if the maze is invalid
    check_maze_dimensions(maze->rows, "height");
    check_maze_dimensions(maze->cols, "width");

    check_maze_exits(starts, "start");
    check_maze_exits(ends, "end");
}
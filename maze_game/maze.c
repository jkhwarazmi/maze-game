/**
 * @file maze.c
 * @author Jamil Khwarazmi
 * @brief Maze source file - Used to create a maze from a file, validate and free it
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

/**
 * @brief Initialises a maze object by setting specific attributes to -1 for validate_file
 *
 * @param maze Pointer to the maze to be initialised
 */
void init_maze(Maze *maze)
{
    maze->cols = -1;
    maze->start[0] = -1;
    maze->end[0] = -1;
    maze->map = NULL;
}

/**
 * @brief Checks that the maze is within the required dimensions
 *
 * @param dimension The dimension to check
 * @param type The type of dimension, either "height" or "width"
 * @return int 0 if the dimension is valid, 1 if it is not
 */
int check_maze_dimensions(int dimension, const char *type)
{
    if (dimension < MIN_DIM)
    {
        printf("Error: Maze must have minimum %s of %d\n", type, MIN_DIM);
        return 1;
    }

    if (dimension > MAX_DIM)
    {
        printf("Error: Maze must have maximum %s of %d\n", type, MAX_DIM);
        return 1;
    }

    return 0;
}

/**
 * @brief Checks that the maze is valid
 *
 * @param file Pointer to the mazefile
 * @param maze Pointer to the maze struct to store width and height
 * @return int 0 if the maze is valid, 1 if it is not
 */
int validate_file(FILE *file, Maze *maze)
{
    // Set line buffer to slightly over MAX_DIM to account for newlines and invalid mazes
    int buffer = MAX_DIM + 10;
    char line[MAX_DIM + 10];
    int lines = 0;

    // Set maze_over to 0, used to check if the maze has invalid empty lines
    int maze_over = 0;

    while (fgets(line, buffer, file) != NULL)
    {
        lines++;

        // If any line is empty, any otherwise valid characters become invalid and set number of rows
        if (line[0] == '\n')
        {
            // If the maze should have ended, do not allow further newlines
            if (maze_over == 1)
            {
                return 1;
            }

            maze_over = 1;
            maze->rows = lines - 1;
            continue;
        }

        // Manually calculate line length to ignore invisible characters but use strlen for looping over all chars
        int line_length = 0;
        int length = strlen(line);

        for (int i = 0; i < length; i++)
        {
            // Check for invalid characters only if the maze is not over
            if (maze_over || !(line[i] == '#' || line[i] == ' ' || line[i] == 'S' || line[i] == 'E' || line[i] == '\n'))
            {
                return 2;
            }

            // Increment line length for each char that is not a newline or set cols to line length on first newline
            if (line[i] != '\n')
            {
                line_length++;
            }
            else if (maze->cols == -1)
            {
                maze->cols = line_length;
            }

            // Check for multiple starts/ends or otherwise set their positions
            if (line[i] == 'S')
            {
                if (maze->start[0] != -1)
                {
                    return 3;
                }
                maze->start[0] = lines - 1;
                maze->start[1] = i;
            }
            else if (line[i] == 'E')
            {
                if (maze->end[0] != -1)
                {
                    return 4;
                }
                maze->end[0] = lines - 1;
                maze->end[1] = i;
            }
        }

        // Check that the line length is constant
        if (line_length != maze->cols)
        {
            return 5;
        }
    }

    // If maze didn't end in a newline, set number of rows
    if (maze_over == 0)
    {
        maze->rows = lines;
    }

    // Check number of rows and columns and return if maze is not within the required dimensions
    if (check_maze_dimensions(maze->rows, "height") == 1 || check_maze_dimensions(maze->cols, "width") == 1)
    {
        return 6;
    }

    // Check that the maze has a start and end
    if (maze->start[0] == -1)
    {
        return 3;
    }
    else if (maze->end[0] == -1)
    {
        return 4;
    }

    rewind(file);
    return 0;
}

/**
 * @brief Print a file error message based on the error code
 *
 * @param error_code The error code to print the message for
 */
void print_maze_error(int error_code)
{
    switch (error_code)
    {
        case 1:
            printf("Error: Maze cannot end in multiple newlines\n");
            return;
        case 2:
            printf("Error: Invalid characters in maze\n");
            return;
        case 3:
            printf("Error: Maze must have exactly one start\n");
            return;
        case 4:
            printf("Error: Maze must have exactly one end\n");
            return;
        case 5:
            printf("Error: Maze must have constant width\n");
            return;
    }
}

/**
 * @brief Initialise a maze's map matrix
 *
 * @param maze Pointer to the maze struct to be initialised
 * @return int 0 on success, 1 on fail
 */
int create_maze(Maze *maze)
{
    maze->map = malloc(maze->rows * sizeof(char *));
    if (maze->map == NULL)
    {
        return 1;
    }

    for (int i = 0; i < maze->rows; i++)
    {
        maze->map[i] = malloc(maze->cols * sizeof(char));
        if (maze->map[i] == NULL)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Read in a mazefile into the maze struct
 *
 * @param file Mazefile pointer
 * @param maze Pointer to maze struct to fill
 * @return int 0 on success, 1 on fail
 */
int read_maze(FILE *file, Maze *maze)
{
    for (int i = 0; i < maze->rows; i++)
    {
        for (int j = 0; j < maze->cols; j++)
        {
            char node = fgetc(file);

            // Skip newlines and ensure file dimensions match maze dimensions
            if (node == '\n')
            {
                j--;
                continue;
            }
            else if (node == EOF)
            {
                return 1;
            }

            maze->map[i][j] = node;
        }
    }
    return 0;
}

/**
 * @brief Free the memory allocated to the maze struct
 *
 * @param maze Pointer to the maze struct to free
 */
void free_maze(Maze *maze)
{
    if (maze == NULL)
    {
        return;
    }

    if (maze->map != NULL)
    {
        for (int i = 0; i < maze->rows; i++)
        {
            if (maze->map[i] != NULL)
            {
                free(maze->map[i]);
                maze->map[i] = NULL;
            }
        }

        free(maze->map);
        maze->map = NULL;
    }

    free(maze);
}

/**
 * @file maze.c
 * @author Jamil Khwarazmi
 * @brief ADD BRIEF DESCRIPTION HERE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

// WHICH OF THESE FUNCTIONS ARE ACTUALLY USED (I.E. LOAD_MAZE ISN'T)

/**
 * @brief Checks that the maze is within the required dimensions
 * 
 * @param dimension The dimension to check
 * @param type The type of dimension, either "height" or "width"
*/
int check_maze_dimensions(int dimension, char *type) 
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
 * @brief Checks that the maze has exactly one start and one end
 * 
 * @param quantity The quantity of starts or ends
 * @param type The type of exit, either "start" or "end"
*/
int check_maze_exits(int quantity, char *type) 
{
    if (quantity != 1) 
    {
        printf("Error: Maze must have exactly one %s\n", type);
        return 1;
    }

    return 0;
}

/**
 * @brief Checks that the maze is valid
 * 
 * @param maze The maze struct the maze is stored in
*/
int validate_file(FILE *file, Maze *maze) 
{
    // Set buffer to slightly over MAX_DIM to account for newlines and invalid mazes
    // Split this up into further functions

    int buffer = MAX_DIM + 10;
    char line[MAX_DIM + 10];
    int lines = 0;

    // Set cols to -1 so it only changes for first line
    maze->cols = -1;
    
    // Set number of start and end points to 0
    int maze_starts = 0;
    int maze_ends = 0;

    // Set maze_over to 0, used to check if the maze has empty lines
    int maze_over = 0;

    // Read each line of the file and store it in the maze map
    while (fgets(line, buffer, file) != NULL) 
    {
        lines++;

        // If any line is empty, any otherwise valid characters become invalid and set number of rows
        if (line[0] == '\n') 
        {
            if (maze_over == 1)
            {
                printf("Error: Maze cannot end in multiple newlines\n");
                return 1;
            }

            maze_over = 1;
            maze->rows = lines - 1;
            continue;
        }

        // Manually calculate line length to remove invisible characters but use strlen for looping over all chars
        int line_length = 0;
        int length = strlen(line);

        for (int i = 0; i < length; i++) 
        {
            // If any character is not a valid maze character, print error and exit
            if ((line[i] != '#' && line[i] != ' ' && line[i] != 'S' && line[i] != 'E' && line[i] != '\n') || maze_over) 
            {
                printf("Error: Invalid characters in maze\n");
                return 1;
            }

            // Increment line length for each character that is not a newline or set cols to first line length
            if (line[i] != '\n') 
            {
                line_length++;
            } 
            else if (maze->cols == -1) 
            {
                maze->cols = line_length;
            }

            // Increment number of starts and ends and set their positions in the maze
            if (line[i] == 'S') 
            {
                maze_starts++;
                maze->start[0] = lines - 1;
                maze->start[1] = i;
            }

            if (line[i] == 'E') 
            {
                maze_ends++;
                maze->end[0] = lines - 1;
                maze->end[1] = i;
            }
        }

            // If the line length is not equal to the first line length, print error and return
            if (line_length != maze->cols) 
            {
                printf("Error: Maze must have constant width\n");
                return 1;
            }
    }
    
    // If maze didn't end in a newline, set number of rows
    if (maze_over == 0) 
    {
        maze->rows = lines;
    }

    // Check number of rows, columns and exits if the maze is invalid
    if (check_maze_dimensions(maze->rows, "height") || check_maze_dimensions(maze->cols, "width"))
    {
        return 1;
    }

    if (check_maze_exits(maze_starts, "start") || check_maze_exits(maze_ends, "end"))
    {
        return 1;
    }

    // Reset file pointer
    rewind(file);
    return 0;
}

/**
 * @brief Initialise a maze object - allocate memory and set attributes
 *
 * @param maze pointer to the maze to be initialised
 * @return int 0 on success, 1 on fail
 */
int create_maze(Maze *maze)
{
    if (maze == NULL) 
    {
        return 1;
    }

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
 * @brief Free the memory allocated to the maze struct
 *
 * @param maze the pointer to the struct to free
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
            free(maze->map[i]);
            maze->map[i] = NULL;
        }
    }

    free(maze->map);
    maze->map = NULL;

    free(maze);
}

/**
 * @brief read in a maze file into a struct
 *
 * @param maze Maze struct to be used
 * @param file Mazefile pointer
 * @return int 0 on success, 1 on fail
 */
int read_maze(Maze *maze, FILE *file)
{
    // Something like this, add extra validation
    // Look at my original solution
    if (maze == NULL || file == NULL) 
    {
        return 1;
    }

    for (int i = 0; i < maze->rows; i++) 
    {
        for (int j = 0; j < maze->cols; j++) 
        {
            char tile = fgetc(file);

            if (tile == '\n') 
            {
                j--;
                continue;
            }
            else if (tile == EOF)
            {
                return 1;
            }

            maze->map[i][j] = tile;
        }
    }
    return 0;
}

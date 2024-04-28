/**
 * @file main.c
 * @author Jamil Khwarazmi
 * @brief Main code for the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "player.h"

// Define the required autograder exit codes
// Should errors go in separate header file?
// In headers, check whether imports are needed
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3
#define EXIT_OTHER_ERROR 100

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <mazefile path>\n", argv[0]);
        return EXIT_ARG_ERROR;
    }

    // Remember to free anything allocated in this function before returning
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) 
    {
        printf("Error: Could not open file\n");
        return EXIT_FILE_ERROR;
    }

    Maze *maze = malloc(sizeof(Maze));
    if (maze == NULL) 
    {
        printf("Error: Could not create maze\n");
        return EXIT_OTHER_ERROR;
    }

    // Need to return int value 1 for sucess, 0 for failure
    // Also put maze height and width into the maze struct
    // Close file at end of validate_maze
    if (validate_file(file, maze) == 1)
    {
        free_maze(maze);
        fclose(file);
        return EXIT_MAZE_ERROR;
    }

    if (create_maze(maze) == 1) 
    {
        printf("Error: Could not create maze\n");
        fclose(file);
        free_maze(maze);
        return EXIT_OTHER_ERROR;
    }

    // We do this so often, maybe it should be a function?
    if (read_maze(maze, file) == 1) 
    {
        printf("Error: Could not create maze\n");
        fclose(file);
        free_maze(maze);
        return EXIT_OTHER_ERROR;
    }

    fclose(file);
    printf("Maze %s (%dx%d) successfully loaded\n", argv[1], maze->rows, maze->cols);
    fflush(stdout);

    // Set player position to the start of the maze and their move count to 0
    Player *player = malloc(sizeof(Player));
    if (create_player(player, maze) == 1) 
    {
        printf("Error: Could not create player\n");
        free_maze(maze);
        free(player);
        return EXIT_OTHER_ERROR;
    }

    if (play_game(player, maze) == 1) 
    {
        // Change wording to completed
        printf("\nCongratulations! You escaped the maze in %d moves.\n", player->moves);
    }

    free_maze(maze);
    free(player);
    return EXIT_SUCCESS;
}

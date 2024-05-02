/**
 * @file main.c
 * @author Jamil Khwarazmi
 * @brief Main code for the maze game
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "player.h"

// Required autograder exit codes
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
        fclose(file);
        return EXIT_OTHER_ERROR;
    }

    // Sets initial values for maze attributes to be modified in validate_file
    init_maze(maze);

    // Check that the maze file is valid else print specific error
    int invalid_file = validate_file(file, maze);
    if (invalid_file != 0)
    {
        print_maze_error(invalid_file);
        fclose(file);
        free_maze(maze);
        return EXIT_MAZE_ERROR;
    }

    // Check that we can create the maze matrix and then fill it from the file
    if (create_maze(maze) == 1 || read_maze(file, maze) == 1)
    {
        printf("Error: Could not create maze\n");
        fclose(file);
        free_maze(maze);
        return EXIT_OTHER_ERROR;
    }

    fclose(file);
    printf("Maze %s (%dx%d) successfully loaded\n", argv[1], maze->rows, maze->cols);
    fflush(stdout);

    // Validate player allocated properly and set their position to the start of the maze and their move count to 0
    Player *player = malloc(sizeof(Player));
    if (create_player(player, maze) == 1)
    {
        printf("Error: Could not create player\n");
        free_maze(maze);
        free(player);
        return EXIT_OTHER_ERROR;
    }

    // Keep playing the game until the player reaches the end of the maze
    if (play_game(player, maze) == 1)
    {
        printf("\nCongratulations! You completed the maze in %d moves.\n", player->moves);
    }

    free_maze(maze);
    free(player);
    return EXIT_SUCCESS;
}

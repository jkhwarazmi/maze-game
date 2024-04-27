#include <stdio.h>
#include "maze.h"
#include "player.h"


int main(int argc, char *argv[]) {
    
    // If not 2 arguments, print usage and exit
    if (argc != 2) {
        printf("Usage: %s <maze file>\n", argv[0]);
        return 0;
    }

    // If file cannot be opened, print error and exit
    FILE *file = fopen(argv[1], "r");

    if (!file) {
        printf("Error: Could not open file\n");
        return 1;
    }
    
    // Create new maze
    Maze maze;

    // Load the maze and check its validity
    load_maze(file, &maze);
    validate_maze(&maze);

    // Display maze loaded message and flush stdout
    printf("Maze %s (%dx%d) successfully loaded\n", argv[1], maze.rows, maze.cols);
    fflush(stdout);

    // Set player position to the start of the maze and their move count to 0
    Player player = {maze.start[0], maze.start[1], 0};

    // Play the game
    if (play_game(&maze, &player)) {
        printf("\nCongratulations! You escaped the maze in %d moves.\n", player.moves);
    }

    return 0;
}

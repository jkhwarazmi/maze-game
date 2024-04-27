#include <stdio.h>
#include <string.h>
#include "player.h"

/**
 * @brief Determines the player's move from their input
 * 
 * @return char The player's move or '0' if the input is invalid
 
*/
char get_move() {

    // Ask the player for their move and store it as a string
    printf("\nYour move (WASD or M for the map): ");
    char input[100];

    fgets(input, sizeof(input), stdin);

    // If the input is not 2 characters long, return error char
    if (strlen(input) != 2) {
        return '0';
    }

    // If the input is valid, return the first character
    return input[0];
}

/**
 * @brief Moves the player up or down if a valid move is possible
 * 
 * @param maze The maze the player is in
 * @param player The player's struct with their position
 * @param direction The direction the player wants to move in, 1 for up, -1 for down
*/
void move_y(Maze *maze, Player *player, int direction) {

    // Determine potential new y position
    int new_y = player->y - direction;

    // Check the new position doesn't go out of bounds or into a wall
    if (new_y < 0 || new_y >= maze->rows) {
        printf("\nYou cannot walk out of bounds\n");
        return;
    }
    
    if (maze->map[new_y][player->x] == '#') {
        printf("\nYou cannot walk into walls\n");
        return;
    }
    
    // If the move is valid, increment the player's move count and update their position
    player->moves++;
    player->y = new_y;
    
    printf("\nYou move %s\n", direction == 1 ? "up" : "down");
}

/**
 * @brief Moves the player left or right if a valid move is possible
 * 
 * @param maze The maze the player is in
 * @param player The player's struct with their position
 * @param direction The direction the player wants to move in, 1 for left, -1 for right
*/
void move_x(Maze *maze, Player *player, int direction) {

    // Determine potential new x position
    int new_x = player->x - direction;

    // Check the new position doesn't go out of bounds or into a wall
    if (new_x < 0 || new_x >= maze->cols) {
        printf("\nYou cannot walk out of bounds\n");
        return;
    }

    if (maze->map[player->y][new_x] == '#') {
        printf("\nYou cannot walk into walls\n");
        return;
    } 
    
    // If the move is valid, increment the player's move count and update their position
    player->moves++;
    player->x = new_x;
    printf("\nYou move %s\n", direction == 1 ? "left" : "right");
}

/**
 * @brief Prints the maze with the player's position
 * 
 * @param maze The maze the player is in
 * @param player The player's struct with their position
*/
void print_maze(Maze *maze, Player *player) {

    printf("\n");
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            
            // Print 'S' and 'E' preferentially to the player's position
            if (i == player->y && j == player->x && maze->map[i][j] != 'S' && maze->map[i][j] != 'E') {
                printf("X");
            } else {
                printf("%c", maze->map[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * @brief Plays the game until the player reaches the end of the maze
 * 
 * @param maze The maze the player is in
 * @param player The player's struct with their position and moves
 * @return int 1 when the player reaches the end of the maze
*/
int play_game(Maze *maze, Player *player) {

    // Play the game until the player reaches the end
    while (1) {
        
        // If the player reaches the end, return 1
        if (player->y == maze->end[0] && player->x == maze->end[1]) {
            return 1;
        }

        // Get the player's move and continue if invalid
        char input = get_move();

        if (input == '0') {
            printf("\nPlease enter a valid direction (W, A, S or D to move or M to view the map)\n");
            continue;
        }

        // Move the player in the direction they chose
        switch (input) {
            case 'W':
            case 'w':
                move_y(maze, player, 1);
                break;
            case 'A':
            case 'a':
                move_x(maze, player, 1);
                break;
            case 'S':
            case 's':
                move_y(maze, player, -1);
                break;
            case 'D':
            case 'd':
                move_x(maze, player, -1);
                break;
            case 'M':
            case 'm':
                print_maze(maze, player);
                break;
            default:
                printf("\nPlease enter a valid direction (W, A, S or D to move or M to view the map)\n");
                break;
        }   
    }
}
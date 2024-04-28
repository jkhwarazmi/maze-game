/**
 * @file player.c
 * @author Jamil Khwarazmi
 * @brief ADD BRIEF DESCRIPTION HERE
 */

#include <stdio.h>
#include <string.h>
#include "player.h"

/**
 * @brief Determines the player's move from their input
 * 
 * @return char The player's move or '0' if the input is invalid
 
*/
char get_move() 
{
    // BIG PROBLEM: IF WE GO OVER 100 CHARACTERS, WE WILL OVERFLOW THE BUFFER

    // Ask the player for their move and store it as a string
    printf("\nYour move (WASD or M for the map): ");
    char input[4];

    // Make size of input a const and define it in .h
    fgets(input, sizeof(input), stdin);

    // If buffer overflow, clear the buffer, create GPT reference chat for this
    // https://chat.openai.com/share/3f0e6739-a098-4435-8a46-5bb6736af863
    if (input[strlen(input) - 1] != '\n') 
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // If the input is not 2 characters long, return error char
    if (strlen(input) != 2) 
    {
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
void move_y(Player *player, Maze *maze, int direction) 
{

    // Determine potential new y position
    int new_y = player->y - direction;

    // Check the new position doesn't go out of bounds or into a wall
    if (new_y < 0 || new_y >= maze->rows) 
    {
        printf("\nYou cannot walk out of bounds\n");
        return;
    }
    
    if (maze->map[new_y][player->x] == '#') 
    {
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
void move_x(Player *player, Maze *maze, int direction) 
{

    // Determine potential new x position
    int new_x = player->x - direction;

    // Check the new position doesn't go out of bounds or into a wall
    if (new_x < 0 || new_x >= maze->cols) 
    {
        printf("\nYou cannot walk out of bounds\n");
        return;
    }

    if (maze->map[player->y][new_x] == '#') 
    {
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
void print_maze(Player *player, Maze *maze) 
{
    printf("\n");
    for (int i = 0; i < maze->rows; i++) 
    {
        for (int j = 0; j < maze->cols; j++) 
        {
            if (i == player->y && j == player->x) 
            {
                printf("X");
            } 
            else 
            {
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
int play_game(Player *player, Maze *maze) 
{

    // Play the game until the player reaches the end
    while (1) 
    {
        
        // If the player reaches the end, return 1
        if (player->y == maze->end[0] && player->x == maze->end[1]) 
        {
            return 1;
        }

        // Get the player's move and continue if invalid
        char input = get_move();

        if (input == '0') 
        {
            printf("\nPlease enter a valid direction (W, A, S or D to move or M to view the map)\n");
            continue;
        }

        // Move player in the direction they chose: 1 for up/left, -1 for down/right or print map
        switch (input) 
        {
            case 'W':
            case 'w':
                move_y(player, maze, 1);
                break;
            case 'A':
            case 'a':
                move_x(player, maze, 1);
                break;
            case 'S':
            case 's':
                move_y(player, maze, -1);
                break;
            case 'D':
            case 'd':
                move_x(player, maze, -1);
                break;
            case 'M':
            case 'm':
                print_maze(player, maze);
                break;
            default:
                printf("\nPlease enter a valid direction (W, A, S or D to move or M to view the map)\n");
                break;
        }   
    }
}

int create_player(Player *player, Maze *maze)
{
    if (player == NULL) 
    {
        return 1;
    }

    player->y = maze->start[0];
    player->x = maze->start[1];
    player->moves = 0;

    return 0;
}
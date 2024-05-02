/**
 * @file player.c
 * @author Jamil Khwarazmi
 * @brief Player source file - Used to create a player, move them and play the game
 */

#include <stdio.h>
#include <string.h>
#include "player.h"

/**
 * @brief Initialises a player struct with the starting position of the maze
 *
 * @param player Pointer to the player struct to be initialised
 * @param maze Pointer to the maze the player is in
 * @return int 0 if the player is created successfully, 1 if the player is NULL
 */
int create_player(Player *player, const Maze *maze)
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

/**
 * @brief Determines the player's move from their input
 *
 * @return char The player's move or '0' if the input is invalid
 */
char get_move()
{
    printf("\nYour move (WASD or M for the map): ");

    int buffer = 4;
    char input[buffer];
    int input_length;

    if (fgets(input, buffer, stdin) == NULL)
    {
        return '0';
    }

    input_length = strlen(input);

    // Clear the input buffer if the input is too long, adapted from: https://chat.openai.com/share/3f0e6739-a098-4435-8a46-5bb6736af863
    if (input[input_length - 1] != '\n')
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // If the input is not 2 characters long, return 'error char' else first character
    if (input_length != 2)
    {
        return '0';
    }

    return input[0];
}

/**
 * @brief Moves the player up or down if a valid move is possible
 *
 * @param player Pointer to the player's struct with their position
 * @param maze Pointer to the maze the player is in
 * @param direction The direction the player wants to move in, 1 for up, -1 for down
 */
void move_y(Player *player, const Maze *maze, int direction)
{
    int new_y = player->y - direction;

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

    player->moves++;
    player->y = new_y;

    printf("\nYou move %s\n", direction == 1 ? "up" : "down");
}

/**
 * @brief Moves the player left or right if a valid move is possible
 *
 * @param player Pointer to the player's struct with their position
 * @param maze Pointer to the maze the player is in
 * @param direction The direction the player wants to move in, 1 for left, -1 for right
 */
void move_x(Player *player, const Maze *maze, int direction)
{
    int new_x = player->x - direction;

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

    player->moves++;
    player->x = new_x;

    printf("\nYou move %s\n", direction == 1 ? "left" : "right");
}

/**
 * @brief Prints the maze with the player's position
 *
 * @param player Pointer to the player's struct with their position
 * @param maze Pointer to the maze the player is in
 */
void print_maze(Player *player, const Maze *maze)
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
 * @param player Pointer to the player's struct with their position and moves
 * @param maze Pointer to the maze the player is in
 * @return int 1 when the player reaches the end of the maze
 */
int play_game(Player *player, const Maze *maze)
{
    while (1)
    {
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

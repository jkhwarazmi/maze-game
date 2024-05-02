/**
 * @file player.h
 * @author Jamil Khwarazmi
 * @brief Player header file - Used to create a player, move them and play the game
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "maze.h"

/**
 * @brief Struct to hold player data, includes integer y and x positions referring to
 *        their current row and col respectively and an integer count of all valid moves.
 *
 */
typedef struct
{
    int y;
    int x;
    int moves;
} Player;

int create_player(Player *player, const Maze *maze);
char get_move();
void move_y(Player *player, const Maze *maze, int direction);
void move_x(Player *player, const Maze *maze, int direction);
void print_maze(Player *player, const Maze *maze);
int play_game(Player *player, const Maze *maze);

#endif /* PLAYER */

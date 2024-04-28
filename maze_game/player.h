/**
 * @file player.h
 * @author Jamil Khwarazmi
 * @brief ADD BRIEF DESCRIPTION HERE
 */

#ifndef PLAYER_H 
#define PLAYER_H

#include "maze.h"

/**
 * @brief Struct to hold player data, includes integer y and x positions and an
 *        integer count of all valid moves.
 * 
*/
typedef struct 
{
    int y;
    int x;
    int moves;
} Player;

char get_move();
void move_y(Player *player, Maze *maze, int direction);
void move_x(Player *player, Maze *maze, int direction);
void print_maze(Player *player, Maze *maze);
int play_game(Player *player, Maze *maze);
int create_player(Player *player, Maze *maze);

#endif /* PLAYER */

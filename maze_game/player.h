#ifndef PLAYER_H 
#define PLAYER_H

#include "maze.h"

/**
 * @brief Struct to hold player data, includes integer y and x positions and an
 *        integer count of all valid moves.
 * 
*/
typedef struct {
    int y;
    int x;
    int moves;
} Player;

char get_move();
void move_y(Maze *maze, Player *player, int direction);
void move_x(Maze *maze, Player *player, int direction);
void print_maze(Maze *maze, Player *player);
int play_game(Maze *maze, Player *player);

#endif /* PLAYER */
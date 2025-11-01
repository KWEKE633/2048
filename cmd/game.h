#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include "../pkg/libft.h"

#define MAX 5

typedef struct s_game
{
    int board[MAX][MAX];
    int N;
    int score;
    // int best;
    // int cell_w;
    // int cell_h;
    // int start_row;
    // int start_col;
} Game;

void game_init(Game *g);
void game_reset(Game *g, int N);
void game_add_random(Game *g);
int  game_can_move(Game *g);

int move_left(Game *g);
int move_right(Game *g);
int move_up(Game *g);
int move_down(Game *g);

int load_best_score(void);
void save_best_score(int best);

#endif

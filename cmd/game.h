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
    int best;
    // int cell_w;
    // int cell_h;
    // int start_row;
    // int start_col;
} Game;

int load_best_score(void);
void save_best_score(int best);

void init_colors(void);
int color_for_value(int v);

#endif

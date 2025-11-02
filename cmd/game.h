#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <signal.h>

#include "../pkg/libft.h"

#define MAX 5

extern volatile sig_atomic_t g_resize_flag;
extern volatile sig_atomic_t g_int;

enum e_const {
  WIN_VALUE = 2048,
};

enum e_window_flag {
  WINDOW_MIN_WIDTH = 32,
  WINDOW_MIN_HEIGHT = 15,

  SCREEN_SIZE_OK = 0,
  SCREEN_SIZE_TOO_SMALL = 1
};

#define MAX_RAIN 100

typedef struct {
    int x, y;
    char ch;
    int color;
    int speed;
} t_raindrop;

typedef struct {
  char *lines[7];
  int width;
  int height;
} aa_char_t;

#define AA_ZERO {{" ::::::: ", \
                  ":+:   :+:", \
                  "+:+   +:+", \
                  "+#+   +:+", \
                  "+#+   +#+", \
                  "#+#   #+#", \
                  " ####### "}, 9, 7}

#define AA_ONE {{"  :::  ", \
                 ":+:+:  ", \
                 "  +:+  ", \
                 "  +#+  ", \
                 "  +#+  ", \
                 "  #+#  ", \
                 "#######"}, 7, 7}

#define AA_TWO {{" :::::::: ", \
                 ":+:    :+:", \
                 "      +:+ ", \
                 "    +#+   ", \
                 "  +#+     ", \
                 " #+#      ", \
                 "##########"}, 10, 7}

#define AA_THREE {{" :::::::: ", \
                   ":+:    :+:", \
                   "       +:+", \
                   "    +#++: ", \
                   "       +#+", \
                   "#+#    #+#", \
                   " ######## "}, 10, 7}

#define AA_FOUR {{"    :::    ", \
                  "   :+:     ", \
                  "  +:+ +:+  ", \
                  " +#+  +:+  ", \
                  "+#+#+#+#+#+", \
                  "      #+#  ", \
                  "      ###  "}, 11, 7}

#define AA_FIVE {{"::::::::::", \
                  ":+:    :+:", \
                  "+:+       ", \
                  "+#++:++#+ ", \
                  "       +#+", \
                  "#+#    #+#", \
                  " ######## "}, 10, 7}

#define AA_SIX {{" :::::::: ", \
                 ":+:    :+:", \
                 "+:+       ", \
                 "+#++:++#+ ", \
                 "+#+    +#+", \
                 "#+#    #+#", \
                 " ######## "}, 10, 7}

#define AA_SEVEN {{":::::::::::", \
                   ":+:     :+:", \
                   "       +:+ ", \
                   "      +#+  ", \
                   "     +#+   ", \
                   "    #+#    ", \
                   "    ###    "}, 11, 7}

#define AA_EIGHT {{" :::::::: ", \
                   ":+:    :+:", \
                   "+:+    +:+", \
                   " +#++:++# ", \
                   "+#+    +#+", \
                   "#+#    #+#", \
                   " ######## "}, 10, 7}

#define AA_NINE {{" :::::::: ", \
                  ":+:    :+:", \
                  "+:+    +:+", \
                  " +#++:++#+", \
                  "       +#+", \
                  "#+#    #+#", \
                  " ######## "}, 10, 7}


#define AA_TITLE {{"       ::::::::   :::::::      :::      :::::::: ", \
                   "     :+:    :+: :+:   :+:    :+:      :+:    :+: ", \
                   "          +:+  +:+   +:+   +:+ +:+   +:+    +:+  ", \
                   "       +#+    +#+   +:+  +#+  +:+    +#++:++#    ", \
                   "    +#+      +#+   +#+ +#+#+#+#+#+ +#+    +#+    ", \
                   "  #+#       #+#   #+#       #+#   #+#    #+#     ", \
                   "##########  #######        ###    ########.fr    "}, 49 , 7}

typedef struct s_game {
  int board[MAX][MAX];
  int N;
  int score;
  int best;
  // int cell_w;
  // int cell_h;
  // int start_row;
  // int start_col;
} Game;

// presentation.c
int draw_menu(int high_score);
int handle_resize();
void draw_board(Game *g);
int draw_win_modal(int win_value);

int load_best_score(void);
void save_best_score(int best);

void init_colors(void);
int color_for_value(int v);

#endif /* GAME_H */

#include "game.h"

int handle_resize() {
  endwin();
  refresh();
  clear();

  // ウィンドウのサイズ
  int min_height = WINDOW_MIN_HEIGHT;
  int min_width = WINDOW_MIN_WIDTH;

  // 画面サイズが小さすぎる場合の対処
  if (LINES < min_height || COLS < min_width) {
    mvprintw(LINES / 2, (COLS - 20) / 2, "Window too small!");
    refresh();
    return SCREEN_SIZE_TOO_SMALL;
  }
  timeout(0);
  return SCREEN_SIZE_OK;
}

int draw_menu(int high_score __attribute__((__unused__))) {
  clear();

  int init = 1;
  int res = SCREEN_SIZE_OK;
  while (1) {
    if (init || g_resize_flag) {
      res = handle_resize();
      init = 0;
      g_resize_flag = 0;
      if (res == SCREEN_SIZE_OK) {
        mvprintw(3, 2, "=== 2048 MENU ===");
        mvprintw(5, 4, "1) 4x4");
        mvprintw(6, 4, "2) 5x5");
        mvprintw(8, 4, "ESC to quit");
        refresh();
      }
    }
    if (g_int)
      return -1;
    int ch = getch();
    if (res == SCREEN_SIZE_TOO_SMALL) {
      continue;
    }
    if (ch == '1')
      return 4;
    if (ch == '2')
      return 5;
    if (ch == 27)
      return -1;
  }
}

void draw_board(Game *g) {
  aa_char_t aa_digits[] = {AA_ZERO, AA_ONE, AA_TWO,   AA_THREE, AA_FOUR,
                           AA_FIVE, AA_SIX, AA_SEVEN, AA_EIGHT, AA_NINE};
  (void) aa_digits;
  clear();
  mvprintw(0, (COLS - 30) / 2, "2048 (arrows to move, q exit)");
  mvprintw(1, (COLS - 14) / 2, "Score: %06d", g->score);

  for (int i = 0; i < g->N; i++) {
    for (int j = 0; j < g->N; j++) {
      int val = g->board[i][j];
      int cp = color_for_value(val);

      if (val == 0) {
        mvprintw(3 + i * 2, j * 6, "  .  ");
      } else {
        if (cp)
          attron(COLOR_PAIR(cp) | A_BOLD);
        mvprintw(3 + i * 2, j * 6, "%4d ", val);
        if (cp)
          attroff(COLOR_PAIR(cp) | A_BOLD);
      }
    }
  }
  refresh();
}

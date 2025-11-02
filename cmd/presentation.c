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
  timeout(100);
  return SCREEN_SIZE_OK;
}

int draw_menu(int high_score) {
  clear();

  aa_char_t aa_title = AA_TITLE;
  char *choices[] = {
      "1) 4 x 4",
      "2) 5 x 5",
      "EXIT",
  };
  t_raindrop rain[MAX_RAIN];
  for (int i = 0; i < MAX_RAIN; i++) {
    rain[i].x = rand() % COLS;
    rain[i].y = rand() % LINES;
    rain[i].ch = rand() % 94 + 33;
    rain[i].color = rand() % 7 + 1;
    rain[i].speed = rand() % 5 + 1;
  }

  int n_choices = sizeof(choices) / sizeof(char *);
  int highlight = 0;
  int i;

  int init = 1;
  int res = SCREEN_SIZE_OK;
  while (1) {
    if (init || g_resize_flag) {
      res = handle_resize();
      init = 0;
      g_resize_flag = 0;
    }

    if (res == SCREEN_SIZE_OK) {
      clear();

      for (int i = 0; i < MAX_RAIN; i++) {
        attron(COLOR_PAIR(rain[i].color));
        mvaddch(rain[i].y, rain[i].x, ' ');
        rain[i].y += rain[i].speed;
        if (rain[i].y >= LINES) {
          rain[i].y = 0;
          rain[i].x = rand() % COLS;
        }
        mvaddch(rain[i].y, rain[i].x, rain[i].ch);
        attroff(COLOR_PAIR(rain[i].color));
      }

      int title_start_row;
      int header_end_line;
      if (COLS >= aa_title.width && LINES >= aa_title.height + 15) {
        int title_col = (COLS - aa_title.width) / 2;
        title_start_row = 3;
        for (int i = 0; i < aa_title.height; i++) {
          mvprintw(title_start_row + i, title_col, "%s", aa_title.lines[i]);
        }
        header_end_line = title_start_row + aa_title.height + 2;
        mvprintw(header_end_line, (COLS - 37) / 2,
                 "- - - - - - - The game - - - - - - -");
      } else {
        mvprintw(3, (COLS - 5) / 2, "2048");
        header_end_line = 5;
        mvprintw(header_end_line, (COLS - 13) / 2, "- The game -");
      }

      for (i = 0; i < n_choices; i++) {
        if (highlight == i) { // 選択中の項目
          attron(A_REVERSE);  // ハイライト（反転表示）をON
          header_end_line += 2;
          mvprintw(header_end_line, (COLS) / 2 - 5, "%s", choices[i]);
          attroff(A_REVERSE); // ハイライトをOFF
        } else {
          header_end_line += 2;
          mvprintw(header_end_line, (COLS) / 2 - 5, "%s", choices[i]);
        }
      }
      header_end_line += 2;
      mvprintw((LINES - header_end_line) / 2 + header_end_line, (COLS - 17) / 2,
               "Best Score: %5d", high_score);
      refresh();
    }

    if (g_int)
      return -1;

    int ch = getch();
    if (res == SCREEN_SIZE_TOO_SMALL) {
      continue;
    }
    switch (ch) {
    case KEY_UP:
      if (highlight == 0)
        highlight = n_choices - 1;
      else
        --highlight;
      break;
    case KEY_DOWN:
      if (highlight == n_choices - 1)
        highlight = 0;
      else
        ++highlight;
      break;
    case '1':
      return 4;
    case '2':
      return 5;
    case 10: // Enter
      if (highlight == 0)
        return 4;
      else if (highlight == 1)
        return 5;
      else if (highlight == 2)
        return -1;
      break;
    case 27: // Escape
      return -1;
    }
  }
}

static int extract_digits(int val, int digits[]) {
  if (val == 0) {
    digits[0] = 0;
    return 1;
  }

  int num_digits = 0;
  int temp = val;

  while (temp > 0) {
    num_digits++;
    temp /= 10;
  }
  temp = val;
  for (int i = num_digits - 1; i >= 0; i--) {
    digits[i] = temp % 10;
    temp /= 10;
  }
  return num_digits;
}

static int calculate_aa_width(const int digits[], int num_digits,
                              const aa_char_t aa_digits[]) {
  int total_width = 0;
  for (int i = 0; i < num_digits; i++) {
    total_width += aa_digits[digits[i]].width;
  }
  if (num_digits > 1) {
    total_width += (num_digits - 1);
  }

  return total_width;
}

static void render_aa_value(int val, int start_row, int start_col) {
  aa_char_t aa_digits[] = {AA_ZERO, AA_ONE, AA_TWO,   AA_THREE, AA_FOUR,
                           AA_FIVE, AA_SIX, AA_SEVEN, AA_EIGHT, AA_NINE};

  int digits[5] = {0};
  int num_digits = extract_digits(val, digits);

  for (int line = 0; line < 7; line++) {
    int col_offset = 0;

    for (int d = 0; d < num_digits; d++) {
      int digit = digits[d];
      aa_char_t *aa = &aa_digits[digit];

      mvprintw(start_row + line, start_col + col_offset, "%s", aa->lines[line]);
      col_offset += aa->width;

      if (d < num_digits - 1) {
        col_offset += 1;
      }
    }
  }
}

void draw_board(Game *g) {
  aa_char_t aa_digits[] = {AA_ZERO, AA_ONE, AA_TWO,   AA_THREE, AA_FOUR,
                           AA_FIVE, AA_SIX, AA_SEVEN, AA_EIGHT, AA_NINE};

  clear();
  mvprintw(0, (COLS - 32) / 2, "2048 (arrows to move, ESC exit)");
  mvprintw(1, (COLS - 14) / 2, "Score: %06d", g->score);

  int available_width_per_tile = COLS / g->N;
  int available_height_per_tile = (LINES - 2) / g->N;

  for (int i = 0; i < g->N; i++) {
    for (int j = 0; j < g->N; j++) {
      int val = g->board[i][j];
      int cp = color_for_value(val);

      int digits[5] = {0};
      int num_digits = extract_digits(val, digits);
      int aa_width = calculate_aa_width(digits, num_digits, aa_digits);
      int aa_height = 7;

      if (cp)
        attron(COLOR_PAIR(cp) | A_BOLD);

      int tile_start_row = 2 + i * available_height_per_tile;
      int tile_start_col = j * available_width_per_tile;

      if (aa_width <= available_width_per_tile &&
          aa_height <= available_height_per_tile && num_digits <= 5) {

        int padding_top = (available_height_per_tile - aa_height) / 2;
        int padding_left = (available_width_per_tile - aa_width) / 2;

        int art_start_row = tile_start_row + padding_top;
        int art_start_col = tile_start_col + padding_left;
        if (val != 0)
          render_aa_value(val, art_start_row, art_start_col);
      } else {
        int padding_top = (available_height_per_tile - 1) / 2;
        int padding_left = (available_width_per_tile - num_digits - 1) / 2;

        int art_start_row = tile_start_row + padding_top;
        int art_start_col = tile_start_col + padding_left;
        if (val != 0)
          mvprintw(art_start_row, art_start_col, "%d", val);
      }
      if (cp)
        attroff(COLOR_PAIR(cp) | A_BOLD);
    }
  }
  refresh();
}

int draw_win_modal(int win_value) {
  int res = SCREEN_SIZE_OK;

  while (1) {
    if (g_resize_flag) {
      res = handle_resize();
      g_resize_flag = 0;
    }

    if (res == SCREEN_SIZE_OK) {
      int msg_row = LINES / 2 - 1;

      // 強調表示
      attron(A_REVERSE | A_BOLD);
      mvprintw(msg_row, (COLS - 17) / 2, "You reached %5d", win_value);
      mvprintw(msg_row + 2, (COLS - 16) / 2, "Continue? (y/n)");
      attroff(A_REVERSE | A_BOLD);
      refresh();
    }

    if (g_int)
      return -1;
    int ch = getch();
    if (res == SCREEN_SIZE_TOO_SMALL) {
      continue;
    }
    if (ch == 'y' || ch == 'Y')
      return 1;
    else if (ch == 'n' || ch == 'N')
      return 0;
  }
}

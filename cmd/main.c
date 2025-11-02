#include "game.h"
#include <signal.h>
#include <time.h>

volatile sig_atomic_t g_resize_flag = 0;
volatile sig_atomic_t g_int = 0;

static void handle_winch(int sig __attribute__((__unused__))) {
  g_resize_flag = 1;
}

static void handle_sigint(int sig __attribute__((__unused__))) { g_int = 1; }

void init_board(Game *g) {
  for (int i = 0; i < g->N; i++)
    for (int j = 0; j < g->N; j++)
      g->board[i][j] = 0;

  for (int k = 0; k < 2; k++) {
    int empties[25];
    int n = 0;
    for (int i = 0; i < g->N; i++)
      for (int j = 0; j < g->N; j++)
        if (g->board[i][j] == 0)
          empties[n++] = i * g->N + j;

    int r = empties[rand() % n];
    int x = r / g->N;
    int y = r % g->N;
    g->board[x][y] = (rand() % 10 < 9) ? 2 : 4;
  }
}

int count_2048(Game *g) {
  int cnt = 0;
  for (int i = 0; i < g->N; i++)
    for (int j = 0; j < g->N; j++)
      if (g->board[i][j] == WIN_VALUE)
        cnt++;
  return cnt;
}


int is_full(Game *g) {
  for (int i = 0; i < g->N; i++)
    for (int j = 0; j < g->N; j++)
      if (g->board[i][j] == 0)
        return 0;
  return 1;
}

int is_won(Game *g) {
  for (int i = 0; i < g->N; i++)
    for (int j = 0; j < g->N; j++)
      if (g->board[i][j] == WIN_VALUE)
        return 1;
  return 0;
}

int can_move(Game *g, int ex) {
  for (int i = 0; i < g->N; i++) {
    for (int j = 0; j < g->N; j++) {
      if (g->board[i][j] == 0)
        return 1;
      if (j < g->N - 1 && g->board[i][j] == g->board[i][j + 1]) {
        if (!(ex && g->board[i][j] == WIN_VALUE))
          return 1;
      }
      if (i < g->N - 1 && g->board[i][j] == g->board[i + 1][j]) {
        if (!(ex && g->board[i][j] == WIN_VALUE))
          return 1;
      }
    }
  }
  return 0;
}

int mov(int dir, Game *g, int ex) {
  int moved = 0;
  int prev[MAX][MAX];
  int N = g->N;

  ft_memcpy(prev, g->board, sizeof(prev));

  if (dir == 0) {
    for (int j = 0; j < N; j++) {
      for (int i = 1; i < N; i++) {
        if (g->board[i][j] != 0) {
          int k = i;
          while (k > 0 && g->board[k - 1][j] == 0) {
            g->board[k - 1][j] = g->board[k][j];
            g->board[k][j] = 0;
            k--;
            moved = 1;
          }
          if (k > 0 && g->board[k - 1][j] == g->board[k][j] && !(ex && g->board[k][j] == WIN_VALUE)) {
            g->board[k - 1][j] *= 2;
            g->score += g->board[k - 1][j];
            g->board[k][j] = 0;
            moved = 1;
          }
        }
      }
    }
  } else if (dir == 1) {
    for (int j = 0; j < N; j++) {
      for (int i = N - 2; i >= 0; i--) {
        if (g->board[i][j] != 0) {
          int k = i;
          while (k < N - 1 && g->board[k + 1][j] == 0) {
            g->board[k + 1][j] = g->board[k][j];
            g->board[k][j] = 0;
            k++;
            moved = 1;
          }
          if (k < N - 1 && g->board[k + 1][j] == g->board[k][j] && !(ex && g->board[k][j] == WIN_VALUE)) {
            g->board[k + 1][j] *= 2;
            g->score += g->board[k + 1][j];
            g->board[k][j] = 0;
            moved = 1;
          }
        }
      }
    }
  } else if (dir == 2) {
    for (int i = 0; i < N; i++) {
      for (int j = 1; j < N; j++) {
        if (g->board[i][j] != 0) {
          int k = j;
          while (k > 0 && g->board[i][k - 1] == 0) {
            g->board[i][k - 1] = g->board[i][k];
            g->board[i][k] = 0;
            k--;
            moved = 1;
          }
          if (k > 0 && g->board[i][k - 1] == g->board[i][k] && !(ex && g->board[i][k] == WIN_VALUE)) {
            g->board[i][k - 1] *= 2;
            g->score += g->board[i][k - 1];
            g->board[i][k] = 0;
            moved = 1;
          }
        }
      }
    }
  } else if (dir == 3) {
    for (int i = 0; i < N; i++) {
      for (int j = N - 2; j >= 0; j--) {
        if (g->board[i][j] != 0) {
          int k = j;
          while (k < N - 1 && g->board[i][k + 1] == 0) {
            g->board[i][k + 1] = g->board[i][k];
            g->board[i][k] = 0;
            k++;
            moved = 1;
          }
          if (k < N - 1 && g->board[i][k + 1] == g->board[i][k] && !(ex && g->board[i][k] == WIN_VALUE)) {
            g->board[i][k + 1] *= 2;
            g->score += g->board[i][k + 1];
            g->board[i][k] = 0;
            moved = 1;
          }
        }
      }
    }
  }

  if (!moved) {
    ft_memcpy(g->board, prev, sizeof(prev));
    return 0;
  }

  int empties[25];
  int n = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (g->board[i][j] == 0)
        empties[n++] = i * N + j;

  int r = empties[rand() % n];
  int x = r / N;
  int y = r % N;
  g->board[x][y] = (rand() % 10 < 9) ? 2 : 4;

  return 1;
}

int main(void) {
  int ex_stage;

  while (1) {
    ex_stage = 0;
    Game g = {.board = {}, .N = 0, .score = 0, .best = load_best_score()};

    signal(SIGWINCH, handle_winch);
    signal(SIGINT, handle_sigint);

    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(100);
    curs_set(0);

    init_colors();

    g.N = draw_menu(g.best);
    if (g.N == -1) {
      endwin();
      if (g_int) {
        ft_putstr_fd("\nInterrupted (Ctrl+C). Cleaning up ...\n", 2);
        return 1;
      }
      return 0;
    }
    init_board(&g);
    draw_board(&g);

    int res = SCREEN_SIZE_OK;
    while (1) {
      if (g_int) {
        endwin();
        ft_putstr_fd("\nInterrupted (Ctrl+C). Cleaning up ...\n", 2);
        return 1;
      }
      if (g_resize_flag) {
        res = handle_resize();
        g_resize_flag = 0;
        if (res == SCREEN_SIZE_OK) {
          draw_board(&g);
        }
      }
      int ch = getch();
      if (res == SCREEN_SIZE_TOO_SMALL) {
        continue;
      }
      if (ch == 27)
        break;
      int moved = 0;
      if (ch == KEY_UP)
        moved = mov(0, &g, ex_stage);
      if (ch == KEY_DOWN)
        moved = mov(1, &g, ex_stage);
      if (ch == KEY_LEFT)
        moved = mov(2, &g, ex_stage);
      if (ch == KEY_RIGHT)
        moved = mov(3, &g, ex_stage);

      if (moved)
        draw_board(&g);

      if (!ex_stage && is_won(&g)) {
        mvprintw(3 + g.N * 2, 0, "You reached %d! Continue? (y/n)", WIN_VALUE);
        refresh();
        int c;
        while (1) {
          c = getch();
          if (c == 'y' || c == 'n')
            break;
        }
        if (c == 'n')
          break;
        else if (c == 'y') {
          ex_stage = 1;
          move(3 + g.N * 2, 0);
          clrtoeol();
          draw_board(&g);
        }
      }

      if (!can_move(&g, ex_stage)) {
        int row = 3 + g.N * 2;

        draw_board(&g);
        timeout(-1);
        if (!ex_stage) {
          mvprintw(row, 0, "GAME OVER! Press z key...");
        } else {
          mvprintw(row, 0, "EXTRA OVER! Final Score: %d   Press z key...", g.score);
          mvprintw(row + 1, 0, "Collected 2048 tiles: %d", count_2048(&g));
        }
        refresh();
        while (1){
          int c = getch();
          if (c == 'z')
            break;
        }
        break;
      }
      
    }
    if (g.best < g.score) {
      save_best_score(
          g.score); // MEMO: Ctrl + C で終了した場合スコアは保存されない。
    }
  }
  endwin();
  return 0;
}

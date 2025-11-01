#include "game.h"
#include "e_const.h"
#include <time.h>

void init_board(Game *g)
{
    for (int i = 0; i < g->N; i++)
        for (int j = 0; j < g->N; j++)
            g->board[i][j] = 0;

    for (int k = 0; k < 2; k++)
    {
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

void draw_board(Game *g)
{
    clear();
    mvprintw(0,0,"2048 (arrows to move, q exit)");
    mvprintw(1,0,"Score: %d", g->score);

    for (int i = 0; i < g->N; i++)
    {
        for (int j = 0; j < g->N; j++)
        {
            if (g->board[i][j] == 0)
                mvprintw(3 + i*2, j*6, "  .  ");
            else
                mvprintw(3 + i*2, j*6, "%4d ", g->board[i][j]);
        }
    }
    refresh();
}

int is_full(Game *g)
{
    for (int i = 0; i < g->N; i++)
        for (int j = 0; j < g->N; j++)
            if (g->board[i][j] == 0)
                return 0;
    return 1;
}

int is_won(Game *g)
{
    for (int i = 0; i < g->N; i++)
        for (int j = 0; j < g->N; j++)
            if (g->board[i][j] == WIN_VALUE)
                return 1;
    return 0;
}

int can_move(Game *g)
{
    for (int i = 0; i < g->N; i++)
    {
        for (int j = 0; j < g->N; j++)
        {
            if (g->board[i][j] == 0)
                return 1;
            if (j < g->N-1 && g->board[i][j] == g->board[i][j+1])
                return 1;
            if (i < g->N-1 && g->board[i][j] == g->board[i+1][j])
                return 1;
        }
    }
    return 0;
}

int mov(int dir, Game *g)
{
    int moved = 0;
    int prev[MAX][MAX];
    int N = g->N;

    ft_memcpy(prev, g->board, sizeof(prev));

    if (dir == 0)
    {
        for (int j = 0; j < N; j++)
        {
            for (int i = 1; i < N; i++)
            {
                if (g->board[i][j] != 0)
                {
                    int k = i;
                    while (k > 0 && g->board[k-1][j] == 0)
                    {
                        g->board[k-1][j] = g->board[k][j];
                        g->board[k][j] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && g->board[k-1][j] == g->board[k][j])
                    {
                        g->board[k-1][j] *= 2;
                        g->score += g->board[k-1][j];
                        g->board[k][j] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }
    else if (dir == 1)
    {
        for (int j = 0; j < N; j++)
        {
            for (int i = N-2; i >= 0; i--)
            {
                if (g->board[i][j] != 0)
                {
                    int k = i;
                    while (k < N-1 && g->board[k+1][j] == 0)
                    {
                        g->board[k+1][j] = g->board[k][j];
                        g->board[k][j] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < N-1 && g->board[k+1][j] == g->board[k][j])
                    {
                        g->board[k+1][j] *= 2;
                        g->score += g->board[k+1][j];
                        g->board[k][j] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }
    else if (dir == 2)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                if (g->board[i][j] != 0)
                {
                    int k = j;
                    while (k > 0 && g->board[i][k-1] == 0)
                    {
                        g->board[i][k-1] = g->board[i][k];
                        g->board[i][k] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && g->board[i][k-1] == g->board[i][k])
                    {
                        g->board[i][k-1] *= 2;
                        g->score += g->board[i][k-1];
                        g->board[i][k] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }
    else if (dir == 3)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = N-2; j >= 0; j--)
            {
                if (g->board[i][j] != 0)
                {
                    int k = j;
                    while (k < N-1 && g->board[i][k+1] == 0)
                    {
                        g->board[i][k+1] = g->board[i][k];
                        g->board[i][k] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < N-1 && g->board[i][k+1] == g->board[i][k])
                    {
                        g->board[i][k+1] *= 2;
                        g->score += g->board[i][k+1];
                        g->board[i][k] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }

    if (!moved)
    {
        ft_memcpy(g->board, prev, sizeof(prev));
        return 0;
    }

    int empties[25];
    int n = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (g->board[i][j] == 0)
                empties[n++] = i*N+j;

    int r = empties[rand() % n];
    int x = r / N;
    int y = r % N;
    g->board[x][y] = (rand()%10 < 9) ? 2 : 4;

    return 1;
}

int menu(void)
{
    clear();
    mvprintw(3,2,"=== 2048 MENU ===");
    mvprintw(5,4,"1) 4x4");
    mvprintw(6,4,"2) 5x5");
    mvprintw(8,4,"ESC to quit");
    refresh();

    while(1)
    {
        int ch = getch();
        if (ch == '1') return 4;
        if (ch == '2') return 5;
        if (ch == 27) return -1;
    }
}

int main(void)
{
    Game g;

    srand(time(NULL));

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    g.N = menu();
    if (g.N == -1)
    {
        endwin();
        return 0;
    }

    g.score = 0;
    init_board(&g);
    draw_board(&g);

    while(1)
    {
        int ch = getch();
        if (ch == 'q')
            break;

        int moved = 0;
        if (ch == KEY_UP) moved = mov(0, &g);
        if (ch == KEY_DOWN) moved = mov(1, &g);
        if (ch == KEY_LEFT) moved = mov(2, &g);
        if (ch == KEY_RIGHT) moved = mov(3, &g);

        if (moved)
            draw_board(&g);

        if (is_won(&g))
        {
            mvprintw(3 + g.N*2, 0, "You reached %d! Continue? (y/n)", WIN_VALUE);
            refresh();
            int c = getch();
            if (c == 'n')
                break;
        }

        if (!can_move(&g))
        {
            mvprintw(3 + g.N*2, 0, "GAME OVER! Press any key...");
            refresh();
            getch();
            break;
        }
    }

    endwin();
    return 0;
}


// int main() {
//     initscr();              // 画面初期化
//     cbreak();               // 行バッファ無効
//     noecho();               // 入力文字を表示しない
//     keypad(stdscr, TRUE);   // 矢印キー入力許可
//     curs_set(0);            // カーソル非表示

//     mvprintw(1, 1, "Hello ncurses!");
//     refresh();              // 描画更新

//     getch();                // 1文字待ち

//     endwin();               // 後片付け
//     return 0;
// }

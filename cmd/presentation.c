#include "game.h"
#include "e_const.h"

int handle_resize() {
    endwin();
    refresh();
    clear();

    // ウィンドウのサイズ
    int min_height = WINDOW_MIN_HEIGHT;
    int min_width = WINDOW_MIN_WIDTH;

    // 画面サイズが小さすぎる場合の対処
    if(LINES < min_height || COLS < min_width) {
        mvprintw(LINES / 2, (COLS - 20) / 2, "Window too small!");
        refresh();
        return SCREEN_SIZE_TOO_SMALL;
    }
    timeout(0);
    return SCREEN_SIZE_OK;
}

int draw_menu(int high_score __attribute__((__unused__)))
{
    clear();

    int init = 1;
    int res = SCREEN_SIZE_OK;
    while(1)
    {
        if(init || g_resize_flag) {
            res = handle_resize();
            init = 0;
            g_resize_flag = 0;
            if (res == SCREEN_SIZE_OK) {
                mvprintw(3,2,"=== 2048 MENU ===");
                mvprintw(5,4,"1) 4x4");
                mvprintw(6,4,"2) 5x5");
                mvprintw(8,4,"ESC to quit");
                refresh();
            }
        }
        if (g_int)
            return -1;
        int ch = getch();
        if (res == SCREEN_SIZE_TOO_SMALL) {
            continue;
        }
        if (ch == '1') return 4;
        if (ch == '2') return 5;
        if (ch == 27) return -1;
    }
}
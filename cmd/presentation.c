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

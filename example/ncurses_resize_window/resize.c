#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// グローバルフラグ: 画面サイズが変更されたかを追跡
volatile sig_atomic_t resize_flag = 0;
WINDOW *menu_win = NULL;
WINDOW *info_win = NULL;

// 選択肢
char *choices[] = {
    "Start Game",
    "Options",
    "Help",
    "Exit",
    NULL
};
int n_choices = 4;
int highlight = 0;  // 現在選択されている項目 (0-indexed)

// SIGWINCHシグナルハンドラ
void handle_winch(int sig __attribute__((__unused__))) {
    resize_flag = 1;
}

// メニューウィンドウを作成/再作成する関数
WINDOW* create_menu_window(int height, int width) {
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    keypad(win, TRUE);

    return win;
}

// 情報ウィンドウを作成する関数
WINDOW* create_info_window() {
    int height = 5;
    int width = 50;
    int start_y = 1;
    int start_x = (COLS - width) / 2;

    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);

    return win;
}

// メニューを描画する関数
void print_menu(WINDOW *menu_win, int highlight) {
    int x = 2, y = 2;

    wclear(menu_win);
    box(menu_win, 0, 0);

    // タイトル
    mvwprintw(menu_win, 0, 2, " Main Menu ");

    // 選択肢を描画
    for(int i = 0; i < n_choices; i++) {
        if(highlight == i) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y + i, x, "  %s  ", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y + i, x, "  %s  ", choices[i]);
        }
    }

    // 操作説明
    mvwprintw(menu_win, y + n_choices + 1, x, "Use up/down to select");
    mvwprintw(menu_win, y + n_choices + 2, x, "Press ENTER to choose");

    wrefresh(menu_win);
}

// 情報ウィンドウを描画する関数
void print_info(WINDOW *info_win) {
    wclear(info_win);
    box(info_win, 0, 0);

    mvwprintw(info_win, 0, 2, " Screen Info ");
    mvwprintw(info_win, 1, 2, "Terminal size: %d x %d", COLS, LINES);
    mvwprintw(info_win, 2, 2, "Try resizing your terminal window!");
    mvwprintw(info_win, 3, 2, "The interface will adapt automatically.");

    wrefresh(info_win);
}

// リサイズ処理を行う関数
void handle_resize() {
    // 既存のウィンドウを削除
    if(menu_win != NULL) {
        delwin(menu_win);
        menu_win = NULL;
    }
    if(info_win != NULL) {
        delwin(info_win);
        info_win = NULL;
    }

    // ncursesを再初期化
    endwin();
    refresh();
    clear();

    // ウィンドウのサイズ
    int menu_height = n_choices + 6;
    int menu_width = 30;

    // 画面サイズが小さすぎる場合の対処
    if(LINES < menu_height + 8 || COLS < menu_width + 4) {
        mvprintw(LINES / 2, (COLS - 20) / 2, "Window too small!");
        mvprintw(LINES / 2 + 1, (COLS - 30) / 2, "Please resize your terminal");
        refresh();
        return;
    }

    // ウィンドウを再作成
    info_win = create_info_window();
    menu_win = create_menu_window(menu_height, menu_width);

    // 再描画
    print_info(info_win);
    print_menu(menu_win, highlight);
}

int main() {
    // シグナルハンドラの設定
    signal(SIGWINCH, handle_winch);

    // ncurses初期化
    initscr();
    cbreak();
    noecho();
    curs_set(0);  // カーソルを非表示
    keypad(stdscr, TRUE);

    // 初期ウィンドウ作成
    int menu_height = n_choices + 6;
    int menu_width = 30;

    // 初期画面サイズチェック
    if(LINES < menu_height + 8 || COLS < menu_width + 4) {
        endwin();
        printf("Terminal window is too small!\n");
        printf("Please resize and try again.\n");
        return 1;
    }

    info_win = create_info_window();
    menu_win = create_menu_window(menu_height, menu_width);

    // 初期描画
    print_info(info_win);
    print_menu(menu_win, highlight);

    int ch;
    int selected = -1;

    // メインループ
    while(selected == -1) {
        // リサイズフラグをチェック
        if(resize_flag) {
            handle_resize();
            resize_flag = 0;
        }

        // キー入力を待つ
        ch = wgetch(menu_win);

        switch(ch) {
            case KEY_UP:
                if(highlight > 0) {
                    highlight--;
                } else {
                    highlight = n_choices - 1;  // 一番下へ
                }
                print_menu(menu_win, highlight);
                break;

            case KEY_DOWN:
                if(highlight < n_choices - 1) {
                    highlight++;
                } else {
                    highlight = 0;  // 一番上へ
                }
                print_menu(menu_win, highlight);
                break;

            case 10:  // Enter キー
            case KEY_ENTER:
                selected = highlight;
                break;

            case 'q':
            case 'Q':
                selected = 3;  // Exit を選択したことにする
                break;
        }
    }

    // ウィンドウを削除
    if(menu_win != NULL) delwin(menu_win);
    if(info_win != NULL) delwin(info_win);

    // ncurses終了
    endwin();

    // 選択結果を表示
    printf("\nYou selected: %s\n", choices[selected]);

    return 0;
}

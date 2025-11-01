#include <ncurses.h>

char *choices[] = {
    "OPTION 1",
    "OPTION 2",
    "OPTION 3",
    "EXIT",
    (char *)NULL
};
int n_choices = sizeof(choices) / sizeof(char *) - 1;
int highlight = 1; // 現在選択されている項目

// メニューを描画する関数
void print_menu(WINDOW *menu_win, int highlight) {
    int i;
    int x = 2, y = 2; // 表示開始位置
    
    box(menu_win, 0, 0); // ウィンドウに枠を描画
    for(i = 0; i < n_choices; ++i) {
        if(highlight == i + 1) { // 選択中の項目
            wattron(menu_win, A_REVERSE); // ハイライト（反転表示）をON
            mvwprintw(menu_win, y + i, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE); // ハイライトをOFF
        } else {
            mvwprintw(menu_win, y + i, x, "%s", choices[i]);
        }
    }
    wrefresh(menu_win); // ウィンドウを更新
}

int main() {
    initscr();    // ncurses開始
    cbreak();     // Ctrl+C以外はバッファリングしない
    noecho();     // 入力を画面に表示しない
    keypad(stdscr, TRUE); // 特殊キーを有効にする


    // メニューウィンドウの作成（例: 高さ10、幅30、座標(4, 4)）
    WINDOW *menu_win = newwin(10, 30, 4, 4);
    keypad(menu_win, TRUE); // メニューウィンドウでも特殊キーを有効にする

    int c; // 入力されたキー
    
    while(1) {
        print_menu(menu_win, highlight); // メニューを描画
        c = wgetch(menu_win); // キー入力を待つ
        
        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices; // 一番下へ
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1; // 一番上へ
                else
                    ++highlight;
                break;
            case 10: // エンターキー (ASCII値 10)
                goto end_loop; // ループを抜けて選択を処理
        }
    }
end_loop:

    mvprintw(LINES - 2, 0, "selected %s", choices[highlight - 1]);
    refresh();
    getch(); // 結果を確認するために待機

    endwin(); // ncurses終了
    return 0;
}
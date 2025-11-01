#include "game.h"
#include "e_const.h"

void init_colors(void)
{
    if (!has_colors())
        return;
    start_color();
    use_default_colors();
    init_pair(1, COLOR_WHITE,   -1);
    init_pair(2, COLOR_CYAN,    -1);
    init_pair(3, COLOR_BLUE,    -1);
    init_pair(4, COLOR_GREEN,   -1);
    init_pair(5, COLOR_YELLOW,  -1);
    init_pair(6, COLOR_MAGENTA, -1);
    init_pair(7, COLOR_RED,     -1);
	init_pair(8, COLOR_RED,     COLOR_YELLOW);
	init_pair(9, COLOR_WHITE,   COLOR_RED);
}

int color_for_value(int v)
{
    if (v == 2)   return 1;
    if (v == 4)   return 2;
    if (v == 8)   return 3;
    if (v == 16)  return 4;
    if (v == 32)  return 5;
    if (v == 64)  return 6;
    if (v == 128) return 7;
	if (v == 256) return 3;
	if (v == 512) return 5;
    if (v == 1024) return 8;
    if (v == 2048) return 9;
    return 0;
}

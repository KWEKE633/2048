#include "game.h"
#include <stdlib.h>
#include <stdio.h>

int load_best_score(void)
{
    FILE *f = fopen("bestscore.txt", "r");
    int b = 0;
    if (f)
    {
        if (fscanf(f, "%d", &b) != 1)
			b = 0;
        fclose(f);
    }
    return b;
}

void save_best_score(int best)
{
    FILE *f = fopen("bestscore.txt", "w");
    if (f)
    {
        fprintf(f, "%d\n", best);
        fclose(f);
    }
}

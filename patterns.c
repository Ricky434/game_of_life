#include "conway.h"
#include <time.h>
#include <stdlib.h>

void init_glider(char* grid, int x, int y) {
    set_cell(grid, x+1, y+0, ALIVE);
    set_cell(grid, x+2, y+1, ALIVE);
    set_cell(grid, x+0, y+2, ALIVE);
    set_cell(grid, x+1, y+2, ALIVE);
    set_cell(grid, x+2, y+2, ALIVE);
}

void init_random(char* grid) {
    srand(time(NULL));

    for (int y=0; y<GRID_HEIGHT; y++) {
        for (int x=0; x<GRID_WIDTH; x++) {
            char state = DEAD;
            if (rand()%2 == 0) {
                state = ALIVE;
            }

            set_cell(grid, x, y, state);
        }
    }
}

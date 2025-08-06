#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "conway.h"
#include "patterns.c"

char* initialize_grid() {
    char* grid = malloc(sizeof(char)*GRID_WIDTH*GRID_HEIGHT);
    for (size_t i=0; i<GRID_WIDTH*GRID_HEIGHT; i++) {
        grid[i] = DEAD;
    }

    return grid;
}

int wrap_abs(int val, int limit) {
    return val%limit + (limit*(val<0));
}

void set_cell(char grid[], int x, int y, char state) {
    int norm_x = wrap_abs(x, GRID_WIDTH);
    int norm_y = wrap_abs(y, GRID_HEIGHT);
    grid[norm_y*GRID_WIDTH+norm_x] = state;
}

char get_cell(char grid[], int x, int y) {
    int norm_x = wrap_abs(x, GRID_WIDTH);
    int norm_y = wrap_abs(y, GRID_HEIGHT);
    return grid[norm_y*GRID_WIDTH+norm_x];
}

int get_surrounding(char grid[], int x, int y) {
    int tot = 0;
    for (int i = -1; i<=1; i++) {
        for (int j = -1; j<=1; j++) {
            if (i==0 && j==0) continue;
            
            tot += (get_cell(grid, x+i, y+j) == ALIVE);
        }
    }
    return tot;
}

void next_step(char current_grid[], char new_grid[]) {
    for (size_t i=0; i<GRID_HEIGHT; i++) {
        for (size_t j=0; j<GRID_WIDTH; j++){
            char state = get_cell(current_grid, j, i);
            int surrounding = get_surrounding(current_grid, j, i);

            char new_state = DEAD;
            if (state == ALIVE)  {
                if (surrounding == 2 || surrounding == 3)
                    new_state = ALIVE;
            } else {
                if (surrounding == 3)
                    new_state = ALIVE;
            } 

            set_cell(new_grid, j, i, new_state);
        }
    }
}

void print_grid(char grid[]) {
    // Clear screen and put cursor on top left cell
    printf("\033[2J");
    printf("\033[H");

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            putchar(get_cell(grid, x, y));
        }
        putchar('\n');
    }
}

int main()
{
    char* printable_grid = initialize_grid();
    char* background_grid = initialize_grid();

    //init_glider(printable_grid, 0, 0);
    //init_glider(printable_grid, 10, 0);
    init_random(printable_grid);

    while (1) {
        print_grid(printable_grid);

        // swap grids
        char* temp = background_grid;
        background_grid = printable_grid;
        printable_grid = temp;

        next_step(background_grid, printable_grid);

        usleep(100000);
    }
    return 0;
}

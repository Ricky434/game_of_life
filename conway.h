#ifndef CONWAY_H
#define CONWAY_H

#define GRID_WIDTH 80
#define GRID_HEIGHT 40
#define ALIVE '*'
#define DEAD ' '

char* initialize_grid();

int wrap_abs(int val, int limit);

void set_cell(char grid[], int x, int y, char state);

char get_cell(char grid[], int x, int y);

int get_surrounding(char grid[], int x, int y);

void next_step(char current_grid[], char new_grid[]);

void print_grid(char grid[]);

#endif

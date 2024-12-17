#pragma once
#include <stdbool.h>
#include <stdint.h>

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 22

typedef struct TetrisGrid {
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
} TetrisGrid;


static void init_tetris_edges(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH]);
extern TetrisGrid initialize_tetris_board();
extern void print_grid(int p_tetris_grid[BOARD_HEIGHT][BOARD_WIDTH]); 

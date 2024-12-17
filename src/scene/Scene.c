#include "Scene.h"
#include <stdio.h>

TetrisGrid initialize_tetris_board() {
    TetrisGrid tetris_grid;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            tetris_grid.grid[i][j] = 0;
        }
    }
    init_tetris_edges(tetris_grid.grid);

    //Hardcoded grid
    // tetris_grid.grid[20][1] = 2;
    // tetris_grid.grid[20][2] = 2;
    // tetris_grid.grid[19][1] = 2;
    // tetris_grid.grid[19][2] = 2;

    return tetris_grid;
}

void init_tetris_edges(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH]) {

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        tetris_grid[i][0] = 8;
        tetris_grid[i][BOARD_WIDTH - 1] = 8;
    
    }

    for (int j = 0; j < BOARD_WIDTH; j++) {
        tetris_grid[0][j] = 8;
        tetris_grid[BOARD_HEIGHT - 1][j] = 8;
    
    }
}

void print_grid(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH]) {

    printf("*****************************");
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        printf("\n");
        for (int j = 0; j < BOARD_WIDTH; j++) {
            printf("%i, ", tetris_grid[i][j]);
        }
    }
    printf("\n*****************************\n");

}

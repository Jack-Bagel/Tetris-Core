#include "Pieces.h"
#include <TetrisUtils.h>
#include <stdio.h>
#include <time.h>

void clear_tetris_grid(TetrisGrid *p_tetris_grid) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (p_tetris_grid->grid[i][j] != 0 && p_tetris_grid->grid[i][j] != 128) {
                p_tetris_grid->grid[i][j] = 0;
            }
        }
    }
}

void combine_tetris_grids(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            p_first_grid->grid[i][j] |= p_second_grid->grid[i][j];
        }
    }
}

void AND_tetris_grid(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            p_first_grid->grid[i][j] &= p_second_grid->grid[i][j];
        }
    }
}

void ADD_tetris_grid(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            p_first_grid->grid[i][j] += p_second_grid->grid[i][j];
        }
    }
}

bool are_grids_equals(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (p_first_grid->grid[i][j] != p_second_grid->grid[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int random_to_piece(int piece_number) {
    if (piece_number == 1) {
        return LINE_BLOCK;
    }

    else if (piece_number == 2) {
        return SQUARE_BLOCK;
    }

    else if (piece_number == 3) {
        return T_BLOCK;
    }

    else if (piece_number == 4) {
        return L_BLOCK;
    }

    else if (piece_number == 5) {
        return R_L_BLOCK;
    }

    else if (piece_number == 6) {
        return Z_BLOCK;
    }

    else if (piece_number == 7) {
        return R_Z_BLOCK;
    }

    else if (piece_number == 8) {
        return EDGE;
    }
    return -1;
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

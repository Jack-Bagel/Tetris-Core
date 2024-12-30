#pragma once
#include <stdbool.h>
#include "TetrisLogic.h"

static u_int s_game_seed;

extern void reset_game_seed();
extern u_int get_game_seed();
extern bool are_grids_equals(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid);
extern void clear_tetris_grid(TetrisGrid *tetris_grid);
extern void combine_tetris_grids(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid);
extern void AND_tetris_grid(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid);
extern void ADD_tetris_grid(TetrisGrid *p_first_grid, TetrisGrid *p_second_grid);
extern int random_to_piece(int piece_number);
extern void print_grid(int p_tetris_grid[BOARD_HEIGHT][BOARD_WIDTH]); 

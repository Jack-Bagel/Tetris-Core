#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include "Pieces.h"

#define BOARD_WIDTH 14
#define BOARD_HEIGHT 23

typedef struct TetrisGrid {
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
} TetrisGrid;

static TetrisGrid m_tetris_grid;
static TetrisGrid m_last_tetris_grid;
static TetrisGrid m_falling_piece_grid;
static Piece m_piece;
static int m_offset;
static u_long m_points;

extern TetrisGrid* get_tetris_grid();
extern TetrisGrid* get_last_tetris_grid();
extern TetrisGrid* get_falling_piece_grid();
extern Piece* get_falling_piece();
extern int get_points();

extern void tetris_loop();
extern void init_new_piece();
extern bool initialize_tetris_scene();
extern void make_piece_fall(int height_offset);
extern bool piece_collides(TetrisGrid *p_last_tetris_grid, TetrisGrid *p_falling_piece_grid);
extern void update_event(bool *is_running);

static int** read_four_lines(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int offset);
static void init_tetris_edges(TetrisGrid *p_grid);
static void generate_new_piece();
static void clear_lines();
static void clear_line(int line);
static void game_over();
static bool can_move_left();
static bool can_move_right();
static bool can_rotate();

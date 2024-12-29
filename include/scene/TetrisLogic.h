#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include "Pieces.h"

#define BOARD_WIDTH 14
#define BOARD_HEIGHT 23

// TODO: Move TetrisGrid somewhere else
typedef struct TetrisGrid {
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
} TetrisGrid;

typedef struct TetrisBoard {
    TetrisGrid m_tetris_grid;
    TetrisGrid m_last_tetris_grid;
    TetrisGrid m_falling_piece_grid;
    Piece m_piece;
    int m_offset;
    u_long m_points;
    u_int m_lines_cleared;
    u_int m_current_level;
    Piece m_next_piece;

} TetrisBoard;

extern TetrisGrid* get_tetris_grid(TetrisBoard *p_tetris_board);
extern TetrisGrid* get_last_tetris_grid(TetrisBoard *p_tetris_board);
extern TetrisGrid* get_falling_piece_grid(TetrisBoard *p_tetris_board);
extern Piece* get_falling_piece(TetrisBoard *p_tetris_board);
extern int get_points(TetrisBoard *p_tetris_board);
extern int get_level(TetrisBoard *p_tetris_board);
extern Piece get_next_piece(TetrisBoard *p_tetris_board);

extern bool init_tetris_board(TetrisBoard *p_tetris_board);
extern void tetris_loop(TetrisBoard *p_tetris_board);
extern void generate_new_piece(TetrisBoard *p_tetris_board, u_int u_int); // Make it static

// Controls 
extern void rotate_piece_clockwise(TetrisBoard *p_tetris_board);
extern void move_left(TetrisBoard *p_tetris_board);
extern void move_right(TetrisBoard *p_tetris_board);

// Tetris board loop
static void make_piece_fall(TetrisBoard *p_tetris_board, int height_offset);
static bool piece_collides(TetrisGrid *p_last_tetris_grid, TetrisGrid *p_falling_piece_grid);
static void init_tetris_edges(TetrisBoard *p_tetris_board);
static void clear_lines(TetrisBoard *p_tetris_board);
static void clear_line(TetrisBoard *p_tetris_board, int line);
static void game_over(TetrisBoard *p_tetris_board);
static bool can_move_left(TetrisBoard *p_tetris_board);
static bool can_move_right(TetrisBoard *p_tetris_board);
static bool can_rotate(TetrisBoard *p_tetris_board);

static void update_level(TetrisBoard *p_tetris_board);
static void update_speed(TetrisBoard *p_tetris_board);

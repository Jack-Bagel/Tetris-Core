#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "Pieces.h"
#include "TetrisTime.h"

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
    bool m_game_start;
    bool m_is_game_over;
    Piece m_piece;
    Piece m_next_piece;
    unsigned int m_seed;
    unsigned int m_increment_seed;
    int m_offset;
    unsigned long m_points;
    unsigned int m_lines_cleared;
    unsigned int m_current_level;
    TetrisCounter m_counter;

} TetrisBoard;


extern TetrisGrid* get_tetris_grid(TetrisBoard *self);
extern TetrisGrid* get_last_tetris_grid(TetrisBoard *self);
extern TetrisGrid* get_falling_piece_grid(TetrisBoard *self);
extern Piece* get_falling_piece(TetrisBoard *self);
extern int get_points(TetrisBoard *self);
extern int get_level(TetrisBoard *self);
extern Piece get_next_piece(TetrisBoard *self);

extern void tetris_loop(TetrisBoard *self);

// Controls 
extern void rotate_piece_clockwise(TetrisBoard *self);
extern void rotate_piece_counter_clockwise(TetrisBoard *self);
extern void move_left(TetrisBoard *self);
extern void move_right(TetrisBoard *self);

// Tetris board loop
static bool init_tetris_board(TetrisBoard *self);
static void generate_new_piece(TetrisBoard *self);
static void make_piece_fall(TetrisBoard *self, int height_offset);
static bool piece_collides(TetrisGrid *p_last_tetris_grid, TetrisGrid *p_falling_piece_grid);
static void init_tetris_edges(TetrisBoard *self);
static void clear_lines(TetrisBoard *self);
static void clear_line(TetrisBoard *self, int line);
static void game_over(TetrisBoard *self);
static bool can_move_left(TetrisBoard *self);
static bool can_move_right(TetrisBoard *self);
static bool can_rotate_clockwise(TetrisBoard *self);
static bool can_rotate_counter_clockwise(TetrisBoard *self);

static void update_level(TetrisBoard *self);
static void update_speed(TetrisBoard *self);

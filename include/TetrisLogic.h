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
    unsigned int m_total_lines_cleared;
    unsigned int m_current_level;
    TetrisCounter m_counter;

} TetrisBoard;

extern void tetris_loop(TetrisBoard *self);


extern void reset_game_seed();
extern unsigned int get_game_seed();
extern Piece get_next_piece(TetrisBoard *self);
extern int get_points(TetrisBoard *self);
extern int get_level(TetrisBoard *self);
extern int get_total_lines(TetrisBoard *self);
extern bool get_game_over(TetrisBoard *self);

// Controls 
extern void rotate_piece_clockwise(TetrisBoard *self);
extern void rotate_piece_counter_clockwise(TetrisBoard *self);
extern void move_left(TetrisBoard *self);
extern void move_right(TetrisBoard *self);


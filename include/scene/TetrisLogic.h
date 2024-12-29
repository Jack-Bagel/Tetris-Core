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

} TetrisBoard;

static TetrisGrid m_tetris_grid;
static TetrisGrid m_last_tetris_grid;
static TetrisGrid m_falling_piece_grid;
static Piece m_piece;
static int m_offset;
static u_long m_points;
static u_int m_lines_cleared;
static u_int m_current_level;
static Piece m_next_piece;

extern TetrisGrid* get_tetris_grid();
extern TetrisGrid* get_last_tetris_grid();
extern TetrisGrid* get_falling_piece_grid();
extern Piece* get_falling_piece();
extern int get_points();
extern int get_level();
extern Piece get_next_piece();

extern bool initialize_tetris_scene();
extern void tetris_loop();
extern void update_event(bool *is_running);
extern void generate_new_piece(u_int u_int);
extern void rotate_piece_clockwise();
extern void move_left();
extern void move_right();

static void make_piece_fall(int height_offset);
static bool piece_collides(TetrisGrid *p_last_tetris_grid, TetrisGrid *p_falling_piece_grid);
static void init_tetris_edges(TetrisGrid *p_grid);
static void clear_lines();
static void clear_line(int line);
static void game_over();
static bool can_move_left();
static bool can_move_right();
static bool can_rotate();

static void update_level();
static void update_speed();

#pragma once
#include <SDL_render.h>
#include <SDL_video.h>
#include "Scene.h"
#include "Pieces.h"

static TetrisGrid s_player_tetris_grid;
static TetrisGrid s_tetris_grid;
static TetrisGrid s_piece_grid;
static int s_last_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH];
static int tetris_counter;
static int random_seed;
static bool game_start;

static int** read_four_lines(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int offset);
static void init_new_piece(Piece piece);
static void make_piece_fall(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]);
static bool piece_collides(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]);
static bool piece_touches_ground(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]);
static void move_piece(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]);

extern int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window);
extern void place_blocks_on_screen(SDL_Window *p_window, SDL_Renderer *p_renderer);
extern bool init_tetris_scene();


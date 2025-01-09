#pragma once
#include "TetrisLogic.h"
#include <SDL2/SDL.h>

extern void render_tetris_grid(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y);
extern void render_score(TetrisBoard *p_tetris_board, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y);
extern void render_level(TetrisBoard *p_tetris_board, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y);
extern void render_lines(TetrisBoard *p_tetris_board, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y);
extern void render_next_piece(Piece next_piece, int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y);
extern void render_background(SDL_Texture *background_texture, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);

extern void clear_screen(SDL_Renderer *p_renderer);
extern void draw_screen(SDL_Renderer *p_renderer, const SDL_Rect viewport);

static void render_block(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int *position, int* color, int size);
static int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window, int offset_x, int offset_y);
static int* index_to_position_next_piece(int index_i, int index_j, int size, SDL_Window *p_window, int offset_x, int offset_y);

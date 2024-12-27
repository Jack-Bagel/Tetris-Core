#pragma once
#include "TetrisLogic.h"
#include <SDL.h>

static SDL_Texture *p_texture;
extern void render_tetris_grid(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer);
extern void register_textures(SDL_Renderer *p_renderer);
extern void render_block(SDL_Window *p_window, SDL_Renderer *p_renderer, int *position, int* color, int size);
extern int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window);

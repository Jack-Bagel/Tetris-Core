#pragma once
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>


extern int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window);
extern void place_blocks_on_screen(SDL_Window *p_window, SDL_Renderer *p_renderer, bool *is_running);


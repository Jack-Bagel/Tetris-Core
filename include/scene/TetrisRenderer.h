#pragma once
#include <SDL.h>

static SDL_Texture *p_texture;
extern void register_textures(SDL_Renderer *p_renderer);
extern void render_block(SDL_Window *p_window, SDL_Renderer *p_renderer, int *position, int* color, int size);

#pragma once
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <sys/types.h>

static u_int m_current_scene;

extern void update_game(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
extern void init_scene();

extern void set_current_scene(u_int scene);
extern u_int get_current_scene();

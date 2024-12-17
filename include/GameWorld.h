#pragma once
#include <stdbool.h>
#include <SDL.h>

// Setup main application
static bool is_running;
static SDL_Window *p_window;
static SDL_Renderer *p_renderer;

extern bool initialize_game_world();
extern bool run_game_world();
extern bool exit_game_world();

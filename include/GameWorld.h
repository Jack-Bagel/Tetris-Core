#pragma once
#include "TetrisLogic.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 884

// Setup main application
static SDL_Window *p_window;
static SDL_Renderer *p_renderer;
static const SDL_Rect m_viewport = {.x = 0, .y = 0, .w = SCREEN_WIDTH, .h = SCREEN_HEIGHT};

static TetrisBoard s_players_board[2];

extern bool initialize_game_world();
extern bool run_game_world();
extern bool exit_game_world();

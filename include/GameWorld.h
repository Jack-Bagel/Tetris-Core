#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 884

extern bool initialize_game_world();
extern bool run_game_world();
extern bool exit_game_world();

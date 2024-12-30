#pragma once
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <stdbool.h>

static bool is_running;
static void one_player_handler(TetrisBoard p_tetris_board[2], SDL_Event *event);
static void two_player_handler(TetrisBoard p_tetris_board[2], SDL_Event *event);
static void main_menu_handler(TetrisBoard p_tetris_board[2], SDL_Event *event);
static void pause_menu_handler(TetrisBoard p_tetris_board[2], SDL_Event *event);
extern void update_event(TetrisBoard p_tetris_board[2], bool *p_is_running);

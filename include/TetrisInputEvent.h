#pragma once
#include "TetrisLogic.h"
#include <SDL_events.h>
#include <stdbool.h>

static void two_player_handler(TetrisBoard p_tetris_board[2], SDL_Event *event);
extern void update_event(TetrisBoard p_tetris_board[2]);

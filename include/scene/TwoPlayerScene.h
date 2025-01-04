#pragma once
#include "PlayableScene.h"
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

extern void init_two_player(PlayableScene *scene);

static void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard *p_one_player_board);
static void render_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard *p_player_one_board);
static void movements(TetrisBoard p_tetris_board[2]);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

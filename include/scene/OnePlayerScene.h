#pragma once
#include "PlayableScene.h"
#include "TetrisLogic.h"
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>

extern void init_one_player(PlayableScene *p_scene);

static void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard p_player_one_board[2]);
static void render_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard p_player_one_board[2]);
static void movements(TetrisBoard p_tetris_board[2]);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

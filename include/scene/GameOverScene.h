#pragma once
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "MenuScene.h"
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

typedef struct GameOverScene {
    void (*update)(SDL_Window*, SDL_Renderer*, const SDL_Rect, TetrisBoard[2]);
    
} GameOverScene;


extern void init_game_over(GameOverScene *scene);

static void update_game_over(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]);
static void render_game_over(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

static void render_buttons(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void increase_button_selection();
static void decrease_button_selection();

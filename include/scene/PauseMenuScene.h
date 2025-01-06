#pragma once
#include "MenuScene.h"
#include "TetrisLogic.h"
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_video.h>

extern void init_pause_menu(MenuScene *scene);

static void update_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void render_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

static void render_buttons(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void render_pause_background(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void increase_button_selection();
static void decrease_button_selection();

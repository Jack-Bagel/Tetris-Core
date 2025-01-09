#pragma once
#include "MenuScene.h"
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

extern void init_main_menu(MenuScene *scene);
extern void init_event_handler();

static void update_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void render_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

static void render_buttons(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void increase_button_selection();
static void decrease_button_selection();

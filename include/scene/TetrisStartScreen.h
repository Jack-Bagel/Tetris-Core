#pragma once
#include "Button.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

static Button one_player;
static Button two_players;
static Button quit_game;
static int button_selection;
static TTF_Font *font;
static SDL_Color text_color;
extern void render_background(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
extern void render_buttons(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
extern void init_start_screen();
extern void increase_button_selection();
extern void decrease_button_selection();
extern u_int get_button_selection();
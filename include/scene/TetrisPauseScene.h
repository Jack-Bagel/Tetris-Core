#pragma once
#include "Button.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

static Button m_continue;
static Button m_restart;
static Button m_return_to_start;
static int button_selection;
static SDL_Color text_color;

extern void render_pause_background(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
extern void render_pause_buttons(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
extern void init_pause_screen();
extern void increase_pause_button_selection();
extern void decrease_pause_button_selection();
extern u_int get_pause_button_selection();

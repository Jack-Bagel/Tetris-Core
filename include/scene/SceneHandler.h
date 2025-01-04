#pragma once
#include "TetrisLogic.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <sys/types.h>

typedef enum SceneID {
    MAIN_MENU,
    PAUSE_MENU,
    ONE_PLAYER,
    TWO_PLAYER
} SceneID;

static u_int s_current_scene;
static u_int s_last_scene;

extern void update_game(TetrisBoard players_board[2], SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
extern void init_scene();

extern void set_current_scene(u_int scene);
extern u_int get_current_scene();
extern u_int get_last_scene();

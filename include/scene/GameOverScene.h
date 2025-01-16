#pragma once
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

typedef struct GameOverScene {
    void (*update)(SDL_Window*, SDL_Renderer*, const SDL_Rect, TetrisBoard[2]);
    
} GameOverScene;

extern void init_game_over(GameOverScene *scene);

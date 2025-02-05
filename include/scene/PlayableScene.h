#pragma once
#include "TetrisLogic.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef struct PlayableScene {
    void (*update)(SDL_Window*, SDL_Renderer*, const SDL_Rect, TetrisBoard[2]);
    
} PlayableScene;

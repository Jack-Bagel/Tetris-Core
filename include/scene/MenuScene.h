#pragma once
#include <SDL_events.h>
#include <SDL_render.h>

typedef struct MenuScene {
    void (*update)(SDL_Window*, SDL_Renderer*, const SDL_Rect);
    
} MenuScene;

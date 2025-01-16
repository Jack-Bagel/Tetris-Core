#pragma once
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef struct MenuScene {
    void (*update)(SDL_Window*, SDL_Renderer*, const SDL_Rect);

} MenuScene;

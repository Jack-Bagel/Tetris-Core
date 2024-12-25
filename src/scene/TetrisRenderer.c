#include "TetrisRenderer.h"
#include <SDL_image.h>
#include <SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void register_textures(SDL_Renderer *p_renderer) {

    p_texture = IMG_LoadTexture(p_renderer, "../resources/Tetris_Block.jpg");

    if (p_texture == NULL) {
        printf("Failed to load texture \n");
    }
}

void render_block(SDL_Window *p_window, SDL_Renderer *p_renderer, int *position, int *color, int size) {
    int w, h;
    SDL_GetWindowSize(p_window, &w, &h);
    const SDL_Rect block = {.x = position[1], .y = position[0], .w = size, .h = size};
    SDL_RenderCopy(p_renderer, p_texture, NULL, &block);
    SDL_SetTextureColorMod(p_texture, color[0], color[1], color[2]);
    free(position); // I may need to free both pointers, idk if it is done automatically
}

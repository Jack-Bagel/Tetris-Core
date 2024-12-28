#include "TextureRegistry.h"
#include <SDL_image.h>

SDL_Texture *g_p_block;
SDL_Texture *g_p_background;
SDL_Texture *g_p_gameplay_background;

void register_textures(SDL_Renderer *p_renderer) {
    g_p_block = IMG_LoadTexture(p_renderer, "../resources/Tetris_Block.jpg");
    g_p_background = IMG_LoadTexture(p_renderer, "../resources/Start_Screen.jpg");
    g_p_gameplay_background = IMG_LoadTexture(p_renderer, "../resources/background_image.jpg");

    if (g_p_block == NULL) {
        printf("Failed to load block texture \n");
    }

    if (g_p_background == NULL) {
        printf("Failed to load background texture \n");
    }
}

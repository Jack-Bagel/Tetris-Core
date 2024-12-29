#include "TextureRegistry.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture *g_p_block;
SDL_Texture *g_p_background;
SDL_Texture *g_p_gameplay_background;
TTF_Font *g_p_font;

void register_textures(SDL_Renderer *p_renderer) {
    g_p_block = IMG_LoadTexture(p_renderer, "resources/Tetris_Block.jpg");
    g_p_background = IMG_LoadTexture(p_renderer, "resources/Start_Screen.jpg");
    g_p_gameplay_background = IMG_LoadTexture(p_renderer, "resources/background_image.jpg");
    g_p_font = TTF_OpenFont("resources/fonts/Monocraft.ttc", 24);

    if (g_p_font == NULL) {
        printf("Error: Could not load font\n");
    }

    if (g_p_block == NULL) {
        printf("Failed to load block texture \n");
    }

    if (g_p_background == NULL) {
        printf("Failed to load background texture \n");
    }

    if (g_p_gameplay_background == NULL) {
        printf("Failed to load gameplay background texture \n");
    }
}

#include "TextureRegistry.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

SDL_Texture *g_block_tex;
SDL_Texture *g_start_menu_bkg;
SDL_Texture *g_pause_menu_bkg;
SDL_Texture *g_game_over_bkg;
SDL_Texture *g_two_player_game_over_bkg;
SDL_Texture *g_one_player_bkg;
SDL_Texture *g_two_player_bkg;
TTF_Font *g_font;

void register_textures(SDL_Renderer *p_renderer) {
    g_block_tex = IMG_LoadTexture(p_renderer, "../resources/Tetris_Block.jpg");
    g_start_menu_bkg = IMG_LoadTexture(p_renderer, "../resources/Main_Menu.png");
    g_pause_menu_bkg = IMG_LoadTexture(p_renderer, "../resources/Pause_Menu.png");
    g_game_over_bkg = IMG_LoadTexture(p_renderer, "../resources/Game_Over_Background.png");
    g_two_player_game_over_bkg = IMG_LoadTexture(p_renderer, "../resources/Two_Player_Game_Over_Background.png");
    g_one_player_bkg = IMG_LoadTexture(p_renderer, "../resources/One_Player_Background.png");
    g_two_player_bkg = IMG_LoadTexture(p_renderer, "../resources/Two_Player_Background.png");
    g_font = TTF_OpenFont("../resources/fonts/Monocraft.ttc", 24);

    if (g_font == NULL) {
        printf("Error: Could not load font\n");
    }

    if (g_block_tex == NULL) {
        printf("Failed to load block texture \n");
    }

    if (g_start_menu_bkg == NULL) {
        printf("Failed to load main menu background texture \n");
    }

    if (g_pause_menu_bkg == NULL) {
        printf("Failed to load pause background texture \n");
    }

    if (g_game_over_bkg == NULL) {
        printf("Failed to load pause background texture \n");
    }

    if (g_one_player_bkg == NULL) {
        printf("Failed to load gameplay background texture \n");
    }

    if (g_two_player_bkg == NULL) {
        printf("Failed to load gameplay background texture \n");
    }
}
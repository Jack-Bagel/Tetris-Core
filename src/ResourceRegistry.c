#include "ResourceRegistry.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// Textures
SDL_Texture *g_block_tex;
SDL_Texture *g_start_menu_bkg;
SDL_Texture *g_pause_menu_bkg;
SDL_Texture *g_game_over_bkg;
SDL_Texture *g_two_player_game_over_bkg;
SDL_Texture *g_one_player_bkg;
SDL_Texture *g_two_player_bkg;

// Fonts
TTF_Font *g_font;

// Sounds & Music
Mix_Music *g_tetris_theme_music;
Mix_Chunk *g_movement_sound;
Mix_Chunk *g_rotate_sound;
Mix_Chunk *g_touch_ground_sound;
Mix_Chunk *g_line_clear_sound;
Mix_Chunk *g_four_lines_clear_sound;
Mix_Chunk *g_next_button_sound;
Mix_Chunk *g_click_button_sound;


void register_resources(SDL_Renderer *p_renderer) {
    // Textures
    g_block_tex = IMG_LoadTexture(p_renderer, "../resources/Tetris_Block.jpg");
    g_start_menu_bkg = IMG_LoadTexture(p_renderer, "../resources/Main_Menu.png");
    g_pause_menu_bkg = IMG_LoadTexture(p_renderer, "../resources/Pause_Menu.png");
    g_game_over_bkg = IMG_LoadTexture(p_renderer, "../resources/Game_Over_Background.png");
    g_two_player_game_over_bkg = IMG_LoadTexture(p_renderer, "../resources/Two_Player_Game_Over_Background.png");
    g_one_player_bkg = IMG_LoadTexture(p_renderer, "../resources/One_Player_Background.png");
    g_two_player_bkg = IMG_LoadTexture(p_renderer, "../resources/Two_Player_Background.png");

    // Fonts
    g_font = TTF_OpenFont("../resources/fonts/Monocraft.ttc", 24);

    // Sounds & Music
    g_tetris_theme_music = Mix_LoadMUS("../resources/sounds/Korobeiniki.mp3");
    g_movement_sound = Mix_LoadWAV("../resources/sounds/Move.wav");
    g_rotate_sound = Mix_LoadWAV("../resources/sounds/Rotate.wav");
    g_touch_ground_sound = Mix_LoadWAV("../resources/sounds/Touch_Ground.wav");
    g_line_clear_sound = Mix_LoadWAV("../resources/sounds/Line_Clear.wav");
    g_four_lines_clear_sound = Mix_LoadWAV("../resources/sounds/Four_Lines_Clear.wav");
    g_next_button_sound = Mix_LoadWAV("../resources/sounds/Button_Select.wav");
    g_click_button_sound = Mix_LoadWAV("../resources/sounds/Click_Button.wav");


    if (g_tetris_theme_music == NULL) {
        printf("Error: Could not load music\n");
    }

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

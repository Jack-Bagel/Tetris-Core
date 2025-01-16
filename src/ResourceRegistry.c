#include "ResourceRegistry.h"
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

// Init in game world
static ResourceRegistry resource_registry = {NULL};

// Feels like bad design
ResourceRegistry *resource_instance() {
    return &resource_registry;
}


void register_resources(SDL_Renderer *p_renderer, ResourceRegistry *resource_registry) {

    // Textures
    resource_registry->s_block_tex = IMG_LoadTexture(p_renderer, "../resources/Tetris_Block.jpg");
    resource_registry->s_start_menu_bkg = IMG_LoadTexture(p_renderer, "../resources/Main_Menu.png");
    resource_registry->s_pause_menu_bkg = IMG_LoadTexture(p_renderer, "../resources/Pause_Menu.png");
    resource_registry->s_game_over_bkg = IMG_LoadTexture(p_renderer, "../resources/Game_Over_Background.png");
    resource_registry->s_two_player_game_over_bkg = IMG_LoadTexture(p_renderer, "../resources/Two_Player_Game_Over_Background.png");
    resource_registry->s_one_player_bkg = IMG_LoadTexture(p_renderer, "../resources/One_Player_Background.png");
    resource_registry->s_two_player_bkg = IMG_LoadTexture(p_renderer, "../resources/Two_Player_Background.png");

    // Fonts
    resource_registry->s_font = TTF_OpenFont("../resources/fonts/Monocraft.ttc", 24);

    // Sounds & Music
    resource_registry->s_tetris_theme_music = Mix_LoadMUS("../resources/sounds/Korobeiniki.mp3");
    resource_registry->s_movement_sound = Mix_LoadWAV("../resources/sounds/Move.wav");
    resource_registry->s_rotate_sound = Mix_LoadWAV("../resources/sounds/Rotate.wav");
    resource_registry->s_touch_ground_sound = Mix_LoadWAV("../resources/sounds/Touch_Ground.wav");
    resource_registry->s_line_clear_sound = Mix_LoadWAV("../resources/sounds/Line_Clear.wav");
    resource_registry->s_four_lines_clear_sound = Mix_LoadWAV("../resources/sounds/Four_Lines_Clear.wav");
    resource_registry->s_next_button_sound = Mix_LoadWAV("../resources/sounds/Button_Select.wav");
    resource_registry->s_click_button_sound = Mix_LoadWAV("../resources/sounds/Click_Button.wav");

    if (resource_registry->s_tetris_theme_music == NULL) {
        printf("Error: Could not load music\n");
    }

    if (resource_registry->s_font == NULL) {
        printf("Error: Could not load font\n");
    }

    if (resource_registry->s_block_tex == NULL) {
        printf("Failed to load block texture \n");
    }

    if (resource_registry->s_start_menu_bkg == NULL) {
        printf("Failed to load main menu background texture \n");
    }

    if (resource_registry->s_pause_menu_bkg == NULL) {
        printf("Failed to load pause background texture \n");
    }

    if (resource_registry->s_game_over_bkg == NULL) {
        printf("Failed to load pause background texture \n");
    }

    if (resource_registry->s_one_player_bkg == NULL) {
        printf("Failed to load gameplay background texture \n");
    }

    if (resource_registry->s_two_player_bkg == NULL) {
        printf("Failed to load gameplay background texture \n");
    }
}

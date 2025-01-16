#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

typedef struct ResourceRegistry {
    
    // Textures
    SDL_Texture *s_block_tex;
    SDL_Texture *s_start_menu_bkg;
    SDL_Texture *s_pause_menu_bkg;
    SDL_Texture *s_game_over_bkg;
    SDL_Texture *s_two_player_game_over_bkg;
    SDL_Texture *s_one_player_bkg;
    SDL_Texture *s_two_player_bkg;

    // Fonts
    TTF_Font *s_font;

    // Sounds & Music
    Mix_Music *s_tetris_theme_music;
    Mix_Chunk *s_movement_sound;
    Mix_Chunk *s_rotate_sound;
    Mix_Chunk *s_touch_ground_sound;
    Mix_Chunk *s_line_clear_sound;
    Mix_Chunk *s_four_lines_clear_sound;
    Mix_Chunk *s_next_button_sound;
    Mix_Chunk *s_click_button_sound;

} ResourceRegistry;

extern ResourceRegistry *resource_instance();
extern void register_resources(SDL_Renderer *p_renderer, ResourceRegistry *resource_registry);

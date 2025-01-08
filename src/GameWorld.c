#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include "SceneHandler.h"
#include "TetrisInputEvent.h"
#include "TetrisUtils.h"
#include "ResourceRegistry.h"
#include "GameWorld.h"

bool is_running = true;

bool initialize_game_world() {

    // Make sure everything is gucci
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Failed to initialize the SDL2 library\n");
        return -1;
    }

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        printf("Failed to initialize the SDL2_image library\n");
        return -1;
    }

    if (TTF_Init() < 0) {
        printf("Failed to initialize the SDL2_ttf library\n");
    }

    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        printf("Failed to initialize the SDL2_mixer library\n");
    }

    // Initialization
    p_window = SDL_CreateWindow("Tetris 95", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    register_resources(p_renderer);
    init_scene();
    reset_game_seed();


    Mix_VolumeMusic(15);
    Mix_Volume(-1, 12);
    if(p_window == NULL) {
        printf("Failed to create window\n");
        return -1;
    }
    
    if(p_renderer == NULL) {
        printf("Failed to get the surface from the window\n");
        return -1;
    }

    return 0;
}

bool run_game_world() {

    while (is_running) {
        update_event(s_players_board);
        update_game(s_players_board, p_window, p_renderer, m_viewport);
    }

    return 0;
}

bool exit_game_world() {
    
    SDL_DestroyWindow(p_window);
    SDL_DestroyRenderer(p_renderer);

    p_window = NULL;
    p_renderer = NULL;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();

    return 0;
}

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "SceneHandler.h"
#include "GameWorld.h"
#include "SceneRenderer.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 1000

bool initialize_game_world() {

    // Make sure everything is gucci
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to initialize the SDL2 library\n");
        return -1;
    }

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        printf("Failed to initialize the SDL2_IMAGE library\n");
        return -1;
    }

    // Initialization
    is_running = true;
    p_window = SDL_CreateWindow("Tetris 95", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);
    init_tetris_scene();
    init_tetris_scene();
    register_textures(p_renderer);

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

bool event(bool *p_is_running) {
    SDL_Event current_event;
    
    while (SDL_PollEvent(&current_event) != 0) {
        switch (current_event.type) {
            case SDL_QUIT:
                *p_is_running = false;
                return false;

            case SDL_KEYDOWN:
                // *p_is_running = false;
                return false;
        }
    }
    return true;
}

bool run_game_world() {

    while (is_running) {
        // event(&is_running);
        place_blocks_on_screen(p_window, p_renderer);
    	// SDL_Delay(100);
    }

    return 0;
}

bool exit_game_world() {
    
    SDL_DestroyWindow(p_window);
    SDL_DestroyRenderer(p_renderer);

    p_window = NULL;
    p_renderer = NULL;
    IMG_Quit();
    SDL_Quit();

    return 0;
}

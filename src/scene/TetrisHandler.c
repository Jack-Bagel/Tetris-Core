#include "TetrisHandler.h"
#include "TetrisRenderer.h"
#include "TetrisLogic.h"
#include "Pieces.h"
#include "TetrisTime.h"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window) {
    int *position = malloc(sizeof(int) * 2); // Free in SceneRenderer "render_block" function
    int w, h;
    SDL_GetWindowSize(p_window, &w, &h);

    position[0] = index_i*size + h/4 - (150);
    position[1] = index_j*size + w/2 - (200);
    // printf("block position: x: %i, y:%i \n", position[1], position[0]);

    return position;
}


void place_blocks_on_screen(SDL_Window *p_window, SDL_Renderer *p_renderer, bool *is_running) {
    // Some variables here should not be recalculated in the game loop
    extern int random_seed; // dogshit design
    extern bool game_start; // dogshit design
    int size = 40.0;
    int *color_value; // Array of 3 elements
    int color_value_test[3] = {255, 0, 0}; // Array of 3 elements

    if (!game_start) {
        reset_tetris_counter();
        *get_falling_piece() = create_piece(1);
        init_new_piece(*get_falling_piece());
        game_start = true;
    }

    update_event(is_running);
    tetris_loop();

    /*** RENDERING ***/

    // Move to TetrisRendering
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 50, 0);
    SDL_RenderClear(p_renderer);

    // print_grid(s_tetris_grid.grid);
    for (int i = 0; i < BOARD_HEIGHT; i++) { //TODO: Read board dimensions from a file
        for (int j = 0; j < BOARD_WIDTH; j++) {

            color_value = get_block_color(get_tetris_grid()->grid[i][j]);

            // No idea why but if I don't run it twice I get rendering issues, need to figure out wtf's going on
            render_block(p_window, p_renderer, index_to_position(i, j, size, p_window), color_value, size);
            render_block(p_window, p_renderer, index_to_position(i, j, size, p_window), color_value, size);
            
            free(color_value); //TODO: avoid using dynamic allocation for the colors
        }
    }

    SDL_RenderPresent(p_renderer);
}


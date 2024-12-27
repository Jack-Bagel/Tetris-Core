#include "TetrisRenderer.h"
#include "TetrisLogic.h"
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


void render_tetris_grid(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer) {
    int *color_value; // Array of 3 elements

    SDL_SetRenderDrawColor(p_renderer, 0, 0, 50, 0);
    SDL_RenderClear(p_renderer);

    for (int i = 0; i < BOARD_HEIGHT; i++) { //TODO: Read board dimensions from a file
        for (int j = 0; j < BOARD_WIDTH; j++) {

            color_value = get_block_color(tetris_grid[i][j]);

            // No idea why but if I don't run it twice I get rendering issues, need to figure out wtf's going on
            render_block(p_window, p_renderer, index_to_position(i, j, piece_size, p_window), color_value, piece_size);
            render_block(p_window, p_renderer, index_to_position(i, j, piece_size, p_window), color_value, piece_size);
            
            free(color_value); //TODO: avoid using dynamic allocation for the colors
        }
    }

    SDL_RenderPresent(p_renderer);
}

void render_block(SDL_Window *p_window, SDL_Renderer *p_renderer, int *position, int *color, int size) {
    int w, h;
    SDL_GetWindowSize(p_window, &w, &h);
    const SDL_Rect block = {.x = position[1], .y = position[0], .w = size, .h = size};
    SDL_RenderCopy(p_renderer, p_texture, NULL, &block);
    SDL_SetTextureColorMod(p_texture, color[0], color[1], color[2]);
    free(position); // I may need to free both pointers, idk if it is done automatically
}

int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window) {
    int *position = malloc(sizeof(int) * 2); // Free in SceneRenderer "render_block" function
    int w, h;
    SDL_GetWindowSize(p_window, &w, &h);

    position[0] = index_i*size + h/5 - (150);
    position[1] = index_j*size + w/2 - (250);

    return position;
}

#include "TetrisRenderer.h"
#include "TetrisLogic.h"
#include "TextureRegistry.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern SDL_Texture *g_p_block;
extern SDL_Texture *g_p_gameplay_background;

void render_tetris_grid(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    int *color_value; // Array of 3 elements


    for (int i = 0; i < BOARD_HEIGHT; i++) { //TODO: Read board dimensions from a file
        for (int j = 0; j < BOARD_WIDTH; j++) {

            color_value = get_block_color(tetris_grid[i][j]);

            // No idea why but if I don't run it twice I get rendering issues, need to figure out wtf's going on
            render_block(p_window, p_renderer, viewport, index_to_position(i, j, piece_size, p_window), color_value, piece_size);
            render_block(p_window, p_renderer, viewport, index_to_position(i, j, piece_size, p_window), color_value, piece_size);
            
            free(color_value); //TODO: avoid using dynamic allocation for the colors
        }
    }

    SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderPresent(p_renderer);
}

void render_block(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int *position, int *color, int size) {
    const SDL_Rect block = {.x = position[1], .y = position[0], .w = size, .h = size};
    SDL_RenderCopy(p_renderer, g_p_block, NULL, &block);
    SDL_SetTextureColorMod(g_p_block, color[0], color[1], color[2]);
    free(position); // I may need to free both pointers, idk if it is done automatically
}

int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window) {
    int *position = malloc(sizeof(int) * 2); // Free in render_tetris_grid()

    position[1] = index_j*size + (500);
    position[0] = index_i*size + (40);

    return position;
}


/** UI **/

void render_gameplay_background(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    SDL_RenderClear(p_renderer);
    const SDL_Rect background = {.x = 0, .y = 0, .w = viewport.w, .h = viewport.h};
    // SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderCopy(p_renderer, g_p_gameplay_background, NULL, &background);
}

void render_score(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {

    TTF_Font *points_font = TTF_OpenFont("../resources/fonts/Minecraft.ttf", 20);

    if (points_font == NULL) {
        printf("Error: Could not load font\n");
    }

    SDL_Color text_color = {255, 255 ,255};
    char temp_str[64];
    sprintf(temp_str, "%d", get_points()); // move integer inside string
    char level_str[] = "Points: ";
    strcat(level_str, temp_str);

    SDL_Surface* surface_message = TTF_RenderText_Solid(points_font, level_str, text_color); 
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
    int tex_w = surface_message->w;
    int tex_h = surface_message->h;

    const SDL_Rect points_rect = {.x = 960, .y = 100, .w = tex_w, .h = tex_h};
    SDL_RenderCopy(p_renderer, texture_message, NULL, &points_rect);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);
    TTF_CloseFont(points_font);
}

void render_level(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {

    TTF_Font *level_font = TTF_OpenFont("../resources/fonts/Minecraft.ttf", 20);

    if (level_font == NULL) {
        printf("Error: Could not load font\n");
    }

    SDL_Color text_color = {255, 255 ,255};
    char temp_str[8];
    sprintf(temp_str, "%d", get_level()); // move integer inside string
    char level_str[] = "Level: ";
    strcat(level_str, temp_str);

    SDL_Surface* surface_message = TTF_RenderText_Solid(level_font, level_str, text_color); 
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
    int tex_w = surface_message->w;
    int tex_h = surface_message->h;

    const SDL_Rect level_rect = {.x = 960, .y = 570, .w = tex_w, .h = tex_h};
    SDL_RenderCopy(p_renderer, texture_message, NULL, &level_rect);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);
    TTF_CloseFont(level_font);
}

void render_next_piece(Piece next_piece, int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    int *color_value; // Array of 3 elements

    for (int i = 0; i < 4; i++) { //TODO: Read board dimensions from a file
        for (int j = 0; j < 4; j++) {
            if (next_piece.tetromino[i][j] != 0) {
                color_value = get_block_color(next_piece.tetromino[i][j] * next_piece.color);

                // No idea why but if I don't run it twice I get rendering issues, need to figure out wtf's going on
                render_block(p_window, p_renderer, viewport, index_to_position_next_piece(i, j, piece_size, p_window), color_value, piece_size);
                render_block(p_window, p_renderer, viewport, index_to_position_next_piece(i, j, piece_size, p_window), color_value, piece_size);
                
                free(color_value); //TODO: avoid using dynamic allocation for the colors
            }

        }
    }
}

int* index_to_position_next_piece(int index_i, int index_j, int size, SDL_Window *p_window) {
    int *position = malloc(sizeof(int) * 2); // Free in render_tetris_grid()

    position[1] = index_j*size + (970);
    position[0] = index_i*size + (300);

    return position;
}

void clear_screen(SDL_Renderer *p_renderer) {
    SDL_SetRenderDrawColor(p_renderer, 0, 30, 30, 0);
    SDL_RenderClear(p_renderer);
}

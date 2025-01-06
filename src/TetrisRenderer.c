#include "TetrisRenderer.h"
#include "TetrisLogic.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern SDL_Texture *g_block_tex;
extern TTF_Font *g_font;

void render_tetris_grid(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y) {
    int *color_value; // Array of 3 elements

    for (int i = 0; i < BOARD_HEIGHT; i++) { //TODO: Read board dimensions from a file
        for (int j = 0; j < BOARD_WIDTH; j++) {

            color_value = get_block_color(tetris_grid[i][j]);

            // No idea why but if I don't run it twice I get rendering issues, need to figure out wtf's going on
            render_block(p_window, p_renderer, viewport, index_to_position(i, j, piece_size, p_window, offset_x, offset_y), color_value, piece_size);
            render_block(p_window, p_renderer, viewport, index_to_position(i, j, piece_size, p_window, offset_x, offset_y), color_value, piece_size);
            
            free(color_value); //TODO: avoid using dynamic allocation for the colors
        }
    }

}

void render_block(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int *position, int *color, int size) {
    const SDL_Rect block = {.x = position[1], .y = position[0], .w = size, .h = size};
    SDL_RenderCopy(p_renderer, g_block_tex, NULL, &block);
    SDL_SetTextureColorMod(g_block_tex, color[0], color[1], color[2]);
    free(position); // I may need to free both pointers, idk if it is done automatically
}

int* index_to_position(int index_i, int index_j, int size, SDL_Window *p_window, int offset_x, int offset_y) {
    int *position = malloc(sizeof(int) * 2); // Free in render_tetris_grid()

    position[1] = index_j*size + (317 + offset_x);
    position[0] = index_i*size + (90 + offset_y);

    return position;
}


/** UI **/

void render_background(SDL_Texture *background_texture, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    const SDL_Rect background = {.x = 0, .y = 0, .w = viewport.w, .h = viewport.h};
    // SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderCopy(p_renderer, background_texture, NULL, &background);
}

void render_score(TetrisBoard *p_tetris_board, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y) {

    SDL_Color text_color = {255, 255 ,255};
    char temp_str[64];
    sprintf(temp_str, "%d", get_points(p_tetris_board)); // move integer inside string
    char level_str[] = "";
    strcat(level_str, temp_str);

    SDL_Surface* surface_message = TTF_RenderText_Solid(g_font, level_str, text_color); 
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
    int tex_w = surface_message->w;
    int tex_h = surface_message->h;

    const SDL_Rect points_rect = {.x = 830 + offset_x, .y = 240 + offset_y, .w = tex_w * 1.4f, .h = tex_h * 1.4f};
    SDL_RenderCopy(p_renderer, texture_message, NULL, &points_rect);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);
}

void render_level(TetrisBoard *p_tetris_board, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y) {

    SDL_Color text_color = {255, 255 ,255};
    char temp_str[8];
    sprintf(temp_str, "%d", get_level(p_tetris_board)); // move integer inside string
    char level_str[] = "";
    strcat(level_str, temp_str);

    SDL_Surface* surface_message = TTF_RenderText_Solid(g_font, level_str, text_color); 
    SDL_Texture* texture_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
    int tex_w = surface_message->w;
    int tex_h = surface_message->h;

    const SDL_Rect level_rect = {.x = 830 + offset_x, .y = 635 + offset_y, .w = tex_w * 1.2f, .h = tex_h * 1.2f};
    SDL_RenderCopy(p_renderer, texture_message, NULL, &level_rect);

    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(texture_message);
}

void render_next_piece(Piece next_piece, int piece_size, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, int offset_x, int offset_y) {
    int *color_value; // Array of 3 elements

    for (int i = 0; i < 4; i++) { //TODO: Read board dimensions from a file
        for (int j = 0; j < 4; j++) {
            if (next_piece.tetromino[i][j] != 0) {
                color_value = get_block_color(next_piece.tetromino[i][j] * next_piece.color);

                // No idea why but if I don't run it twice I get rendering issues, need to figure out wtf's going on
                render_block(p_window, p_renderer, viewport, index_to_position_next_piece(i, j, piece_size, p_window, offset_x, offset_y), color_value, piece_size);
                render_block(p_window, p_renderer, viewport, index_to_position_next_piece(i, j, piece_size, p_window, offset_x, offset_y), color_value, piece_size);
                
                free(color_value); //TODO: avoid using dynamic allocation for the colors
            }

        }
    }
}

int* index_to_position_next_piece(int index_i, int index_j, int size, SDL_Window *p_window, int offset_x, int offset_y) {
    int *position = malloc(sizeof(int) * 2); // Free in render_tetris_grid()

    position[1] = index_j*size + (790) + offset_x;
    position[0] = index_i*size + (420) + offset_y;

    return position;
}

void clear_screen(SDL_Renderer *p_renderer) {
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    SDL_RenderClear(p_renderer);
}

void draw_screen(SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderPresent(p_renderer);
}

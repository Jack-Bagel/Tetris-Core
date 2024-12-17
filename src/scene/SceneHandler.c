#include "SceneHandler.h"
#include "Pieces.h"
#include "Scene.h"
#include "SceneRenderer.h"
#include "TetrisTime.h"
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

bool init_tetris_scene() {
    const int empty_grid[BOARD_HEIGHT][BOARD_WIDTH] = {0};
    s_tetris_grid = initialize_tetris_board();

    memcpy(s_player_tetris_grid.grid, s_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    memcpy(s_piece_grid.grid, empty_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    tetris_counter = 0;
    game_start = false;

    return true; // If everything initialized properly (TODO: add a check)
}

void combine_grids(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            tetris_grid[i][j] |= current_tetromino_grid[i][j];
        }
    }
}

void clear_player_grid() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            s_player_tetris_grid.grid[i][j] &= s_tetris_grid.grid[i][j];
        }
    }
}

void place_blocks_on_screen(SDL_Window *p_window, SDL_Renderer *p_renderer) {
    int w, h;
    SDL_GetWindowSize(p_window, &w, &h);
    srand(random_seed);
    int random_piece = ceil(((double)rand() / (double)RAND_MAX) * 7);
    Piece piece;
    int size = 40.0;
    int *color_value;
    int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH] = {0};

    SDL_SetRenderDrawColor(p_renderer, 0, 0, 50, 0);
    SDL_RenderClear(p_renderer);

    if (!game_start) {
        reset_tetris_counter();
        tetris_counter = get_tetris_counter();
        piece = create_piece(random_piece);
        init_new_piece(piece);
        game_start = true;
    } else {
        tetris_counter = get_tetris_counter();
    }

    move_piece(current_tetromino_grid);
    clear_player_grid();

    // Move to Rendering 
    if (piece_collides(current_tetromino_grid)) {
        combine_grids(s_tetris_grid.grid, s_last_tetromino_grid);
        memcpy(s_player_tetris_grid.grid, s_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
        memset(s_piece_grid.grid, 0, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
        reset_tetris_counter();
        game_start = false;
        random_seed = SDL_GetTicks();

    }

    else {
        // Draw falling piece on tetris grid
        combine_grids(s_player_tetris_grid.grid, current_tetromino_grid);
        memcpy(s_last_tetromino_grid, current_tetromino_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    }

    for (int i = 0; i < BOARD_HEIGHT; i++) { //TODO: Read board dimensions from a file
        for (int j = 0; j < BOARD_WIDTH; j++) {

            color_value = get_block_color(s_player_tetris_grid.grid[i][j]);

            // No idea why but if I don't run it twice I get rendering issues, need to figure out wtf's going on
            // Maybe double buffer issue idk.
            render_block(p_window, p_renderer, index_to_position(i, j, size, p_window), color_value, size);
            render_block(p_window, p_renderer, index_to_position(i, j, size, p_window), color_value, size);
            
            free(color_value); //TODO: avoid using dynamic allocation for the colors
        }
    }

    SDL_RenderPresent(p_renderer);
}

bool piece_collides(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]) {

    if (piece_touches_ground(current_tetromino_grid)){

        return true;
    }
    
    // This fails after a certain time when pieces reach the hight limit
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if ((s_tetris_grid.grid[i][j] + current_tetromino_grid[i][j]) != s_tetris_grid.grid[i][j]) {
                if ((s_tetris_grid.grid[i][j] + current_tetromino_grid[i][j]) != current_tetromino_grid[i][j]) { 
                    return true;
                }
            }
        }
    }

    return false;
}

bool piece_touches_ground(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]) {
    
    for (int j = 0; j < 9; j++) {
        if (current_tetromino_grid[21][j] != 0) { 
            return true;
        } 
    }
    
    return false;
}

void move_right() {
    int tetromino_line[BOARD_WIDTH];

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < BOARD_WIDTH; j++) {
            tetromino_line[j] = s_piece_grid.grid[i][j];
        }

        if (tetromino_line[BOARD_WIDTH - 2] != 0) {
            return;
        }

        for (int j = 0; j < BOARD_WIDTH; j++) {
            s_piece_grid.grid[i][j + 1] = tetromino_line[j];
        }

        s_piece_grid.grid[i][0] = 0;
    }
}

void move_left() {
    int tetromino_line[BOARD_WIDTH];

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < BOARD_WIDTH; j++) {
            tetromino_line[j] = s_piece_grid.grid[i][j];
        }

        if (tetromino_line[1] != 0) {
            return;
        }

        for (int j = 0; j < BOARD_WIDTH; j++) {
            s_piece_grid.grid[i][j - 1] = tetromino_line[j];
        }

        s_piece_grid.grid[i][0] = 0;
    }
}

void move_piece(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]) {
    SDL_Event current_event;
    make_piece_fall(current_tetromino_grid);
    while (SDL_PollEvent(&current_event) != 0) {
        switch (current_event.type) {
            case SDL_KEYDOWN:
                switch (current_event.key.keysym.sym) {
                    case SDLK_a: 
                        move_left();
                        break;
                    case SDLK_d:
                        move_right();
                        break;
                }
            break;
        }
    }
}

// Find a nice way to move the row down without having to handle the out of index
void make_piece_fall(int current_tetromino_grid[BOARD_HEIGHT][BOARD_WIDTH]) {
    // Segfaults when counter gets bigger than 21
    // After a while, the counter starts incrementing again
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {

            if (i + tetris_counter == BOARD_HEIGHT + 1) {
                index = i - 3;
            }
            else {
                index = i;
            }

            current_tetromino_grid[index + tetris_counter][j] = s_piece_grid.grid[i][j];
        }
    }
}

// Use a sliding window
int** read_four_lines(int tetris_grid[BOARD_HEIGHT][BOARD_WIDTH], int offset) {
    int row = 4;
    int column = BOARD_WIDTH;

    int** four_lines = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        four_lines[i] = (int*)malloc(sizeof(int) * column);
    }

    if (offset > 17) {
        printf("Offset is out of bounds \n");
        return NULL;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            four_lines[i][j] = tetris_grid[i + offset][j];
        }
    }

    // printf("*****************************");
    // for (int i = 0; i < row; i++) {
    //     printf("\n");
    //     for (int j = 0; j < column; j++) {
    //         printf("%i, ", four_lines[i][j]);
    //     }
    // }
    // printf("\n*****************************\n");
    
    return four_lines;
}

void init_new_piece(Piece piece) {
    int tetromino_line[4] = {1, 1, 1, 1};

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
            tetromino_line[j] = piece.tetromino[i][j];
        }

        for (int j = 3; j < 7; j++) {
            if (tetromino_line[j - 3] != 0) {
                s_piece_grid.grid[i + 1][j + 1] = piece.type;
            }
        }
    }
}

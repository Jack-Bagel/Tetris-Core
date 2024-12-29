#include "TetrisHandler.h"
#include "TetrisLogic.h"
#include "TetrisPauseScene.h"
#include "TetrisRenderer.h"
#include "TetrisStartScreen.h"
#include "TetrisTime.h"
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

extern bool g_game_start; // dogshit design

void init_scene() {
    s_current_scene = 0;
}

void set_current_scene(u_int scene) {
    s_current_scene = scene;
}

u_int get_current_scene() {
    return s_current_scene;
}

void update_game(TetrisBoard *p_tetris_board, SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    int size = 32.0; // Size of tetris blocks, move to rendering

    // Start screen
    if (s_current_scene == 0) {
        render_background(p_window, p_renderer, viewport);
        render_buttons(p_window, p_renderer, viewport);
    }

    // One player
    else if (s_current_scene == 1) {
        if (!g_game_start) {

            if (!init_tetris_board(p_tetris_board)) {
                printf("Failed to initialize Tetris Scene\n");
            }

            reset_tetris_counter();
            generate_new_piece(p_tetris_board, time(NULL));
            g_game_start = true;
            printf("GAME STARTS\n");
        }

        tetris_loop(p_tetris_board);
        clear_screen(p_renderer);
        // render_gameplay_background(p_window, p_renderer, viewport);
        render_score(p_tetris_board, p_window, p_renderer, viewport);
        render_level(p_tetris_board, p_window, p_renderer, viewport);
        render_next_piece(get_next_piece(p_tetris_board), size, p_window, p_renderer, viewport);
        render_tetris_grid(get_tetris_grid(p_tetris_board)->grid, size, p_window, p_renderer, viewport);
    }

    // Two players
    else if (s_current_scene == 2) {
        render_pause_background(p_window, p_renderer, viewport);
        render_pause_buttons(p_window, p_renderer, viewport);
    }

}


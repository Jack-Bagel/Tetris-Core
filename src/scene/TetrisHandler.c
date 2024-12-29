#include "TetrisHandler.h"
#include "GameWorld.h"
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
    m_current_scene = 0;
}

void set_current_scene(u_int scene) {
    m_current_scene = scene;
}

u_int get_current_scene() {
    return m_current_scene;
}

void update_game(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    int size = 32.0;

    // Start screen
    if (m_current_scene == 0) {
        render_background(p_window, p_renderer, viewport);
        render_buttons(p_window, p_renderer, viewport);
    }

    // One player
    else if (m_current_scene == 1) {
        if (!g_game_start) {

            if (!initialize_tetris_scene()) {
                printf("Failed to initialize Tetris Scene\n");
            }

            reset_tetris_counter();
            generate_new_piece(time(NULL));
            g_game_start = true;
            printf("GAME STARTS\n");
        }

        tetris_loop();
        clear_screen(p_renderer);
        // render_gameplay_background(p_window, p_renderer, viewport);
        render_score(p_window, p_renderer, viewport);
        render_level(p_window, p_renderer, viewport);
        render_next_piece(get_next_piece(), size, p_window, p_renderer, viewport);
        render_tetris_grid(get_tetris_grid()->grid, size, p_window, p_renderer, viewport);
    }

    // Two players
    else if (m_current_scene == 2) {
        render_pause_background(p_window, p_renderer, viewport);
        render_pause_buttons(p_window, p_renderer, viewport);
    }

}


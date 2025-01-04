#include "TetrisHandler.h"
#include "TetrisLogic.h"
#include "TetrisPauseScene.h"
#include "TetrisRenderer.h"
#include "TetrisStartScreen.h"
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

extern SDL_Texture *g_one_player_bkg;
extern SDL_Texture *g_two_player_bkg;
extern SDL_Texture *g_two_player_bkg;
extern SDL_Texture *g_start_menu_bkg;

void init_scene() {
    s_current_scene = 0;
    s_last_scene = 0;
}

void set_current_scene(u_int scene) {
    s_last_scene = s_current_scene;
    s_current_scene = scene;
}

u_int get_current_scene() {
    return s_current_scene;
}

u_int get_last_scene() {
    return s_last_scene;
}

void update_game(TetrisBoard players_board[2], SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    int piece_size = 32.0; // Size of tetris blocks, move to rendering
    int next_piece_size = 29.0; // Size of tetris blocks, move to rendering

    // Start screen
    if (s_current_scene == 0) {
        clear_screen(p_renderer);
        render_background(g_start_menu_bkg, p_window, p_renderer, viewport);
        render_buttons(p_window, p_renderer, viewport);
    }

    // One player
    else if (s_current_scene == 1) {
        tetris_loop(&players_board[0]);

        // Rendering 
        clear_screen(p_renderer);
        render_tetris_grid(get_tetris_grid(&players_board[0])->grid, piece_size, p_window, p_renderer, viewport, 0, 0);
        render_background(g_one_player_bkg ,p_window, p_renderer, viewport);

        render_score(&players_board[0], p_window, p_renderer, viewport, 0, 0);
        render_level(&players_board[0], p_window, p_renderer, viewport, 0, 0);
        render_next_piece(get_next_piece(&players_board[0]), next_piece_size, p_window, p_renderer, viewport, 0, 0);
        draw_screen(p_renderer, viewport);
    }
    
    // Pause screen
    else if (s_current_scene == 2) {
            render_pause_background(p_window, p_renderer, viewport);
            render_pause_buttons(p_window, p_renderer, viewport);
    }

    // Two players
    else if (s_current_scene == 3) {
        tetris_loop(&players_board[0]);
        tetris_loop(&players_board[1]);

        // Rendering
        clear_screen(p_renderer);

        // Render grids behind background
        render_tetris_grid(get_tetris_grid(&players_board[0])->grid, piece_size, p_window, p_renderer, viewport, -336, 15);
        render_tetris_grid(get_tetris_grid(&players_board[1])->grid, piece_size, p_window, p_renderer, viewport, + 278, 15);
        render_background(g_two_player_bkg ,p_window, p_renderer, viewport);

        // Render UI on top

        // Player 1
        render_score(&players_board[0], p_window, p_renderer, viewport, -490, -165);
        render_level(&players_board[0], p_window, p_renderer, viewport, -710, -560);
        render_next_piece(get_next_piece(&players_board[0]), next_piece_size, p_window, p_renderer, viewport, -373, -100);

        // Player 2
        render_score(&players_board[1], p_window, p_renderer, viewport, - 205, -165);
        render_level(&players_board[1], p_window, p_renderer, viewport, + 50, -560);
        render_next_piece(get_next_piece(&players_board[1]), next_piece_size, p_window, p_renderer, viewport, -291, 170);

        draw_screen(p_renderer, viewport);
    }

}

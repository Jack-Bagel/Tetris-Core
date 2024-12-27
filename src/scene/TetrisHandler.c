#include "TetrisHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"
#include "TetrisTime.h"
#include <stdbool.h>
#include <time.h>

void place_blocks_on_screen(SDL_Window *p_window, SDL_Renderer *p_renderer, bool *is_running) {
    extern bool g_game_start; // dogshit design
    int size = 40.0;

    if (!g_game_start) {
        reset_tetris_counter();
        generate_new_piece(time(NULL));
        g_game_start = true;
    }

    tetris_loop();
    render_tetris_grid(get_tetris_grid()->grid, size, p_window, p_renderer);
}


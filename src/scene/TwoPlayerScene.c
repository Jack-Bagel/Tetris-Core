#include "TwoPlayerScene.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"

extern SDL_Texture *g_two_player_bkg;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);

void init_two_player(PlayableScene *scene) {
    scene->update = &update_playable;
}

void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard players_board[2]) {
    tetris_loop(&players_board[0]);
    tetris_loop(&players_board[1]);
    render_playable(p_window, p_renderer, viewport, players_board);
    handle_event = &events;
}

void render_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard players_board[2]) {
    int piece_size = 32.0; // Size of tetris blocks, move to rendering
    int next_piece_size = 29.0; // Size of tetris blocks, move to rendering


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

void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    pause_tetris_counter(&p_tetris_board[0].m_counter);
                    pause_tetris_counter(&p_tetris_board[1].m_counter);
                    set_current_scene(2);
                break;


                // Player 1 Controls
                case SDLK_a:
                    move_left(&p_tetris_board[0]);
                break;

                case SDLK_d:
                    move_right(&p_tetris_board[0]);
                break;

                case SDLK_w:
                case SDLK_x:
                    rotate_piece_clockwise(&p_tetris_board[0]);
                break;

                case SDLK_s:
                    accelerate_piece(&p_tetris_board[0].m_counter);
                break;

                // Player 2 Controls
                case SDLK_LEFT:
                    move_left(&p_tetris_board[1]);
                break;

                case SDLK_RIGHT:
                    move_right(&p_tetris_board[1]);
                break;

                case SDLK_UP:
                    rotate_piece_clockwise(&p_tetris_board[1]);
                break;

                case SDLK_DOWN:
                    accelerate_piece(&p_tetris_board[1].m_counter);
                break;
            }

        break;

        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
                // Player 1 Controls
                case SDLK_s:
                    reset_piece_acceleration(&p_tetris_board[0].m_counter);
                break;

                // Player 2 Controls
                case SDLK_DOWN:
                    reset_piece_acceleration(&p_tetris_board[1].m_counter);
                break;
            }
    }

}

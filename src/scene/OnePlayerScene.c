#include "OnePlayerScene.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"

extern SDL_Texture *g_one_player_bkg;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);

void init_one_player(PlayableScene *scene) {
    scene->update = &update_playable;
}

void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard *p_player_one_board) {
    tetris_loop(p_player_one_board);
    render_playable(p_window, p_renderer, viewport, p_player_one_board);
    handle_event = &events;
}

void render_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard *p_player_one_board) {
    int piece_size = 32.0; // Size of tetris blocks, move to rendering
    int next_piece_size = 29.0; // Size of tetris blocks, move to rendering

    clear_screen(p_renderer);
    render_tetris_grid(get_tetris_grid(p_player_one_board)->grid, piece_size, p_window, p_renderer, viewport, 0, 0);
    render_background(g_one_player_bkg ,p_window, p_renderer, viewport);

    render_score(p_player_one_board, p_window, p_renderer, viewport, 0, 0);
    render_level(p_player_one_board, p_window, p_renderer, viewport, 0, 0);
    render_next_piece(get_next_piece(p_player_one_board), next_piece_size, p_window, p_renderer, viewport, 0, 0);
    draw_screen(p_renderer, viewport);
}

void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    pause_tetris_counter(&p_tetris_board[0].m_counter);
                    set_current_scene(2);
                break;

                case SDLK_LEFT:
                case SDLK_a:
                    move_left(&p_tetris_board[0]);
                break;


                case SDLK_RIGHT:
                case SDLK_d:
                    move_right(&p_tetris_board[0]);
                break;

                case SDLK_UP:
                case SDLK_w:
                case SDLK_x:
                    rotate_piece_clockwise(&p_tetris_board[0]);
                break;

                case SDLK_DOWN:
                case SDLK_s:
                    accelerate_piece(&p_tetris_board[0].m_counter);
                break;
            }

        break;


        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
                case SDLK_DOWN:
                case SDLK_s:
                    reset_piece_acceleration(&p_tetris_board[0].m_counter);
                break;
            }
    }
}

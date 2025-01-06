#include "OnePlayerScene.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"
#include <SDL_timer.h>

extern SDL_Texture *g_one_player_bkg;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);

static bool pressed_left = false;
static bool pressed_right = false;
static bool pressed_rotate_clock = false;
static bool pressed_rotate_counter = false;
static unsigned int first_elapsed_time[4] = {0, 0, 0, 0};
static unsigned int elapsed_time[4] = {0, 0, 0, 0};

#define INPUT_LAG 30
#define WAITING_LAG 150

void init_one_player(PlayableScene *p_scene) {
    p_scene->update = &update_playable;
}

void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard players_board[2]) {
    tetris_loop(players_board);
    render_playable(p_window, p_renderer, viewport, players_board);
    movements(players_board);
    handle_event = &events;
}

void render_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard players_board[2]) {
    int piece_size = 32.0; // Size of tetris blocks, move to rendering
    int next_piece_size = 29.0; // Size of tetris blocks, move to rendering

    clear_screen(p_renderer);
    render_tetris_grid(get_tetris_grid(&players_board[0])->grid, piece_size, p_window, p_renderer, viewport, 0, 0);
    render_background(g_one_player_bkg ,p_window, p_renderer, viewport);

    render_score(&players_board[0], p_window, p_renderer, viewport, 0, 0);
    render_level(&players_board[0], p_window, p_renderer, viewport, 0, 0);
    render_next_piece(get_next_piece(&players_board[0]), next_piece_size, p_window, p_renderer, viewport, 0, 0);
    draw_screen(p_renderer, viewport);
}

void movements(TetrisBoard p_tetris_board[2]) {
    // Move left
    if (pressed_left && elapsed_time[0] == 0) {
        first_elapsed_time[0] = SDL_GetTicks();
        elapsed_time[0] = SDL_GetTicks();
        move_left(&p_tetris_board[0]);
    }

    else if (pressed_left && (SDL_GetTicks() - first_elapsed_time[0]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time[0]) > INPUT_LAG) {
        move_left(&p_tetris_board[0]);
        elapsed_time[0] = SDL_GetTicks();
    }

    // Move right
    if (pressed_right && elapsed_time[1] == 0) {
        first_elapsed_time[1] = SDL_GetTicks();
        elapsed_time[1] = SDL_GetTicks();
        move_right(&p_tetris_board[0]);
    }

    else if (pressed_right && (SDL_GetTicks() - first_elapsed_time[1]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time[1]) > INPUT_LAG) {
        move_right(&p_tetris_board[0]);
        elapsed_time[1] = SDL_GetTicks();
    }

    // Rotate Clockwise
    if (pressed_rotate_clock && elapsed_time[2] == 0) {
        first_elapsed_time[2] = SDL_GetTicks();
        elapsed_time[2] = SDL_GetTicks();
        rotate_piece_clockwise(&p_tetris_board[0]);
    }

    else if (pressed_rotate_clock && (SDL_GetTicks() - first_elapsed_time[2]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time[2]) > INPUT_LAG) {
        rotate_piece_clockwise(&p_tetris_board[0]);
        elapsed_time[2] = SDL_GetTicks();
    }

    // Rotate Counter Clockwise
    if (pressed_rotate_counter && elapsed_time[3] == 0) {
        first_elapsed_time[3] = SDL_GetTicks();
        elapsed_time[3] = SDL_GetTicks();
        rotate_piece_counter_clockwise(&p_tetris_board[0]);
    }

    else if (pressed_rotate_counter && (SDL_GetTicks() - first_elapsed_time[3]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time[3]) > INPUT_LAG) {
        rotate_piece_counter_clockwise(&p_tetris_board[0]);
        elapsed_time[3] = SDL_GetTicks();
    }
}

void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {

    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    pause_tetris_counter(&p_tetris_board[0].m_counter);
                    set_current_scene(PAUSE_MENU);
                break;

                case SDLK_LEFT:
                case SDLK_a:
                    pressed_left = true;
                break;

                case SDLK_RIGHT:
                case SDLK_d:
                    pressed_right = true;
                break;

                case SDLK_UP:
                case SDLK_w:
                case SDLK_x:
                    pressed_rotate_clock = true;
                break;

                case SDLK_z:
                    pressed_rotate_counter = true;
                break;

                case SDLK_DOWN:
                case SDLK_s:
                    accelerate_piece(&p_tetris_board[0].m_counter);
                break;
            }

        break;

        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_a:
                    pressed_left = false;
                    first_elapsed_time[0] = 0;
                    elapsed_time[0] = 0;
                break;

                case SDLK_RIGHT:
                case SDLK_d:
                    pressed_right = false;
                    first_elapsed_time[1] = 0;
                    elapsed_time[1] = 0;
                break;

                case SDLK_UP:
                case SDLK_w:
                case SDLK_x:
                    pressed_rotate_clock = false;
                    first_elapsed_time[2] = 0;
                    elapsed_time[2] = 0;
                break;

                case SDLK_z:
                    pressed_rotate_counter = false;
                    first_elapsed_time[3] = 0;
                    elapsed_time[3] = 0;
                break;

                case SDLK_DOWN:
                case SDLK_s:
                    reset_piece_acceleration(&p_tetris_board[0].m_counter);
                break;
            }
    }
}

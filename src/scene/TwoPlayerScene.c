#include "TwoPlayerScene.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"

extern SDL_Texture *g_two_player_bkg;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);

// Player 1
static bool pressed_left = false;
static bool pressed_right = false;
static bool pressed_rotate_clock = false;
static bool pressed_rotate_counter = false;
static unsigned int first_elapsed_time[4] = {0, 0, 0, 0};
static unsigned int elapsed_time[4] = {0, 0, 0, 0};

// Player 2
static bool pressed_left_two = false;
static bool pressed_right_two = false;
static bool pressed_rotate_clock_two = false;
static bool pressed_rotate_counter_two = false;
static unsigned int first_elapsed_time_two[4] = {0, 0, 0, 0};
static unsigned int elapsed_time_two[4] = {0, 0, 0, 0};

#define INPUT_LAG 30
#define WAITING_LAG 150

void init_two_player(PlayableScene *scene) {
    scene->update = &update_playable;
}

void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]) {
    tetris_loop(&player_board[0]);
    tetris_loop(&player_board[1]);
    movements(player_board);
    render_playable(p_window, p_renderer, viewport, player_board);
    handle_event = &events;

    if (get_game_over(&player_board[0]) && get_game_over(&player_board[1])) {
        set_current_scene(GAME_OVER);
    }
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
    render_lines(&players_board[0], p_window, p_renderer, viewport, 223, 845);
    render_next_piece(get_next_piece(&players_board[0]), next_piece_size, p_window, p_renderer, viewport, -373, -100);

    // Player 2
    render_score(&players_board[1], p_window, p_renderer, viewport, - 205, -165);
    render_level(&players_board[1], p_window, p_renderer, viewport, + 50, -560);
    render_lines(&players_board[1], p_window, p_renderer, viewport, 845, 845);
    render_next_piece(get_next_piece(&players_board[1]), next_piece_size, p_window, p_renderer, viewport, -291, 170);

    draw_screen(p_renderer, viewport);
}

void movements(TetrisBoard p_tetris_board[2]) {
    //Playe One

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

    //Playe Two

    // Move left
    if (pressed_left_two && elapsed_time_two[0] == 0) {
        first_elapsed_time_two[0] = SDL_GetTicks();
        elapsed_time_two[0] = SDL_GetTicks();
        move_left(&p_tetris_board[1]);
    }

    else if (pressed_left_two && (SDL_GetTicks() - first_elapsed_time_two[0]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time_two[0]) > INPUT_LAG) {
        elapsed_time_two[0] = SDL_GetTicks();
        move_left(&p_tetris_board[1]);
    }

    // Move right
    if (pressed_right_two && elapsed_time_two[1] == 0) {
        first_elapsed_time_two[1] = SDL_GetTicks();
        elapsed_time_two[1] = SDL_GetTicks();
        move_right(&p_tetris_board[1]);
    }

    else if (pressed_right_two && (SDL_GetTicks() - first_elapsed_time_two[1]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time_two[1]) > INPUT_LAG) {
        elapsed_time_two[1] = SDL_GetTicks();
        move_right(&p_tetris_board[1]);
    }

    // Rotate Clockwise
    if (pressed_rotate_clock_two && elapsed_time_two[2] == 0) {
        first_elapsed_time_two[2] = SDL_GetTicks();
        elapsed_time_two[2] = SDL_GetTicks();
        rotate_piece_clockwise(&p_tetris_board[1]);
    }

    else if (pressed_rotate_clock_two && (SDL_GetTicks() - first_elapsed_time_two[2]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time_two[2]) > INPUT_LAG) {
        rotate_piece_clockwise(&p_tetris_board[1]);
        elapsed_time_two[2] = SDL_GetTicks();
    }

    // Rotate Counter Clockwise
    if (pressed_rotate_counter_two && elapsed_time_two[3] == 0) {
        first_elapsed_time_two[3] = SDL_GetTicks();
        elapsed_time_two[3] = SDL_GetTicks();
        rotate_piece_counter_clockwise(&p_tetris_board[1]);
    }

    else if (pressed_rotate_counter_two && (SDL_GetTicks() - first_elapsed_time_two[3]) > WAITING_LAG && (SDL_GetTicks() - elapsed_time_two[3]) > INPUT_LAG) {
        rotate_piece_counter_clockwise(&p_tetris_board[1]);
        elapsed_time_two[3] = SDL_GetTicks();
    }
}

void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    pause_tetris_counter(&p_tetris_board[0].m_counter);
                    pause_tetris_counter(&p_tetris_board[1].m_counter);
                    set_current_scene(PAUSE_MENU);
                break;


                // Player 1 Controls
                case SDLK_a:
                    pressed_left = true;
                break;

                case SDLK_d:
                    pressed_right = true;
                break;

                case SDLK_w:
                case SDLK_x:
                    pressed_rotate_clock = true;
                break;

                case SDLK_z:
                    pressed_rotate_counter = true;
                break;

                case SDLK_s:
                    accelerate_piece(&p_tetris_board[0].m_counter);
                break;

                // Player 2 Controls
                case SDLK_LEFT:
                    pressed_left_two = true;
                break;

                case SDLK_RIGHT:
                    pressed_right_two = true;
                break;

                case SDLK_UP:
                    pressed_rotate_clock_two = true;
                break;

                case SDLK_m:
                    pressed_rotate_counter_two = true;
                break;

                case SDLK_DOWN:
                    accelerate_piece(&p_tetris_board[1].m_counter);
                break;
            }

        break;

        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
                // Player 1 Controls
                case SDLK_a:
                    first_elapsed_time[0] = 0;
                    elapsed_time[0] = 0;
                    pressed_left = false;
                break;

                case SDLK_d:
                    first_elapsed_time[1] = 0;
                    elapsed_time[1] = 0;
                    pressed_right = false;
                break;

                case SDLK_w:
                case SDLK_x:
                    first_elapsed_time[2] = 0;
                    elapsed_time[2] = 0;
                    pressed_rotate_clock = false;
                break;

                case SDLK_z:
                    first_elapsed_time[3] = 0;
                    elapsed_time[3] = 0;
                    pressed_rotate_counter = false;
                break;

                case SDLK_s:
                    reset_piece_acceleration(&p_tetris_board[0].m_counter);
                break;

                // Player 2 Controls
                case SDLK_LEFT:
                    first_elapsed_time_two[0] = 0;
                    elapsed_time_two[0] = 0;
                    pressed_left_two = false;
                break;
                case SDLK_RIGHT:
                    first_elapsed_time_two[1] = 0;
                    elapsed_time_two[1] = 0;
                    pressed_right_two = false;
                break;

                case SDLK_UP:
                    first_elapsed_time_two[2] = 0;
                    elapsed_time_two[2] = 0;
                    pressed_rotate_clock_two = false;
                break;

                case SDLK_m:
                    first_elapsed_time_two[3] = 0;
                    elapsed_time_two[3] = 0;
                    pressed_rotate_counter_two = false;
                break;
                case SDLK_DOWN:
                    reset_piece_acceleration(&p_tetris_board[1].m_counter);
                break;

            }
    }

}

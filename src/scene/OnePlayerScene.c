#include "OnePlayerScene.h"
#include "EventListener.h"
#include "Pieces.h"
#include "ResourceRegistry.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"
#include <SDL2/SDL_timer.h>

#define INPUT_LAG 30
#define WAITING_LAG 150

extern void (*handle_event)(TetrisBoard[2], SDL_Event *);


static void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard p_player_one_board[2]);
static void render_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard p_player_one_board[2]);
static void render_statistics(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void update_statistics(void* event_data);
static void reset_statistics(void* event_data);
static void movements(TetrisBoard p_tetris_board[2]);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

// This is probably the worst way to handle inputs delay
static bool pressed_left = false;
static bool pressed_right = false;
static bool pressed_rotate_clock = false;
static bool pressed_rotate_counter = false;
static unsigned int first_elapsed_time[4] = {0, 0, 0, 0};
static unsigned int elapsed_time[4] = {0, 0, 0, 0};
static unsigned int piece_stats[8] = {0};

static EventListener update_statistics_event = {.callback = &update_statistics, .type = NEW_PIECE_EVENT};
static EventListener reset_statistics_event = {.callback = &reset_statistics, .type = GAME_RESTART_EVENT};


void init_one_player(PlayableScene *p_scene) {
    p_scene->update = &update_playable;
}

void register_one_player_listeners() {
    sub_event_listener(&update_statistics_event);
    sub_event_listener(&reset_statistics_event);
}

static void update_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]) {
    tetris_loop(player_board);
    render_playable(p_window, p_renderer, viewport, player_board);
    movements(player_board);
    handle_event = &events;

    if (get_game_over(&player_board[0])) {
        set_current_scene(GAME_OVER);
    }
}

static void render_playable(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]) {
    int piece_size = 32.0; // Size of tetris blocks, move to rendering
    int next_piece_size = 29.0; // Size of tetris blocks, move to rendering

    clear_screen(p_renderer);
    render_tetris_grid(player_board[0].m_tetris_grid.grid, piece_size, p_window, p_renderer, viewport, 317, 90);
    render_background(resource_instance()->s_one_player_bkg ,p_window, p_renderer, viewport);

    render_top_score(&player_board[0], p_window, p_renderer, viewport, 830, 140);
    render_score(&player_board[0], p_window, p_renderer, viewport, 830, 240);
    render_level(&player_board[0], p_window, p_renderer, viewport, 830, 635);
    render_lines(&player_board[0], p_window, p_renderer, viewport, 620, 60);
    render_statistics(p_window, p_renderer, viewport);
    render_next_piece(get_next_piece(&player_board[0]), next_piece_size, p_window, p_renderer, viewport, 790, 420);
    draw_screen(p_renderer, viewport);
}


static void render_statistics(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    SDL_Color text_color = {155, 0 ,0};
    char temp_str[8];
    for (int i =0; i < 7; i++) {
        sprintf(temp_str, "%d", piece_stats[i]); // move integer inside string
        char level_str[] = "";
        strcat(level_str, temp_str);

        SDL_Surface* surface_message = TTF_RenderText_Solid(resource_instance()->s_font, level_str, text_color);
        SDL_Texture* texture_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
        int tex_w = surface_message->w;
        int tex_h = surface_message->h;

        const SDL_Rect level_rect = {.x = 250, .y = 320 + 70*i, .w = tex_w * 1.2f, .h = tex_h * 1.2f};
        SDL_RenderCopy(p_renderer, texture_message, NULL, &level_rect);

        SDL_FreeSurface(surface_message);
        SDL_DestroyTexture(texture_message);
    }

    render_next_piece(create_piece(T_BLOCK), 27, p_window, p_renderer, viewport, 140, 290);
    render_next_piece(create_piece(R_L_BLOCK), 27, p_window, p_renderer, viewport, 140, 355);
    render_next_piece(create_piece(Z_BLOCK), 27, p_window, p_renderer, viewport, 140, 425);
    render_next_piece(create_piece(SQUARE_BLOCK), 27, p_window, p_renderer, viewport, 170, 495);
    render_next_piece(create_piece(R_Z_BLOCK), 27, p_window, p_renderer, viewport, 142, 565);
    render_next_piece(create_piece(L_BLOCK), 27, p_window, p_renderer, viewport, 140, 635);
    render_next_piece(create_piece(LINE_BLOCK), 27, p_window, p_renderer, viewport, 115, 705);
}

static void update_statistics(void* event_data) {
    Piece current_piece = *(Piece*) event_data;

    switch (current_piece.type) {
        case T_BLOCK:
            piece_stats[0]++;
        break;

        case R_L_BLOCK:
            piece_stats[1]++;
        break;

        case Z_BLOCK:
            piece_stats[2]++;
        break;

        case SQUARE_BLOCK:
            piece_stats[3]++;
        break;

        case R_Z_BLOCK:
            piece_stats[4]++;
        break;

        case L_BLOCK:
            piece_stats[5]++;
        break;

        case LINE_BLOCK:
            piece_stats[6]++;
        break;

        default:
            piece_stats[7]++;
    
    }

}


static void reset_statistics(void* event_data) {
    for (int i = 0; i < 8; i++) {
        piece_stats[i] = 0;
    }
}

static void movements(TetrisBoard p_tetris_board[2]) {
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

static void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {

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

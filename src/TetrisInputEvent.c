#include "TetrisInputEvent.h"
#include "GameWorld.h"
#include "TetrisHandler.h"
#include "TetrisLogic.h"
#include "TetrisPauseScene.h"
#include "TetrisStartScreen.h"
#include "TetrisTime.h"
#include "TetrisUtils.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

void (*handle_event)(TetrisBoard[2], SDL_Event *) = &main_menu_handler;

void one_player_handler(TetrisBoard p_tetris_board[2], SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    pause_tetris_counter(&p_tetris_board[0].m_counter);
                    set_current_scene(2);
                    handle_event = &pause_menu_handler;
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

void two_player_handler(TetrisBoard p_tetris_board[2], SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    pause_tetris_counter(&p_tetris_board[0].m_counter);
                    pause_tetris_counter(&p_tetris_board[1].m_counter);
                    set_current_scene(2);
                    handle_event = &pause_menu_handler;
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

void main_menu_handler(TetrisBoard p_tetris_board[2], SDL_Event *event) {
        switch (event->type) {
            case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {

                case SDLK_LEFT:
                case SDLK_a:
                    decrease_button_selection();
                break;

                case SDLK_RIGHT:
                case SDLK_d:
                    increase_button_selection();
                break;

                case SDLK_RETURN:
                    switch (get_button_selection()) {
                        // Start One Player Game
                        case 0:
                            set_current_scene(1);
                            handle_event = &one_player_handler;
                        break;
                        // Start Two Player Game
                        case 1:
                            set_current_scene(3);
                            handle_event = &two_player_handler;
                        break;
                        // Exit Game
                        case 2:
                            printf("CLOSE GAME\n");
                            is_running = false;
                        break;
                    }
                break;
            }

        break;
    }
}

void pause_menu_handler(TetrisBoard p_tetris_board[2], SDL_Event *event) {
        switch (event->type) {
            case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {

                case SDLK_ESCAPE:
                    // One Player Scene
                    if (get_last_scene() == 1) { 
                        set_current_scene(1);
                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                        handle_event = &one_player_handler;
                    }
                    // Two Players Scene
                    else if (get_last_scene() == 3) {
                        set_current_scene(3);
                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                        unpause_tetris_counter(&p_tetris_board[1].m_counter);
                        handle_event = &two_player_handler;
                    }
                break;

                case SDLK_LEFT:
                case SDLK_a:
                    decrease_pause_button_selection();
                break;

                case SDLK_RIGHT:
                case SDLK_d:
                    increase_pause_button_selection();
                break;

                case SDLK_RETURN:
                    switch (get_pause_button_selection()) {
                        // Continue Game
                        case 0:
                            // One Player
                            if (get_last_scene() == 1) {
                                set_current_scene(1);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                handle_event = &one_player_handler;
                            }
                            // Two Players
                            else if (get_last_scene() == 3) {
                                set_current_scene(3);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                handle_event = &two_player_handler;
                            }
                        break;

                        // Reset Game
                        case 1:
                            // One Player
                            if (get_last_scene() == 1) {
                                set_current_scene(1);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                reset_game_seed();
                                handle_event = &one_player_handler;
                            }
                            // Two Players
                            else if (get_last_scene() == 3) {
                                set_current_scene(3);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                p_tetris_board[1].m_game_start = false;
                                reset_game_seed();
                                handle_event = &two_player_handler;
                            }

                        break;

                        // Return to Main Menu
                        case 2:
                            // One Player
                            if (get_last_scene() == 1) {
                                set_current_scene(0);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                reset_game_seed();
                                handle_event = &main_menu_handler;
                            }
                            // Two Players
                            else if (get_last_scene() == 3) {
                                set_current_scene(0);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                p_tetris_board[1].m_game_start = false;
                                reset_game_seed();
                                handle_event = &main_menu_handler;
                            }
                        break;
                    }
                break;
            }
        break;
    }
}

void update_event(TetrisBoard p_tetris_board[2], bool *p_is_running) {
    SDL_Event current_event;
    is_running = true;

    while (SDL_PollEvent(&current_event) != 0) {

        // Handles all events
        handle_event(p_tetris_board, &current_event);

        // Handles things like ALT + F4
        switch (current_event.type) {
            case SDL_QUIT:
                is_running = false;
            break;
        }

        *p_is_running = is_running;
    }
}

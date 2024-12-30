#include "TetrisHandler.h"
#include "TetrisLogic.h"
#include "TetrisPauseScene.h"
#include "TetrisStartScreen.h"
#include "TetrisTime.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>

extern bool g_game_start;

void update_event(TetrisBoard p_tetris_board[2], bool *p_is_running) {
    SDL_Event current_event;
    while (SDL_PollEvent(&current_event) != 0) {
        switch (current_event.type) {
            case SDL_QUIT:
                *p_is_running = false;
                break;

            case SDL_KEYDOWN:
                switch (current_event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            pause_tetris_counter(&p_tetris_board[0].m_counter);
                            set_current_scene(2);
                        }

                        // Two Players Scene
                        else if (get_current_scene() == 3) {
                            pause_tetris_counter(&p_tetris_board[0].m_counter);
                            pause_tetris_counter(&p_tetris_board[1].m_counter);
                            set_current_scene(2);
                        }

                        // In Pause Scene
                        else if (get_current_scene() == 2) {
                            // One Player Scene
                            if (get_last_scene() == 1) { 
                                set_current_scene(1);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                            }
                            // Two Players Scene
                            else if (get_last_scene() == 3) {
                                set_current_scene(3);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                            }
                        }
                    break;

                    case SDLK_LEFT:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            move_left(&p_tetris_board[0]);
                        }
                        // Two Players Scene
                        else if (get_current_scene() == 3) {
                            move_left(&p_tetris_board[1]);
                        }
                    break;

                    case SDLK_a: 
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            move_left(&p_tetris_board[0]);
                        }
                        // Two Players Scene
                        else if (get_current_scene() == 3) {
                            move_left(&p_tetris_board[0]);
                        }
                        // In Start Scene
                        else if (get_current_scene() == 0) {
                            decrease_button_selection();
                        }
                        // In Pause Scene
                        else if (get_current_scene() == 2) {
                            decrease_pause_button_selection();
                        }
                        break;

                    case SDLK_RIGHT:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            move_right(&p_tetris_board[0]);
                        }
                        // Two Players Scene
                        if (get_current_scene() == 3) {
                            move_right(&p_tetris_board[1]);
                        }
                    break;

                    case SDLK_d:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            move_right(&p_tetris_board[0]);
                        }
                        // Two Players Scene
                        else if (get_current_scene() == 3) {
                            move_right(&p_tetris_board[0]);
                        }
                        // In Start Scene
                        else if (get_current_scene() == 0) {
                            increase_button_selection();
                        }
                        // In Pause Scene
                        else if (get_current_scene() == 2) {
                            increase_pause_button_selection();
                        }
                        break;

                    case SDLK_UP:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            rotate_piece_clockwise(&p_tetris_board[0]);
                        }
                        // Two Players Scene
                        if (get_current_scene() == 3) {
                            rotate_piece_clockwise(&p_tetris_board[1]);
                        }
                        break;

                    case SDLK_x:
                    case SDLK_w:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            rotate_piece_clockwise(&p_tetris_board[0]);
                        }
                        // Two Players Scene
                        if (get_current_scene() == 3) {
                            rotate_piece_clockwise(&p_tetris_board[0]);
                        }
                        break;

                    case SDLK_DOWN:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            accelerate_piece(&p_tetris_board[0].m_counter);
                        }
                        // Two Players Scene
                        if (get_current_scene() == 3) {
                            accelerate_piece(&p_tetris_board[1].m_counter);
                        }
                        break;
                    case SDLK_s:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            accelerate_piece(&p_tetris_board[0].m_counter);
                        }
                        // Two Players Scene
                        if (get_current_scene() == 3) {
                            accelerate_piece(&p_tetris_board[0].m_counter);
                        }
                        break;

                    case SDLK_RETURN:
                        // In Start Scene
                        if (get_current_scene() == 0) {
                            switch (get_button_selection()) {
                                case 0:
                                    set_current_scene(1);
                                break;
                                case 1:
                                    set_current_scene(3);
                                break;
                                case 2:
                                    printf("CLOSE GAME\n");
                                    *p_is_running = false;
                                break;
                            }
                        }

                        // In Pause Scene
                        else if (get_current_scene() == 2) {
                            switch (get_pause_button_selection()) {
                                case 0:
                                    // One Player
                                    if (get_last_scene() == 1) {
                                        set_current_scene(1);
                                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                    }
                                    // Two Players
                                    else if (get_last_scene() == 3) {
                                        set_current_scene(3);
                                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                        unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                    }
                                break;
                                case 1:
                                    // One Player
                                    if (get_last_scene() == 1) {
                                        set_current_scene(1);
                                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                        p_tetris_board[0].m_game_start = false;
                                    }
                                    // Two Players
                                    else if (get_last_scene() == 3) {
                                        set_current_scene(3);
                                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                        unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                        p_tetris_board[0].m_game_start = false;
                                        p_tetris_board[1].m_game_start = false;
                                    }

                                break;
                                case 2:
                                    // One Player
                                    if (get_last_scene() == 1) {
                                        set_current_scene(0);
                                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                        p_tetris_board[0].m_game_start = false;
                                    }
                                    // Two Players
                                    else if (get_last_scene() == 3) {
                                        set_current_scene(0);
                                        unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                        unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                        p_tetris_board[0].m_game_start = false;
                                        p_tetris_board[1].m_game_start = false;
                                    }
                                break;
                            }
                        }
                }
            break;

            case SDL_KEYUP:
                switch (current_event.key.keysym.sym) {
                    case SDLK_DOWN:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            reset_piece_acceleration(&p_tetris_board[0].m_counter);
                        }
                        // Two Players Scene
                        if (get_current_scene() == 3) {
                            reset_piece_acceleration(&p_tetris_board[1].m_counter);
                        }
                        break;

                    case SDLK_s:
                        // One Player Scene
                        if (get_current_scene() == 1) {
                            reset_piece_acceleration(&p_tetris_board[0].m_counter);
                        }
                        // Two Players Scene
                        if (get_current_scene() == 3) {
                            reset_piece_acceleration(&p_tetris_board[0].m_counter);
                        }
                        break;
                }
            break;
        }
    }
}

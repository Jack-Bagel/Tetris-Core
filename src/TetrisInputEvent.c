#include "TetrisHandler.h"
#include "TetrisLogic.h"
#include "TetrisPauseScene.h"
#include "TetrisStartScreen.h"
#include "TetrisTime.h"
#include <SDL_events.h>
#include <SDL.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>

extern bool g_game_start;
Uint8 *keystate;

void update_event(bool *p_is_running) {
    SDL_Event current_event;
    while (SDL_PollEvent(&current_event) != 0) {
        switch (current_event.type) {
            case SDL_QUIT:
                *p_is_running = false;
                break;

            case SDL_KEYDOWN:
                switch (current_event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        // In Start Scene
                        if (get_current_scene() == 1) {
                            pause_tetris_counter();
                            set_current_scene(2);
                        }
                        // In Pause Scene
                        else if (get_current_scene() == 2) {
                            set_current_scene(1);
                            unpause_tetris_counter();
                        }
                    break;

                    case SDLK_LEFT:
                    case SDLK_a: 
                        // In Game Scene
                        if (get_current_scene() == 1) {
                            move_left();
                        }
                        // In Start Scene
                        if (get_current_scene() == 0) {
                            decrease_button_selection();
                        }
                        // In Pause Scene
                        else if (get_current_scene() == 2) {
                            decrease_pause_button_selection();
                        }
                        break;

                    case SDLK_RIGHT:
                    case SDLK_d:
                        // In Game Scene
                        if (get_current_scene() == 1) {
                            move_right();
                        }
                        // In Start Scene
                        if (get_current_scene() == 0) {
                            increase_button_selection();
                        }
                        // In Pause Scene
                        else if (get_current_scene() == 2) {
                            increase_pause_button_selection();
                        }
                        break;

                    case SDLK_UP:
                    case SDLK_x:
                    case SDLK_w:
                        // In Game Scene
                        if (get_current_scene() == 1) {
                            rotate_piece_clockwise();
                        }
                        break;

                    case SDLK_DOWN:
                    case SDLK_s:
                        // In Game Scene
                        if (get_current_scene() == 1) {
                            accelerate_piece();
                        }
                        break;

                    case SDLK_RETURN:
                        // In Start Scene
                        if (get_current_scene() == 0) {
                            switch (get_button_selection()) {
                                case 0:
                                    set_current_scene(1);
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
                                    set_current_scene(1);
                                    unpause_tetris_counter();
                                break;
                                case 1:
                                    set_current_scene(1);
                                    unpause_tetris_counter();
                                    g_game_start = false;
                                break;
                                case 2:
                                    set_current_scene(0);
                                    unpause_tetris_counter();
                                    g_game_start = false;
                                break;
                            }
                        }
                }
            break;

            case SDL_KEYUP:
                switch (current_event.key.keysym.sym) {
                    case SDLK_DOWN:
                    case SDLK_s:
                        // In Game Scene
                        if (get_current_scene() == 1) {
                            reset_piece_acceleration();
                        }
                        break;
                }
            break;
        }
    }
}

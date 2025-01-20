#include "Button.h"
#include "GameOverScene.h"
#include <SDL2/SDL_mixer.h>
#include "EventListener.h"
#include "ResourceRegistry.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"
#include "TetrisUtils.h"
#include <SDL2/SDL_ttf.h>

extern bool is_running;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);

static Button restart_button = {.x = 500, .y = 250, .text = "Restart"};
static Button menu_button = {.x = 700, .y = 250, .text = "Menu"};
static SDL_Color text_color = {255, 255, 255};
static unsigned int button_selection = 0;

//Forward Declaration
static void update_game_over(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]);
static void render_game_over(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

void init_game_over(GameOverScene *scene) {
    scene->update = &update_game_over;
}

static void update_game_over(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]) {
    render_game_over(p_window, p_renderer, viewport, player_board);
    handle_event = &events; // Shouldn't run every frames
}

static void render_game_over(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport, TetrisBoard player_board[2]) {
    SDL_Texture *background;
    if (get_last_scene() == ONE_PLAYER) {
        background = resource_instance()->s_game_over_bkg;
    }
    else {
        background = resource_instance()->s_two_player_game_over_bkg;
    }

    clear_screen(p_renderer);
    render_background(background, p_window, p_renderer, viewport);
    Button buttons[2] = {restart_button, menu_button};

    // Render Stats
    if (get_last_scene() == ONE_PLAYER) {
        render_top_score(&player_board[0], p_window, p_renderer, viewport, 270, 390);
        render_score(&player_board[0], p_window, p_renderer, viewport, 330, 485);
        render_level(&player_board[0], p_window, p_renderer, viewport, 326, 585);
        render_lines(&player_board[0], p_window, p_renderer, viewport, 323, 675);
    }
    else {
        render_score(&player_board[0], p_window, p_renderer, viewport, 290, 510);
        render_level(&player_board[0], p_window, p_renderer, viewport, 290, 605);
        render_lines(&player_board[0], p_window, p_renderer, viewport, 285, 688);
        render_score(&player_board[1], p_window, p_renderer, viewport, 720, 510);
        render_level(&player_board[1], p_window, p_renderer, viewport, 720, 605);
        render_lines(&player_board[1], p_window, p_renderer, viewport, 710, 688);
    }

    // Render Buttons
    for (int i=0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        SDL_Surface* surface_message = TTF_RenderText_Solid(resource_instance()->s_font, buttons[i].text, text_color);
        SDL_Texture* texture_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
        int tex_w = surface_message->w;
        int tex_h = surface_message->h;

        // Makes the selected button green
        if (button_selection == i) {
            SDL_SetTextureColorMod(texture_message, 0, 220, 30);
        }

        const SDL_Rect one_player_rect = {.x = buttons[i].x, .y = buttons[i].y, .w = tex_w, .h = tex_h};
        SDL_RenderCopy(p_renderer, texture_message, NULL, &one_player_rect);

        SDL_FreeSurface(surface_message);
        SDL_DestroyTexture(texture_message);
    }

    // Render All
    SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderPresent(p_renderer);
}

static void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {

            case SDLK_LEFT:
            case SDLK_a:
                decrease_button_selection(&button_selection, 2);
                Mix_PlayChannel( -1, resource_instance()->s_next_button_sound, 0);
            break;

            case SDLK_RIGHT:
            case SDLK_d:
                increase_button_selection(&button_selection, 2);
                Mix_PlayChannel( -1, resource_instance()->s_next_button_sound, 0);
            break;

            case SDLK_RETURN:
                    call_event(NULL, CLICK_BUTTON_EVENT);

                    switch (button_selection) {
                        // Reset Game
                        case 0:
                            // One Player
                            if (get_last_scene() == ONE_PLAYER) {
                                set_current_scene(ONE_PLAYER);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                reset_game_seed();
                                pub_game_restart_event(NULL);
                            }

                            // Two Player
                            else if (get_last_scene() == TWO_PLAYER) {
                                set_current_scene(TWO_PLAYER);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                p_tetris_board[1].m_game_start = false;
                                reset_game_seed();
                                pub_game_restart_event(NULL);
                            }
                        break;

                        // Return to Main Menu
                        case 1:
                            // One Player
                            if (get_last_scene() == ONE_PLAYER) {
                                set_current_scene(MAIN_MENU);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                reset_game_seed();
                                pub_game_restart_event(NULL);
                            }

                            // Two Player
                            else if (get_last_scene() == TWO_PLAYER) {
                                set_current_scene(MAIN_MENU);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                p_tetris_board[1].m_game_start = false;
                                reset_game_seed();
                                pub_game_restart_event(NULL);
                            }
                        break;
                    }
        }

        break;
    }
}


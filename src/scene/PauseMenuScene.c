#include "Button.h"
#include "PauseMenuScene.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"
#include "TetrisUtils.h"
#include <SDL2/SDL_ttf.h>

extern TTF_Font *g_font;
extern SDL_Texture *g_pause_menu_bkg;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);
extern bool is_running;

static Button continue_game = {.x = 290, .y = 470, .text = "Continue"};
static Button restart_game = {.x = 530, .y = 470, .text = "Restart"};
static Button return_menu = {.x = 760, .y = 470, .text = "Menu"};
static SDL_Color text_color = {255, 255, 255};
static unsigned int button_selection = 0;


void init_pause_menu(MenuScene *scene) {
    scene->update = &update_menu;
}

void update_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    render_menu(p_window, p_renderer, viewport);
    handle_event = &events; // Shouldn't run every loop
}

void render_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    render_pause_background(p_window, p_renderer, viewport);

    Button buttons[3] = {continue_game, restart_game, return_menu};

    for (int i=0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        SDL_Surface* surface_message = TTF_RenderText_Solid(g_font, buttons[i].text, text_color); 
        SDL_Texture* texture_message = SDL_CreateTextureFromSurface(p_renderer, surface_message);
        int tex_w = surface_message->w;
        int tex_h = surface_message->h;

        // Makes the selected button green
        if (button_selection == i) {
            SDL_SetTextureColorMod(texture_message, 0, 220, 30);
        }

        const SDL_Rect button_rect = {.x = buttons[i].x, .y = buttons[i].y, .w = tex_w, .h = tex_h};
        SDL_RenderCopy(p_renderer, texture_message, NULL, &button_rect);

        SDL_FreeSurface(surface_message);
        SDL_DestroyTexture(texture_message);
    }

    // SDL_RenderSetViewport(p_renderer, &viewport);
    SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderPresent(p_renderer);
}

void render_pause_background(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    // SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    // SDL_RenderClear(p_renderer);
    const SDL_Rect background = {.x = (viewport.w / 4), .y = viewport.h / 2, .w = 600, .h = 86};
    // SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderCopy(p_renderer, g_pause_menu_bkg, NULL, &background);
}

void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {
        switch (event->type) {
            case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {

                case SDLK_ESCAPE:
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
                break;

                case SDLK_LEFT:
                case SDLK_a:
                    decrease_button_selection();
                break;

                case SDLK_RIGHT:
                case SDLK_d:
                    increase_button_selection();
                break;

                case SDLK_RETURN:
                    switch (button_selection) {
                        // Continue Game
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

                        // Reset Game
                        case 1:
                            // One Player
                            if (get_last_scene() == 1) {
                                set_current_scene(1);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                reset_game_seed();
                            }
                            // Two Players
                            else if (get_last_scene() == 3) {
                                set_current_scene(3);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                p_tetris_board[1].m_game_start = false;
                                reset_game_seed();
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
                            }
                            // Two Players
                            else if (get_last_scene() == 3) {
                                set_current_scene(0);
                                unpause_tetris_counter(&p_tetris_board[0].m_counter);
                                unpause_tetris_counter(&p_tetris_board[1].m_counter);
                                p_tetris_board[0].m_game_start = false;
                                p_tetris_board[1].m_game_start = false;
                                reset_game_seed();
                            }
                        break;
                    }
                break;
            }
        break;
    }
}

void increase_button_selection() {
    if (button_selection == 2) {
        button_selection = 0;
    }

    else {
        button_selection++;
    }
}
void decrease_button_selection() {
    if (button_selection == 0) {
        button_selection = 2;
    }

    else {
        button_selection--;
    }
}

#include "Button.h"
#include "MainMenuScene.h"
#include "EventListener.h"
#include "ResourceRegistry.h"
#include "SceneHandler.h"
#include "TetrisLogic.h"
#include "TetrisRenderer.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

extern bool is_running;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);


static Button one_player = {.x = 150, .y = 600, .text = "One Player"};
static Button two_players = {.x = 370, .y = 600, .text = "Two Players"};
static Button quit_game = {.x = 250, .y = 650, .text = "Quit Tetris"};
static SDL_Color text_color = {255, 255, 255};
static unsigned int button_selection = 0;

//Forward Declaration
static void update_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void render_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport);
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event);

void init_main_menu(MenuScene *scene) {
    scene->update = &update_menu;
}

// I dont like this
void init_event_handler() {
    handle_event = &events;
}

static void update_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    render_menu(p_window, p_renderer, viewport);
    handle_event = &events; // Shouldn't run every frames
}

static void render_menu(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    clear_screen(p_renderer);
    render_background(resource_instance()->s_start_menu_bkg, p_window, p_renderer, viewport);
    Button buttons[3] = {one_player, two_players, quit_game};

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

    SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderPresent(p_renderer);
}
static void events(TetrisBoard p_tetris_board[2], SDL_Event *event) {
    switch (event->type) {
        case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {

            case SDLK_LEFT:
            case SDLK_a:
                decrease_button_selection(&button_selection, 3);
            break;

            case SDLK_RIGHT:
            case SDLK_d:
                increase_button_selection(&button_selection, 3);
            break;

            case SDLK_RETURN:
                call_event(NULL, CLICK_BUTTON_EVENT);

                switch (button_selection) {
                    // Start One Player Game
                    case 0:
                        set_current_scene(ONE_PLAYER);
                    break;
                    // Start Two Player Game
                    case 1:
                        set_current_scene(TWO_PLAYER);
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

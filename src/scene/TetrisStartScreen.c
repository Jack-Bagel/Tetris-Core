#include "TetrisStartScreen.h"
#include "Button.h"
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string.h>

extern SDL_Texture *g_p_background;
extern TTF_Font *g_p_font;

void init_start_screen() {
    Button temp_one_player = {.x = 450, .y = 400, .text = "One Player"};
    one_player = temp_one_player;

    Button temp_two_players = {.x = 640, .y = 400, .text = "Two Players"};
    two_players = temp_two_players;

    Button temp_quit = {.x = 850, .y = 400, .text = "Quit Tetris"};
    quit_game = temp_quit;

    text_color.r = 255; text_color.g = 255; text_color.b = 255;
    button_selection = 0;

}

void increase_button_selection() {
    if (button_selection == 3) {
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

u_int get_button_selection() {
    return button_selection;
}

void render_background(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    SDL_RenderClear(p_renderer);
    const SDL_Rect background = {.x = 0, .y = 0, .w = viewport.w, .h = viewport.h};
    // SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderCopy(p_renderer, g_p_background, NULL, &background);
}

void render_buttons(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    Button buttons[3] = {one_player, two_players, quit_game};

    for (int i=0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        SDL_Surface* surface_message = 
        TTF_RenderText_Solid(g_p_font, buttons[i].text, text_color); 
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

    // SDL_RenderSetViewport(p_renderer, &viewport);
    SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderPresent(p_renderer);
}

#include "TetrisPauseScene.h"

extern SDL_Texture *g_p_background;

void init_pause_screen() {
    Button temp_continue = {.x = 450, .y = 400, .text = "Continue"};
    m_continue = temp_continue;

    Button temp_restart = {.x = 650, .y = 400, .text = "Restart"};
    m_restart = temp_restart;

    Button temp_return = {.x = 850, .y = 400, .text = "Return to Menu"};
    m_return_to_start = temp_return;

    font = TTF_OpenFont("../resources/fonts/Minecraft.ttf", 25);
    text_color.r = 255; text_color.g = 255; text_color.b = 255;
    button_selection = 0;

    if (font == NULL) {
        printf("Error: Could not load font\n");
    }
}

void increase_pause_button_selection() {
    if (button_selection == 3) {
        button_selection = 0;
    }

    else {
        button_selection++;
    }
}
void decrease_pause_button_selection() {
    if (button_selection == 0) {
        button_selection = 2;
    }

    else {
        button_selection--;
    }
}

u_int get_pause_button_selection() {
    return button_selection;
}


void render_pause_background(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    // SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 0);
    // SDL_RenderClear(p_renderer);
    const SDL_Rect background = {.x = 390, .y = 200, .w = viewport.w / 2, .h = viewport.h / 2};
    // SDL_RenderSetLogicalSize(p_renderer, viewport.w, viewport.h);
    SDL_RenderCopy(p_renderer, g_p_background, NULL, &background);
}

void render_pause_buttons(SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {
    Button buttons[3] = {m_continue, m_restart, m_return_to_start};

    for (int i=0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
        SDL_Surface* surface_message = TTF_RenderText_Solid(font, buttons[i].text, text_color); 
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



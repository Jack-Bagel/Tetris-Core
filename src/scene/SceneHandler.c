#include "SceneHandler.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "PauseMenuScene.h"
#include "OnePlayerScene.h"
#include "TwoPlayerScene.h"
#include "MenuScene.h"
#include "PlayableScene.h"
#include "TetrisLogic.h"
#include <SDL_rect.h>
#include <stdbool.h>

extern SDL_Texture *g_one_player_bkg;
extern SDL_Texture *g_two_player_bkg;
extern SDL_Texture *g_two_player_bkg;
extern SDL_Texture *g_start_menu_bkg;
extern void (*handle_event)(TetrisBoard[2], SDL_Event *);

static MenuScene main_menu;
static MenuScene pause_menu;
static GameOverScene game_over_scene;
static PlayableScene one_player_scene;
static PlayableScene two_player_scene;

void init_scene() {
    s_current_scene = 0;
    s_last_scene = 0;
    init_main_menu(&main_menu);
    init_pause_menu(&pause_menu);
    init_one_player(&one_player_scene);
    init_two_player(&two_player_scene);
    init_game_over(&game_over_scene);
    init_event_handler();
}

void set_current_scene(unsigned int scene) {
    s_last_scene = s_current_scene;
    s_current_scene = scene;
}

unsigned int get_current_scene() {
    return s_current_scene;
}

unsigned int get_last_scene() {
    return s_last_scene;
}

void update_game(TetrisBoard players_board[2], SDL_Window *p_window, SDL_Renderer *p_renderer, const SDL_Rect viewport) {

    if (s_current_scene == MAIN_MENU) {
        main_menu.update(p_window, p_renderer, viewport);
    }

    else if (s_current_scene == PAUSE_MENU) {
        pause_menu.update(p_window, p_renderer, viewport);
    }

    else if (s_current_scene == GAME_OVER) {
        game_over_scene.update(p_window, p_renderer, viewport, players_board);
    }

    else if (s_current_scene == ONE_PLAYER) {
        one_player_scene.update(p_window, p_renderer, viewport, players_board);
    }

    else if (s_current_scene == TWO_PLAYER) {
        two_player_scene.update(p_window, p_renderer, viewport, players_board);
    }
}

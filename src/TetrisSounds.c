#include "EventListener.h"
#include "ResourceRegistry.h"
#include <SDL2/SDL_mixer.h>

static void on_collision_event(void* data);
static void on_button_selection_event(void* event_data);
static void on_button_click_event(void* event_data);
static void on_clear_line_event(void* line_clear);
static void on_move_event(void* event_data);
static void on_rotate_event(void* event_data);

static EventListener collision_event = {.callback = &on_collision_event, .type = COLLISION_EVENT};
static EventListener select_event = {.callback = &on_button_selection_event, .type = SELECT_BUTTON_EVENT};
static EventListener line_event = {.callback = &on_clear_line_event, .type = CLEAR_LINE_EVENT};
static EventListener move_event = {.callback = &on_move_event, .type = MOVE_PIECE_EVENT};
static EventListener rotate_event = {.callback = &on_rotate_event, .type = ROTATE_PIECE_EVENT};
static EventListener click_event = {.callback = &on_button_click_event, .type = CLICK_BUTTON_EVENT};

void register_sound_listeners() {
    register_event(&collision_event);
    register_event(&select_event);
    register_event(&line_event);
    register_event(&move_event);
    register_event(&rotate_event);
    register_event(&click_event);
}

void init_music() {

    if ( Mix_PlayMusic(resource_instance()->s_tetris_theme_music, -1) != 0 ) {
        printf("Failed to play music: %s\n", Mix_GetError());
    }

    Mix_VolumeMusic(15);
    Mix_Volume(-1, 12);
}

static void on_collision_event(void* event_data) {
    // Play sound
    Mix_PlayChannel(-1, resource_instance()->s_touch_ground_sound, 0);
}

static void on_button_selection_event(void* event_data) {
    Mix_PlayChannel(-1, resource_instance()->s_next_button_sound, 0);
}

static void on_button_click_event(void* event_data) {
    Mix_PlayChannel( -1, resource_instance()->s_click_button_sound, 0);
}

static void on_clear_line_event(void* event_data) {
    int line_cleared = *(int*)event_data == 4;

    if (line_cleared == 4) {
        Mix_PlayChannel( -1, resource_instance()->s_four_lines_clear_sound, 0);
    }
    else {
        Mix_PlayChannel( -1, resource_instance()->s_line_clear_sound, 0);
    }
}

static void on_move_event(void* event_data) {
    Mix_PlayChannel( -1, resource_instance()->s_movement_sound, 0);
}

static void on_rotate_event(void* event_data) {
    Mix_PlayChannel( -1, resource_instance()->s_rotate_sound, 0);
}

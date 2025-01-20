#pragma once

typedef enum EventType {
    COLLISION_EVENT,
    SELECT_BUTTON_EVENT,
    CLICK_BUTTON_EVENT,
    CLEAR_LINE_EVENT,
    MOVE_PIECE_EVENT,
    ROTATE_PIECE_EVENT,
    GAME_OVER_EVENT,
    GAME_RESTART_EVENT,
    NEW_PIECE_EVENT
} EventType;

typedef struct EventListener {
    void (*callback)(void*);
    EventType type;

} EventListener;

extern void sub_event_listener(EventListener* callback);
extern void init_listeners();
extern void call_event(void* data, EventType type);
extern void pub_game_over_event(void* data);
extern void pub_game_restart_event(void* data);
extern void pub_new_piece_event(void* data);

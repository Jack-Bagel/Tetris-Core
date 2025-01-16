#pragma once

typedef enum EventType {
    COLLISION_EVENT,
    SELECT_BUTTON_EVENT,
    CLICK_BUTTON_EVENT,
    CLEAR_LINE_EVENT,
    MOVE_PIECE_EVENT,
    ROTATE_PIECE_EVENT
} EventType;

typedef struct EventListener {
    void (*callback)(void*);
    EventType type;

} EventListener;

extern void register_event(EventListener* callback);
extern void init_listeners();
extern void call_event(void* data, EventType type);

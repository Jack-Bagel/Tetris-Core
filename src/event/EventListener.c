#include <string.h>
#include "EventListener.h"
#include "OnePlayerScene.h"
#include "TetrisIO.h"
#include "TetrisSounds.h"
#include <stdio.h>
#define MAX_EVENTS 10

static EventListener *event_listeners[MAX_EVENTS] = {NULL};
static EventListener *game_over_listeners[MAX_EVENTS] = {NULL};
static EventListener *new_piece_listeners[MAX_EVENTS] = {NULL};
static EventListener *game_restart_listeners[MAX_EVENTS] = {NULL};

void sub_event_listener(EventListener* listener) {
    int i = 0;
    while (event_listeners[i] != NULL) {

        if (i == 10) {
            printf("Listener could not be added to the event array\n");
            return;
        }

        i++;
    }

    // Make a push function
    switch (listener->type) {
        case GAME_OVER_EVENT:
            game_over_listeners[0] = listener;
        break;

        case NEW_PIECE_EVENT:
            new_piece_listeners[0] = listener;
        break;

        case GAME_RESTART_EVENT:
            game_restart_listeners[0] = listener;
        break;

        default:
            event_listeners[i] = listener;
    }

}

void init_listeners() {
    register_sound_listeners();
    register_IO_listeners();
    register_one_player_listeners();
}

void call_event(void* data, EventType type) {
    for (int i = 0; i < MAX_EVENTS; i++) {

        if (event_listeners[i] == NULL) {
            return;
        }

        if (event_listeners[i]->type == type) {
            event_listeners[i]->callback(data);
        }
    }
}

void pub_game_over_event(void* data) {
    for (int i = 0; i < MAX_EVENTS; i++) {

        if (game_over_listeners[i] == NULL) {
            return;
        }

        game_over_listeners[i]->callback(data);
    }
}


void pub_new_piece_event(void* data) {
    for (int i = 0; i < MAX_EVENTS; i++) {

        if (new_piece_listeners[i] == NULL) {
            return;
        }

        new_piece_listeners[i]->callback(data);
    }
}

void pub_game_restart_event(void* data) {
    for (int i = 0; i < MAX_EVENTS; i++) {

        if (game_restart_listeners[i] == NULL) {
            return;
        }

        printf("I RUN");

        game_restart_listeners[i]->callback(data);
    }
}

#include <string.h>
#include "EventListener.h"
#include "TetrisSounds.h"
#include <stdio.h>
#define MAX_EVENTS 10

static EventListener *event_listeners[MAX_EVENTS] = {NULL};

void register_event(EventListener* listener) {
    int i = 0;
    while (event_listeners[i] != NULL) {

        if (i == 10) {
            printf("Listener could not be added to the event array\n");
            return;
        }

        i++;
    }

    event_listeners[i] = listener;
}

void init_listeners() {
    register_sound_listeners();
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

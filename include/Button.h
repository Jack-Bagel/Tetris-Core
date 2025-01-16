#pragma once
#include "EventListener.h"
#include <string.h>
typedef struct Button {
    int x, y;
    char text[50];
    void (*on_press)();
} Button;

extern void *start_one_player();


static inline void increase_button_selection(unsigned int *p_button_selection, unsigned int max_button) {
    if (*p_button_selection == max_button - 1) {
        *p_button_selection = 0;
    }

    else {
        *p_button_selection += 1;
    }
    
    call_event(NULL, SELECT_BUTTON_EVENT);
}

static inline void decrease_button_selection(unsigned int *p_button_selection, unsigned int max_button) {
    if (*p_button_selection == 0) {
        *p_button_selection = max_button - 1;
    }

    else {
        *p_button_selection -= 1;
    }

    call_event(NULL, SELECT_BUTTON_EVENT);
}

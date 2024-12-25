#include "TetrisTime.h"
#include <SDL_timer.h>
#include <stdio.h>

#define TICK_INTERVAL 200
void init_tetris_time() {
    counter = 0;
    time_since_reset = 0;
}

int get_tetris_counter() {
    counter = (SDL_GetTicks() / TICK_INTERVAL) - (time_since_reset / TICK_INTERVAL);
    // printf("Counter value: %i\n", counter);
    return counter;
}

void reset_tetris_counter() {
    time_since_reset = SDL_GetTicks();
}

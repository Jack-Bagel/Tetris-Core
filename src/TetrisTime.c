#include "TetrisTime.h"
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <sys/types.h>

#define ACCELERATION 6

void init_tetris_time(TetrisCounter *self) {
    self->m_counter = 0;
    self->m_time_since_reset = 0;
    self->m_normal_tick_interval = 200;
    self->m_last_update_time = 0;
    self->m_accelerated_tick_interval = self->m_normal_tick_interval / ACCELERATION;
    self->m_tick_interval = self->m_normal_tick_interval;
    self->m_paused_time = 0;
    self->m_start_paused_time = 0;
    self->m_is_paused = false;
    self->m_pressed_down = false;
}

int get_tetris_counter(TetrisCounter *self) {
        unsigned int current_time = SDL_GetTicks();
        unsigned int elapsed_time = current_time - self->m_last_update_time;

        if (elapsed_time >= self->m_tick_interval && !self->m_is_paused) {
            self->m_counter++;
            self->m_last_update_time = current_time;
        }

    return self->m_counter;
}

void accelerate_piece(TetrisCounter *self) {
    if (!self->m_pressed_down) {
        self->m_tick_interval = self->m_accelerated_tick_interval;
        self->m_pressed_down = true;
    }
}

void reset_piece_acceleration(TetrisCounter *self) {
    self->m_tick_interval = self->m_normal_tick_interval;
    self->m_pressed_down = false;
}

void reset_tetris_counter(TetrisCounter *self) {
    self->m_counter = 0;
    self->m_time_since_reset = SDL_GetTicks();
    self->m_last_update_time = self->m_time_since_reset;
    self->m_tick_interval = self->m_normal_tick_interval;
    self->m_start_paused_time = 0;
    self->m_paused_time = 0;
}

void pause_tetris_counter(TetrisCounter *self) {
    self->m_is_paused = true;
    self->m_start_paused_time = SDL_GetTicks();
}

void unpause_tetris_counter(TetrisCounter *self) {
    if (self->m_is_paused) {
        self->m_is_paused = false;
        unsigned int pause_end_time = SDL_GetTicks();
        self->m_last_update_time += (pause_end_time - self->m_start_paused_time);
        printf("PAUSED: %f\n", self->m_paused_time / 1000.0);
    }
}

void update_tick_interval(TetrisCounter *self, int ticks) {
    self->m_normal_tick_interval -= ticks;
    self->m_accelerated_tick_interval = self->m_normal_tick_interval / ACCELERATION;
}

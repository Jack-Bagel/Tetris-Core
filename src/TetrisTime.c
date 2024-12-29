#include "TetrisTime.h"
#include "TetrisHandler.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <sys/types.h>

#define ACCELERATION 6

void init_tetris_time() {
    m_counter = 0;
    m_time_since_reset = 0;
    m_normal_tick_interval = 200;
    m_last_update_time = 0;
    m_accelerated_tick_interval = m_normal_tick_interval / ACCELERATION;
    m_tick_interval = m_normal_tick_interval;
    m_paused_time = 0;
    m_start_paused_time = 0;
    m_is_paused = false;
    m_pressed_down = false;
}

int get_tetris_counter() {
        u_int current_time = SDL_GetTicks();
        u_int elapsed_time = current_time - m_last_update_time;

        if (elapsed_time >= m_tick_interval && !m_is_paused) {
            m_counter++;
            m_last_update_time = current_time;
        }

    return m_counter;
}

void accelerate_piece() {
    if (!m_pressed_down) {
        m_tick_interval = m_accelerated_tick_interval;
        m_pressed_down = true;
    }
}

void reset_piece_acceleration() {
    m_tick_interval = m_normal_tick_interval;
    m_pressed_down = false;
}

void reset_tetris_counter() {
    m_counter = 0;
    m_time_since_reset = SDL_GetTicks();
    m_last_update_time = m_time_since_reset;
    m_tick_interval = m_normal_tick_interval;
    m_start_paused_time = 0;
    m_paused_time = 0;
}

void pause_tetris_counter() {
    m_is_paused = true;
    m_start_paused_time = SDL_GetTicks();
}

void unpause_tetris_counter() {
    if (m_is_paused) {
        m_is_paused = false;
        u_int pause_end_time = SDL_GetTicks();
        m_last_update_time += (pause_end_time - m_start_paused_time);
        printf("PAUSED: %f\n", m_paused_time / 1000.0);
    }
}

void update_tick_interval(int ticks) {
    m_normal_tick_interval -= ticks;
    m_accelerated_tick_interval = m_normal_tick_interval / ACCELERATION;
}

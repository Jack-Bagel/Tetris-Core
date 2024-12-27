#include "TetrisTime.h"
#include <SDL_stdinc.h>
#include <SDL_timer.h>


void init_tetris_time() {
    m_counter = 0;
    m_time_since_reset = 0;
    m_normal_tick_interval = 200;
    m_accelerated_tick_interval = m_normal_tick_interval / 2;
    m_tick_interval = m_normal_tick_interval;
}

int get_tetris_counter() {
    u_int current_time = SDL_GetTicks();
    u_int elapsed_time = current_time - m_last_update_time;

    if (elapsed_time >= m_tick_interval) {
        m_counter++;
        m_last_update_time = current_time;
    }

    return m_counter;
}

void accelerate_piece() {
    m_tick_interval = m_accelerated_tick_interval;
}

void reset_piece_acceleration() {
    m_tick_interval = m_normal_tick_interval;
}

void reset_tetris_counter() {
    m_counter = 0;
    m_time_since_reset = SDL_GetTicks();
    m_last_update_time = m_time_since_reset;
    m_tick_interval = m_normal_tick_interval;
}

void update_tick_interval(int ticks) {
    m_normal_tick_interval -= ticks;
    m_accelerated_tick_interval = m_normal_tick_interval / 2;
}

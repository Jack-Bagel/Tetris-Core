#pragma once
#include <stdbool.h>

typedef struct TetrisCounter {

    int m_counter;
    int m_paused_time;
    int m_start_paused_time;
    int m_time_since_reset;
    int m_tick_interval;
    int m_last_update_time;
    int m_normal_tick_interval;
    int m_accelerated_tick_interval;
    bool m_is_paused;
    bool m_pressed_down;

} TetrisCounter;

extern void init_tetris_time(TetrisCounter *self);
extern void accelerate_piece(TetrisCounter *self);
extern void reset_piece_acceleration(TetrisCounter *self);
extern void reset_tetris_counter(TetrisCounter *self);
extern int get_tetris_counter(TetrisCounter *self);
extern void update_tick_interval(TetrisCounter *self, int ticks);
extern void pause_tetris_counter(TetrisCounter *self);
extern void unpause_tetris_counter(TetrisCounter *self);

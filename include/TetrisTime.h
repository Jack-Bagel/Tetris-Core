static int m_counter;
static int m_time_since_reset;
static int m_tick_interval;
static int m_last_update_time;
static int m_normal_tick_interval;
static int m_accelerated_tick_interval;

extern void accelerate_piece();
extern void reset_piece_acceleration();
extern void reset_tetris_counter();
extern int get_tetris_counter();
extern void init_tetris_time();
extern void update_tick_interval(int ticks);

#include "TetrisLogic.h"
#include "EventListener.h"
#include "TetrisUtils.h"
#include "TetrisIO.h"
#include "Pieces.h"
#include "TetrisTime.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


static unsigned int s_game_seed;

// Forward declaration
static bool init_tetris_board(TetrisBoard *self);
static void init_tetris_edges(TetrisBoard *self);

static void generate_new_piece(TetrisBoard *self);
static void make_piece_fall(TetrisBoard *self, int height_offset);
static bool piece_collides(TetrisGrid *p_last_tetris_grid, TetrisGrid *p_falling_piece_grid);
static void clear_lines(TetrisBoard *self);
static void clear_line(TetrisBoard *self, int line);
static void game_over(TetrisBoard *self);
static void update_level(TetrisBoard *self);
static void update_speed(TetrisBoard *self);
static void update_top_score(TetrisBoard *self);

// Merge these functions with their actions
static bool can_rotate_clockwise(TetrisBoard *self);
static bool can_rotate_counter_clockwise(TetrisBoard *self);
static bool can_move_left(TetrisBoard *self);
static bool can_move_right(TetrisBoard *self);


Piece get_next_piece(TetrisBoard *self) {
    return self->m_next_piece;
}

int get_points(TetrisBoard *self) {
    return self->m_points;
}

int get_top_score(TetrisBoard *self) {
    return self->m_top_score;
}

int get_level(TetrisBoard *self) {
    return self->m_current_level;
}

int get_total_lines(TetrisBoard *self) {
    return self->m_total_lines_cleared;
}

bool get_game_over(TetrisBoard *self) {
    return self->m_is_game_over;
}

static bool init_tetris_board(TetrisBoard *self) {

    // Init grids
    const int empty_grid[BOARD_HEIGHT][BOARD_WIDTH] = {0};
    memcpy(self->m_tetris_grid.grid, empty_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    init_tetris_edges(self);
    memcpy(self->m_last_tetris_grid.grid, self->m_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    memcpy(self->m_falling_piece_grid.grid, empty_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);

    // init member variables
    init_tetris_time(&self->m_counter);
    read_top_score(&self->m_top_score, SAVE_FILE);
    self->m_game_start = false;
    self->m_is_game_over = false;
    self->m_offset = 6;
    self->m_points = 0;
    self->m_lines_cleared = 0;
    self->m_total_lines_cleared = 0;
    self->m_current_level = 0;
    self->m_increment_seed = 0;

    return true; // If everything initialized properly (TODO: add a check)
}

static void init_tetris_edges(TetrisBoard *self) {

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        self->m_tetris_grid.grid[i][0] = GREY;
        self->m_tetris_grid.grid[i][1] = GREY;
        self->m_tetris_grid.grid[i][BOARD_WIDTH - 1] = GREY;
        self->m_tetris_grid.grid[i][BOARD_WIDTH - 2] = GREY;
    }

    for (int j = 0; j < BOARD_WIDTH; j++) {
        self->m_tetris_grid.grid[BOARD_HEIGHT - 1][j] = GREY;
    }
}

/** GAME LOGIC **/
void tetris_loop(TetrisBoard *self) {

    if (!self->m_game_start) {

        if (!init_tetris_board(self)) {
            printf("Failed to initialize Tetris Scene\n");
        }
        
        self->m_seed = get_game_seed();
        reset_tetris_counter(&self->m_counter);
        generate_new_piece(self);
        self->m_game_start = true;
        printf("GAME STARTS\n");
    }

    if (!self->m_is_game_over) {
        make_piece_fall(self, 0);

        if (piece_collides(&self->m_last_tetris_grid, &self->m_falling_piece_grid)) {
            
            call_event(NULL, COLLISION_EVENT);

            // Place the block one step behind the collision
            make_piece_fall(self, -1);

            // update the last tetris grid
            AND_tetris_grid(&self->m_tetris_grid, &self->m_last_tetris_grid);
            combine_tetris_grids(&self->m_tetris_grid, &self->m_falling_piece_grid);

            // Clear the possible lines
            clear_lines(self);

            // Updates the top score
            update_top_score(self);

            // Update last tetris grid
            memcpy(self->m_last_tetris_grid.grid, self->m_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);

            // Check for game over
            game_over(self);

            // Move to the next block
            reset_tetris_counter(&self->m_counter);
            self->m_offset = 6; // Initial position of the falling block
            generate_new_piece(self);
            return;
        }

        // Clear screen for the falling piece
        AND_tetris_grid(&self->m_tetris_grid, &self->m_last_tetris_grid);

        // Render piece on the Tetris Grid
        combine_tetris_grids(&self->m_tetris_grid, &self->m_falling_piece_grid);
    }
}

static bool piece_collides(TetrisGrid *p_last_tetris_grid, TetrisGrid *p_falling_piece_grid) {
    
    // Piece touches ground
    for (int j = 0; j < BOARD_WIDTH; j++) {
        if (p_falling_piece_grid->grid[BOARD_HEIGHT - 1][j] != 0) {
            return true;
        } 
    }

    // Piece touches other piece
    TetrisGrid temp_grid = *p_last_tetris_grid;
    ADD_tetris_grid(&temp_grid, p_falling_piece_grid);
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (temp_grid.grid[i][j] != 0 && temp_grid.grid[i][j] % 2 == 0) {

                return true;
            }
        }
    }

    return false;
}

static void make_piece_fall(TetrisBoard *self, int height_offset) {
    int height = get_tetris_counter(&self->m_counter) + height_offset;
    TetrisGrid temp_grid = {.grid = {0}};
    clear_tetris_grid(&self->m_falling_piece_grid);

    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            temp_grid.grid[i][j] = self->m_piece.tetromino[i][j] * self->m_piece.color;
        }
    }

    int i = 0;
    while (i + height < BOARD_HEIGHT) {
        for (int j=0; j < 4; j++) {

            if (i + 1 + height >= BOARD_HEIGHT) {
                continue;
            }

            // Update the falling piece
            self->m_falling_piece_grid.grid[i + 1 + height][j + self->m_offset] = temp_grid.grid[i][j];
        }

        i++;
    }
}

static void game_over(TetrisBoard *self) {
    for (int j=2; j < BOARD_WIDTH - 2; j++) {
        if (self->m_last_tetris_grid.grid[2][j] != 0 && !self->m_is_game_over) {
            self->m_is_game_over = true;
            pub_game_over_event(&self->m_top_score);
            pub_game_restart_event(NULL);
        }
    }
}

static void clear_lines(TetrisBoard *self) {
    unsigned int line_count = 0;
    bool full_line = true;

    // Find every lines in the grid
    for (int i=2; i < BOARD_HEIGHT - 1; i++) {
        full_line = true;
        for (int j=2; j < BOARD_WIDTH - 2; j++) {
            if (self->m_tetris_grid.grid[i][j] == 0) {
                full_line = false;
                break;
            }
        }

        if (full_line) {
            line_count++;
            full_line = false;
            clear_line(self, i);
        }
    }

    // Calculate Points TODO: Should also win points when piece is placed
    if (line_count == 1) {
        self->m_points += 40 * (self->m_current_level + 1);
        self->m_lines_cleared += 1;
        self->m_total_lines_cleared += 1;
        call_event(&line_count, CLEAR_LINE_EVENT);
    }
    else if (line_count == 2) {
        self->m_points += 100 * (self->m_current_level + 1);
        self->m_lines_cleared += 2;
        self->m_total_lines_cleared += 2;
        call_event(&line_count, CLEAR_LINE_EVENT);
    }
    else if (line_count == 3) {
        self->m_points += 300 * (self->m_current_level + 1);
        self->m_lines_cleared += 3;
        self->m_total_lines_cleared += 3;
        call_event(&line_count, CLEAR_LINE_EVENT);
    }
    else if (line_count == 4) {
        self->m_points += 1200 * (self->m_current_level + 1);
        self->m_lines_cleared += 4;
        self->m_total_lines_cleared += 4;
        call_event(&line_count, CLEAR_LINE_EVENT);
    }

    if (line_count > 0) {
        update_level(self);
    }

}

static void clear_line(TetrisBoard *self, int line) {
    for (int j=2; j < BOARD_WIDTH - 2; j++) {
        self->m_tetris_grid.grid[line][j] = 0;
    }

    TetrisGrid temp_grid = self->m_tetris_grid;
    for (int i=2; i < line; i++) {
        for (int j=2; j < BOARD_WIDTH - 2; j++) {
            self->m_tetris_grid.grid[i + 1][j] = temp_grid.grid[i][j];
        }
    }
}

static void generate_new_piece(TetrisBoard *self) { 

    srand(self->m_seed + self->m_increment_seed);
    int random_piece = random_to_piece(rand() % 7 + 1);

    if (!self->m_game_start) {
        self->m_next_piece = create_piece(random_piece);
    }

    // Could be a reroll function
    self->m_increment_seed++;
    srand(self->m_seed + self->m_increment_seed);
    random_piece = random_to_piece(rand() % 7 + 1);

    self->m_piece = self->m_next_piece;
    self->m_next_piece = create_piece(random_piece);
    pub_new_piece_event(&self->m_piece);
    
    // If same piece twice, reroll
    if (self->m_next_piece.type == self->m_piece.type) {
        self->m_increment_seed++;
        srand(self->m_seed + self->m_increment_seed);
        random_piece = random_to_piece(rand() % 7 + 1);

        self->m_next_piece = create_piece(random_piece);
    }

    self->m_increment_seed++;
}

static void update_top_score(TetrisBoard *self) {
    if (self->m_top_score < self->m_points) {
        self->m_top_score = self->m_points;
    }
}

void reset_game_seed() {
    s_game_seed = time(NULL);
}

unsigned int get_game_seed() {
    return s_game_seed;
}


/** LEVELING AND SPEED **/
static void update_level(TetrisBoard *self) {
    if (self->m_current_level >= 0) {
        // if (m_lines_cleared >= (m_current_level * 10 + 10)) {
        if (self->m_lines_cleared >= 10) {
            self->m_current_level++;
            // m_lines_cleared = m_lines_cleared - ((m_current_level - 1) * 10 + 10);
            self->m_lines_cleared = self->m_lines_cleared - 10;

            update_speed(self);
        }
    }
}

static void update_speed(TetrisBoard *self) {
    if (self->m_current_level >= 0 && self->m_current_level <= 10) {
        update_tick_interval(&self->m_counter, 20);
    }

    else if (self->m_current_level == 13) {
        update_tick_interval(&self->m_counter,20);
    }

    else if (self->m_current_level == 16) {
        update_tick_interval(&self->m_counter,20);
    }

    else if (self->m_current_level == 19) {
        update_tick_interval(&self->m_counter,20);
    }

    else if (self->m_current_level == 29) {
        update_tick_interval(&self->m_counter,20);
    }
}

/** MOVEMENT **/

void rotate_piece_clockwise(TetrisBoard *self) {
    if (can_rotate_clockwise(self)) {
        rotate_clockwise(&self->m_piece);

        call_event(&self->m_piece, ROTATE_PIECE_EVENT);
    }
}

void rotate_piece_counter_clockwise(TetrisBoard *self) {
    if (can_rotate_counter_clockwise(self)) {
        rotate_counter_clockwise(&self->m_piece);

        call_event(&self->m_piece, ROTATE_PIECE_EVENT);
    }
}

void move_left(TetrisBoard *self) {
    if (can_move_left(self)) {
        self->m_offset--;

        call_event(&self->m_piece, MOVE_PIECE_EVENT);
    }
}
void move_right(TetrisBoard *self) {
    if (can_move_right(self)) {
        self->m_offset++;

        call_event(&self->m_piece, MOVE_PIECE_EVENT);
    }
}
// Move all the bool functions directly inside the movement functions
static bool can_move_left(TetrisBoard *self) {
    TetrisGrid temp_grid = {.grid = {0}};
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            temp_grid.grid[i][j - 1] |= self->m_falling_piece_grid.grid[i][j];
        }
    }

    if (piece_collides(&self->m_last_tetris_grid, &temp_grid)) {
        return false;
    }

    return true;
}
static bool can_move_right(TetrisBoard *self) {
    TetrisGrid temp_grid = {.grid = {0}};
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            temp_grid.grid[i][j + 1] |= self->m_falling_piece_grid.grid[i][j];
        }
    }

    if (piece_collides(&self->m_last_tetris_grid, &temp_grid)) {
        return false;
    }

    return true;
}


static bool can_rotate_clockwise(TetrisBoard *self) {
    TetrisGrid temp_grid = {.grid = {0}};
    TetrisGrid temp_falling_piece_grid = {.grid = {0}};
    Piece temp_piece = self->m_piece;
    rotate_clockwise(&temp_piece);
    int height = get_tetris_counter(&self->m_counter) + 0;
    // Wer simulate a piece with the rotation and check if it collides with something
    // Reusing make_piece_fall() logic.
    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            temp_grid.grid[i][j] = temp_piece.tetromino[i][j] * temp_piece.color;
        }
    }

    int i = 0;
    while (i + height < BOARD_HEIGHT) {
        for (int j=0; j < 4; j++) {

            if (i + 1 + height >= BOARD_HEIGHT) {
                continue;
            }

            // Update the falling piece
            temp_falling_piece_grid.grid[i + 1 + height][j + self->m_offset] = temp_grid.grid[i][j];
        }

        i++;
    }

    if (piece_collides(&self->m_last_tetris_grid, &temp_falling_piece_grid)) {
        return false;
    }

    return true;
}

static bool can_rotate_counter_clockwise(TetrisBoard *self) {
    TetrisGrid temp_grid = {.grid = {0}};
    TetrisGrid temp_falling_piece_grid = {.grid = {0}};
    Piece temp_piece = self->m_piece;
    rotate_counter_clockwise(&temp_piece);
    int height = get_tetris_counter(&self->m_counter) + 0;
    // Wer simulate a piece with the rotation and check if it collides with something
    // Reusing make_piece_fall() logic.
    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            temp_grid.grid[i][j] = temp_piece.tetromino[i][j] * temp_piece.color;
        }
    }

    int i = 0;
    while (i + height < BOARD_HEIGHT) {
        for (int j=0; j < 4; j++) {

            if (i + 1 + height >= BOARD_HEIGHT) {
                continue;
            }

            // Update the falling piece
            temp_falling_piece_grid.grid[i + 1 + height][j + self->m_offset] = temp_grid.grid[i][j];
        }

        i++;
    }

    if (piece_collides(&self->m_last_tetris_grid, &temp_falling_piece_grid)) {
        return false;
    }

    return true;
}

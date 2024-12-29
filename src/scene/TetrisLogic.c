#include "TetrisLogic.h"
#include "TetrisUtils.h"
#include "Pieces.h"
#include "TetrisTime.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

//global 
bool g_game_start;

bool init_tetris_board(TetrisBoard *p_tetris_board) {
    // Init grids
    const int empty_grid[BOARD_HEIGHT][BOARD_WIDTH] = {0};
    memcpy(p_tetris_board->m_tetris_grid.grid, empty_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    init_tetris_edges(p_tetris_board);
    memcpy(p_tetris_board->m_last_tetris_grid.grid, p_tetris_board->m_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    memcpy(p_tetris_board->m_falling_piece_grid.grid, empty_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);

    // init member variables
    g_game_start = false;
    p_tetris_board->m_offset = 6;
    p_tetris_board->m_points = 0;
    p_tetris_board->m_lines_cleared = 0;
    p_tetris_board->m_current_level = 0;

    return true; // If everything initialized properly (TODO: add a check)
}

void init_tetris_edges(TetrisBoard *p_tetris_board) {

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        p_tetris_board->m_tetris_grid.grid[i][0] = GREY;
        p_tetris_board->m_tetris_grid.grid[i][1] = GREY;
        p_tetris_board->m_tetris_grid.grid[i][BOARD_WIDTH - 1] = GREY;
        p_tetris_board->m_tetris_grid.grid[i][BOARD_WIDTH - 2] = GREY;
    }

    for (int j = 0; j < BOARD_WIDTH; j++) {
        p_tetris_board->m_tetris_grid.grid[BOARD_HEIGHT - 1][j] = GREY;
    }
}

TetrisGrid* get_tetris_grid(TetrisBoard *p_tetris_board) {
    return &p_tetris_board->m_tetris_grid;
}

TetrisGrid* get_last_tetris_grid(TetrisBoard *p_tetris_board) {
    return &p_tetris_board->m_last_tetris_grid;
}

TetrisGrid* get_falling_piece_grid(TetrisBoard *p_tetris_board) {
    return &p_tetris_board->m_falling_piece_grid;
}

Piece* get_falling_piece(TetrisBoard *p_tetris_board) {
    return &p_tetris_board->m_piece;
}

Piece get_next_piece(TetrisBoard *p_tetris_board) {
    return p_tetris_board->m_next_piece;
}

int get_points(TetrisBoard *p_tetris_board) {
    return p_tetris_board->m_points;
}

int get_level(TetrisBoard *p_tetris_board) {
    return p_tetris_board->m_current_level;
}


/** GAME LOGIC **/
void tetris_loop(TetrisBoard *p_tetris_board) {
    make_piece_fall(p_tetris_board, 0);


    if (piece_collides(&p_tetris_board->m_last_tetris_grid, &p_tetris_board->m_falling_piece_grid)) {
        
        // Place the block one step behind the collision
        make_piece_fall(p_tetris_board, -1);
        // update the last tetris grid
        AND_tetris_grid(&p_tetris_board->m_tetris_grid, &p_tetris_board->m_last_tetris_grid);
        combine_tetris_grids(&p_tetris_board->m_tetris_grid, &p_tetris_board->m_falling_piece_grid);

        // Clear the possible lines 
        clear_lines(p_tetris_board);

        // Update last tetris grid
        memcpy(p_tetris_board->m_last_tetris_grid.grid, p_tetris_board->m_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);

        // Check for game over
        game_over(p_tetris_board);

        // Move to the next block
        reset_tetris_counter();
        p_tetris_board->m_offset = 6; // Initial position of the falling block
        generate_new_piece(p_tetris_board, time(NULL));
        return;
    }

    // Clear screen for the falling piece
    AND_tetris_grid(&p_tetris_board->m_tetris_grid, &p_tetris_board->m_last_tetris_grid);

    // Render piece on the Tetris Grid
    combine_tetris_grids(&p_tetris_board->m_tetris_grid, &p_tetris_board->m_falling_piece_grid);
}

bool piece_collides(TetrisGrid *p_last_tetris_grid, TetrisGrid *p_falling_piece_grid) {
    
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

void make_piece_fall(TetrisBoard *p_tetris_board, int height_offset) {
    int height = get_tetris_counter() + height_offset;
    TetrisGrid temp_grid = {.grid = {0}};
    clear_tetris_grid(&p_tetris_board->m_falling_piece_grid);

    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            temp_grid.grid[i][j] = p_tetris_board->m_piece.tetromino[i][j] * p_tetris_board->m_piece.color;
        }
    }

    int i = 0;
    while (i + height < BOARD_HEIGHT) {
        for (int j=0; j < 4; j++) {

            if (i + 1 + height >= BOARD_HEIGHT) {
                continue;
            }

            // Update the falling piece
            p_tetris_board->m_falling_piece_grid.grid[i + 1 + height][j + p_tetris_board->m_offset] = temp_grid.grid[i][j];
        }

        i++;
    }
}

void game_over(TetrisBoard *p_tetris_board) {
    for (int j=2; j < BOARD_WIDTH - 2; j++) {
        if (p_tetris_board->m_last_tetris_grid.grid[2][j] != 0) {
            printf("GAME OVER!!\n");
            printf("YOUR SCORE IS: %lu\n", p_tetris_board->m_points);
        }
    }
}

void clear_lines(TetrisBoard *p_tetris_board) {
    u_short line_count = 0;
    bool full_line = true;

    // Find every lines in the grid
    for (int i=2; i < BOARD_HEIGHT - 1; i++) {
        full_line = true;
        for (int j=2; j < BOARD_WIDTH - 2; j++) {
            if (p_tetris_board->m_tetris_grid.grid[i][j] == 0) {
                full_line = false;
                break;
            }
        }

        if (full_line) {
            line_count++;
            full_line = false;
            clear_line(p_tetris_board, i);
        }
    }

    // Calculate Points TODO: Should also win points when piece is placed
    if (line_count == 1) {
        p_tetris_board->m_points += 40 * (p_tetris_board->m_current_level + 1);
        p_tetris_board->m_lines_cleared += 1;
        printf("ONE LINE CLEARED\n");
    }
    else if (line_count == 2) {
        p_tetris_board->m_points += 100 * (p_tetris_board->m_current_level + 1);
        p_tetris_board->m_lines_cleared += 2;
        printf("TWO LINE CLEARED\n");
    }
    else if (line_count == 3) {
        p_tetris_board->m_points += 300 * (p_tetris_board->m_current_level + 1);
        p_tetris_board->m_lines_cleared += 3;
        printf("THREE LINE CLEARED\n");
    }
    else if (line_count == 4) {
        p_tetris_board->m_points += 1200 * (p_tetris_board->m_current_level + 1);
        p_tetris_board->m_lines_cleared += 4;
        printf("TETRIS\n");
    }

    if (line_count > 0) {
        update_level(p_tetris_board);
    }
}

void clear_line(TetrisBoard *p_tetris_board, int line) {
    for (int j=2; j < BOARD_WIDTH - 2; j++) {
        p_tetris_board->m_tetris_grid.grid[line][j] = 0;
    }

    TetrisGrid temp_grid = p_tetris_board->m_tetris_grid;
    for (int i=2; i < line; i++) {
        for (int j=2; j < BOARD_WIDTH - 2; j++) {
            p_tetris_board->m_tetris_grid.grid[i + 1][j] = temp_grid.grid[i][j];
        }
    }
}

// TODO: Implement NES piece generation 
void generate_new_piece(TetrisBoard *p_tetris_board, u_int random_seed) { 

    srand(random_seed);
    int random_piece = random_to_piece(ceil(((double)rand() / (double)RAND_MAX) * 7));

    if (!g_game_start) {
        p_tetris_board->m_next_piece = create_piece(random_piece);
    }

    p_tetris_board->m_piece = p_tetris_board->m_next_piece;
    p_tetris_board->m_next_piece = create_piece(random_piece);
}

/** LEVELING AND SPEED **/
void update_level(TetrisBoard *p_tetris_board) {
    if (p_tetris_board->m_current_level >= 0) {
        // if (m_lines_cleared >= (m_current_level * 10 + 10)) {
        if (p_tetris_board->m_lines_cleared >= 10) {
            p_tetris_board->m_current_level++;
            // m_lines_cleared = m_lines_cleared - ((m_current_level - 1) * 10 + 10);
            p_tetris_board->m_lines_cleared = p_tetris_board->m_lines_cleared - 10;

            update_speed(p_tetris_board);
        }
    }

    printf("LINES: %i\n", p_tetris_board->m_lines_cleared);
    printf("LEVEL: %i\n", p_tetris_board->m_current_level);
}

void update_speed(TetrisBoard *p_tetris_board) {
    if (p_tetris_board->m_current_level >= 0 && p_tetris_board->m_current_level <= 10) {
        update_tick_interval(20);
    }

    else if (p_tetris_board->m_current_level == 13) {
        update_tick_interval(20);
    }

    else if (p_tetris_board->m_current_level == 16) {
        update_tick_interval(20);
    }

    else if (p_tetris_board->m_current_level == 19) {
        update_tick_interval(20);
    }

    else if (p_tetris_board->m_current_level == 29) {
        update_tick_interval(20);
    }
}

/** MOVEMENT **/

void rotate_piece_clockwise(TetrisBoard *p_tetris_board) {
    if (can_rotate(p_tetris_board)) {
        rotate_up_piece(&p_tetris_board->m_piece);
    }
}

void move_left(TetrisBoard *p_tetris_board) {
    if (can_move_left(p_tetris_board)) {
        p_tetris_board->m_offset--;
    }
}
void move_right(TetrisBoard *p_tetris_board) {
    if (can_move_right(p_tetris_board)) {
        p_tetris_board->m_offset++;
    }
}

bool can_move_left(TetrisBoard *p_tetris_board) {
    TetrisGrid temp_grid = {.grid = {0}};
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            temp_grid.grid[i][j - 1] |= p_tetris_board->m_falling_piece_grid.grid[i][j];
        }
    }

    if (piece_collides(&p_tetris_board->m_last_tetris_grid, &temp_grid)) {
        return false;
    }

    return true;
}
bool can_move_right(TetrisBoard *p_tetris_board) {
    TetrisGrid temp_grid = {.grid = {0}};
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            temp_grid.grid[i][j + 1] |= p_tetris_board->m_falling_piece_grid.grid[i][j];
        }
    }

    if (piece_collides(&p_tetris_board->m_last_tetris_grid, &temp_grid)) {
        return false;
    }

    return true;
}


bool can_rotate(TetrisBoard *p_tetris_board) {
    TetrisGrid temp_grid = {.grid = {0}};
    TetrisGrid temp_falling_piece_grid = {.grid = {0}};
    Piece temp_piece = p_tetris_board->m_piece;
    rotate_up_piece(&temp_piece);
    int height = get_tetris_counter() + 0;
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
            temp_falling_piece_grid.grid[i + 1 + height][j + p_tetris_board->m_offset] = temp_grid.grid[i][j];
        }

        i++;
    }

    if (piece_collides(&p_tetris_board->m_last_tetris_grid, &temp_falling_piece_grid)) {
        return false;
    }

    return true;
}



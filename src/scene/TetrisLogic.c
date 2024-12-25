#include "TetrisLogic.h"
#include "TetrisUtils.h"
#include "Pieces.h"
#include "TetrisTime.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

//global 
bool game_start;
int random_seed;

bool initialize_tetris_scene() {
    const int empty_grid[BOARD_HEIGHT][BOARD_WIDTH] = {0};

    memcpy(m_tetris_grid.grid, empty_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    init_tetris_edges(&m_tetris_grid);
    memcpy(m_last_tetris_grid.grid, m_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);
    memcpy(m_falling_piece_grid.grid, empty_grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);

    game_start = false;
    m_offset = 6;
    return true; // If everything initialized properly (TODO: add a check)
}

void init_tetris_edges(TetrisGrid *p_grid) {

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        p_grid->grid[i][0] = GREY;
        p_grid->grid[i][1] = GREY;
        p_grid->grid[i][BOARD_WIDTH - 1] = GREY;
        p_grid->grid[i][BOARD_WIDTH - 2] = GREY;
    }

    for (int j = 0; j < BOARD_WIDTH; j++) {
        // p_grid->grid[0][j] = GREY;
        // p_grid->grid[1][j] = GREY;
        p_grid->grid[BOARD_HEIGHT - 1][j] = GREY;
    }
}

TetrisGrid* get_tetris_grid() {
    return &m_tetris_grid;
}

TetrisGrid* get_last_tetris_grid() {
    return &m_last_tetris_grid;
}

TetrisGrid* get_falling_piece_grid() {
    return &m_falling_piece_grid;
}

Piece* get_falling_piece() {
    return &m_piece;
}

int get_points() {
    return m_points;
}

/** GAME LOGIC **/
void tetris_loop() {
    make_piece_fall(0);


    if (piece_collides(&m_last_tetris_grid, &m_falling_piece_grid)) {
        
        // Place the block one step behind the collision
        make_piece_fall(-1);
        // update the last tetris grid
        AND_tetris_grid(&m_tetris_grid, &m_last_tetris_grid);
        combine_tetris_grids(&m_tetris_grid, &m_falling_piece_grid);

        // Clear the possible lines 
        clear_lines();

        // Update last tetris grid
        memcpy(m_last_tetris_grid.grid, m_tetris_grid.grid, sizeof(int) * BOARD_HEIGHT * BOARD_WIDTH);

        // Check for game over
        game_over();

        // Move to the next block
        reset_tetris_counter();
        m_offset = 6;
        random_seed = time(NULL); // Time since jan 1 1970
        generate_new_piece();
        return;
    }

    // Clear screen for the falling piece
    AND_tetris_grid(&m_tetris_grid, &m_last_tetris_grid);

    // Render piece on the Tetris Grid
    combine_tetris_grids(&m_tetris_grid, &m_falling_piece_grid);
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

void make_piece_fall(int height_offset) {
    int height = get_tetris_counter() + height_offset;
    TetrisGrid temp_grid = {.grid = {0}};
    clear_tetris_grid(&m_falling_piece_grid);

    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            temp_grid.grid[i][j] = m_piece.tetromino[i][j] * m_piece.color;
        }
    }

    int i = 0;
    while (i + height < BOARD_HEIGHT) {
        for (int j=0; j < 4; j++) {

            if (i + 1 + height >= BOARD_HEIGHT) {
                continue;
            }

            // Update the falling piece
            m_falling_piece_grid.grid[i + 1 + height][j + m_offset] = temp_grid.grid[i][j];
        }

        i++;
    }
}

void clear_lines() {
    u_short line_count = 0;
    bool full_line = true;

    // Find every lines in the grid
    for (int i=2; i < BOARD_HEIGHT - 1; i++) {
        full_line = true;
        for (int j=2; j < BOARD_WIDTH - 2; j++) {
            if (m_tetris_grid.grid[i][j] == 0) {
                full_line = false;
                break;
            }
        }

        if (full_line) {
            line_count++;
            full_line = false;
            clear_line(i);
        }
    }
    printf("Line count: %i\n", line_count);

    // Calculate Points
    if (line_count == 1) {
        m_points += 1000;
        printf("ONE LINE CLEARED\n");
    }
    else if (line_count == 2) {
        m_points += 2000;
        printf("TWO LINE CLEARED\n");
    }
    else if (line_count == 3) {
        m_points += 3000;
        printf("THREE LINE CLEARED\n");
    }
    else if (line_count == 4) {
        m_points += 5000;
        printf("TETRIS\n");
    }
}

void clear_line(int line) {
    for (int j=2; j < BOARD_WIDTH - 2; j++) {
        m_tetris_grid.grid[line][j] = 0;
    }

    TetrisGrid temp_grid = m_tetris_grid;
    for (int i=2; i < line; i++) {
        for (int j=2; j < BOARD_WIDTH - 2; j++) {
            m_tetris_grid.grid[i + 1][j] = temp_grid.grid[i][j];
        }
    }
}

void game_over() {
    for (int j=2; j < BOARD_WIDTH - 2; j++) {
        if (m_last_tetris_grid.grid[2][j] != 0) {
            printf("GAME OVER!!\n");
            printf("YOUR SCORE IS: %lu\n", m_points);
        }
    }
}

void init_new_piece() {
    int tetromino_line[4] = {1, 1, 1, 1};

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
            tetromino_line[j] = m_piece.tetromino[i][j];
        }

        for (int j = 3; j < 7; j++) {
            if (tetromino_line[j - 3] != 0) {
                m_falling_piece_grid.grid[i + 2][j + 3] = m_piece.color;
            }
        }
    }

    print_grid(m_tetris_grid.grid);
}

void generate_new_piece() {
    srand(random_seed);
    int random_piece = random_to_piece(ceil(((double)rand() / (double)RAND_MAX) * 7));
    printf("piece: %i\n", random_piece);
    m_piece = create_piece(random_piece);
    m_piece = create_piece(LINE_BLOCK);
}

/** MOVEMENT **/
bool can_move_left() {
    TetrisGrid temp_grid = {.grid = {0}};
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            temp_grid.grid[i][j - 1] |= m_falling_piece_grid.grid[i][j];
        }
    }

    if (piece_collides(&m_last_tetris_grid, &temp_grid)) {
        return false;
    }

    return true;
}
bool can_move_right() {
    TetrisGrid temp_grid = {.grid = {0}};
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            temp_grid.grid[i][j + 1] |= m_falling_piece_grid.grid[i][j];
        }
    }

    if (piece_collides(&m_last_tetris_grid, &temp_grid)) {
        return false;
    }

    return true;
}


bool can_rotate() {
    TetrisGrid temp_grid = {.grid = {0}};
    TetrisGrid temp_falling_piece_grid = {.grid = {0}};
    Piece temp_piece = m_piece;
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
            temp_falling_piece_grid.grid[i + 1 + height][j + m_offset] = temp_grid.grid[i][j];
        }

        i++;
    }

    if (piece_collides(&m_last_tetris_grid, &temp_falling_piece_grid)) {
        return false;
    }

    return true;
}

void update_event(bool *is_running) {
    SDL_Event current_event;
    while (SDL_PollEvent(&current_event) != 0) {
        switch (current_event.type) {
            case SDL_QUIT:
                *is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (current_event.key.keysym.sym) {
                    case SDLK_a: 
                        if (can_move_left()) {
                            m_offset -= 1;
                        }
                        break;
                    case SDLK_d:
                        if (can_move_right()) {
                            m_offset += 1;
                        }
                        break;
                    case SDLK_w:
                        if (can_rotate()) {
                            rotate_up_piece(&m_piece);
                        }
                        break;
                }
            break;
        }
    }
}


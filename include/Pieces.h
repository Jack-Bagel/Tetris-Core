#pragma once

typedef enum Tetromino {
    EMPTY = 0,
    LINE_BLOCK = 1,
    SQUARE_BLOCK = 2,
    T_BLOCK = 3,
    L_BLOCK = 4,
    R_L_BLOCK = 5,
    Z_BLOCK = 6,
    R_Z_BLOCK = 7,
    EDGE = 8

} Tetromino ;

typedef struct Piece {
    Tetromino type;
    int tetromino[4][4];
} Piece;


extern Piece create_piece(Tetromino tetromino);
extern int *get_block_color(Tetromino tetromino);

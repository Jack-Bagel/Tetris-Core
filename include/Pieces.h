#pragma once

typedef enum Tetromino {
    EMPTY,
    LINE_BLOCK,
    LINE_BLOCK_ROT,
    SQUARE_BLOCK,
    T_BLOCK,
    T_BLOCK_ROT_1,
    T_BLOCK_ROT_2,
    T_BLOCK_ROT_3,
    L_BLOCK,
    L_BLOCK_ROT_1,
    L_BLOCK_ROT_2,
    L_BLOCK_ROT_3,
    R_L_BLOCK,
    R_L_BLOCK_ROT_1,
    R_L_BLOCK_ROT_2,
    R_L_BLOCK_ROT_3,
    Z_BLOCK,
    Z_BLOCK_ROT,
    R_Z_BLOCK,
    R_Z_BLOCK_ROT,
    EDGE

} Tetromino;

// Piece colors must be odd for collision detection
typedef enum PieceColor {
    BLACK = 0,
    RED = 1,
    BLUE = 3,
    YELLOW = 5,
    GREEN = 7,
    PURPLE = 9,
    ORANGE = 11,
    CYAN = 13,
    PINK = 15,
    GREY = 17

} PieceColor;

typedef struct Piece {
    PieceColor color;
    Tetromino type;
    int tetromino[4][4];
} Piece;


extern Piece create_piece(Tetromino tetromino);
extern int *get_block_color(PieceColor color);
extern void rotate_up_piece(Piece *piece);

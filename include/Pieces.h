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

typedef struct Tetrominos {
    const int line_block[4][4];
    const int line_block_rot[4][4];

    const int square_block[4][4];

    const int T_block[4][4];
    const int T_block_rot_1[4][4];
    const int T_block_rot_2[4][4];
    const int T_block_rot_3[4][4];

    const int L_block[4][4];
    const int L_block_rot_1[4][4];
    const int L_block_rot_2[4][4];
    const int L_block_rot_3[4][4];

    const int R_L_block[4][4];
    const int R_L_block_rot_1[4][4];
    const int R_L_block_rot_2[4][4];
    const int R_L_block_rot_3[4][4];

    const int Z_block[4][4];
    const int Z_block_rot[4][4];

    const int R_Z_block[4][4];
    const int R_Z_block_rot[4][4];

} Tetrominos;

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
extern void rotate_clockwise(Piece *piece);
extern void rotate_counter_clockwise(Piece *piece);

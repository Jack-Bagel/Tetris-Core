#include "Pieces.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const Tetrominos tetrominos = {
    .line_block =
       {{0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},

    .line_block_rot =
       {{0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}},

    .square_block =
       {{0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}},
    .T_block =
       {{0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

    .T_block_rot_1 =
       {{0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

    .T_block_rot_2 =
       {{0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},

    .T_block_rot_3 = 
       {{0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},
    
    .L_block =
       {{0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}},

    .L_block_rot_1 =
       {{0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}},

    .L_block_rot_2 =
       {{0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    .L_block_rot_3 =
       {{0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},

    .R_L_block =
       {{0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}},
    .R_L_block_rot_1 =
       {{0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},
    .R_L_block_rot_2 = 
       {{1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    .R_L_block_rot_3 =
       {{0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},
    .Z_block =
       {{0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}},

    .Z_block_rot =
       {{0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}},

    .R_Z_block =
       {{0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}},
    
    .R_Z_block_rot =
       {{0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}}
};


Piece create_piece(Tetromino tetromino) {
    
    Piece I_block = {
        .type = LINE_BLOCK,
        .color = CYAN,
        .tetromino = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece S_block = {
        .type = SQUARE_BLOCK,
        .color = YELLOW,
        .tetromino = {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece T_block = {
        .type = T_BLOCK,
        .color = PURPLE,
        .tetromino = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece L_block = {
        .type = L_BLOCK,
        .color = ORANGE,
        .tetromino = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece R_L_block = {
        .type = R_L_BLOCK,
        .color = BLUE,
        .tetromino = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}}
    };

    Piece Z_block = {
        .type = Z_BLOCK,
        .color = RED,
        .tetromino = {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}}
    };

    Piece R_Z_block = {
        .type = R_Z_BLOCK,
        .color = GREEN,
        .tetromino = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece error_block = {
        .type = EDGE,
        .color = GREY,
        .tetromino = {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0}}
    };

    switch (tetromino) {
        case LINE_BLOCK: 
            return I_block;
        case SQUARE_BLOCK:
            return S_block;
        case T_BLOCK:
            return T_block;
        case L_BLOCK:
            return L_block;
        case R_L_BLOCK:
            return R_L_block;
        case Z_BLOCK:
            return Z_block;
        case R_Z_BLOCK:
            return R_Z_block;
        default: return error_block;
    }
}

void rotate_clockwise(Piece *piece) {

    switch (piece->type) {
        case LINE_BLOCK:
            memcpy(piece->tetromino, tetrominos.line_block_rot, sizeof(int) * 4 * 4);
            piece->type = LINE_BLOCK_ROT;
            break;
        case LINE_BLOCK_ROT:
            memcpy(piece->tetromino, tetrominos.line_block, sizeof(int) * 4 * 4);
            piece->type = LINE_BLOCK;
            break;

        case T_BLOCK:
            memcpy(piece->tetromino, tetrominos.T_block_rot_1, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK_ROT_1;
            break;
        case T_BLOCK_ROT_1:
            memcpy(piece->tetromino, tetrominos.T_block_rot_2, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK_ROT_2;
            break;
        case T_BLOCK_ROT_2:
            memcpy(piece->tetromino, tetrominos.T_block_rot_3, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK_ROT_3;
            break;
        case T_BLOCK_ROT_3:
            memcpy(piece->tetromino, tetrominos.T_block, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK;
            break;

        case L_BLOCK:
            memcpy(piece->tetromino, tetrominos.L_block_rot_1, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK_ROT_1;
            break;
        case L_BLOCK_ROT_1:
            memcpy(piece->tetromino, tetrominos.L_block_rot_2, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK_ROT_2;
            break;
        case L_BLOCK_ROT_2:
            memcpy(piece->tetromino, tetrominos.L_block_rot_3, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK_ROT_3;
            break;
        case L_BLOCK_ROT_3:
            memcpy(piece->tetromino, tetrominos.L_block, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK;
            break;

        case R_L_BLOCK:
            memcpy(piece->tetromino, tetrominos.R_L_block_rot_1, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK_ROT_1;
            break;
        case R_L_BLOCK_ROT_1:
            memcpy(piece->tetromino, tetrominos.R_L_block_rot_2, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK_ROT_2;
            break;
        case R_L_BLOCK_ROT_2:
            memcpy(piece->tetromino, tetrominos.R_L_block_rot_3, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK_ROT_3;
            break;
        case R_L_BLOCK_ROT_3:
            memcpy(piece->tetromino, tetrominos.R_L_block, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK;
            break;

        case Z_BLOCK:
            memcpy(piece->tetromino, tetrominos.Z_block_rot, sizeof(int) * 4 * 4);
            piece->type = Z_BLOCK_ROT;
            break;
        case Z_BLOCK_ROT:
            memcpy(piece->tetromino, tetrominos.Z_block, sizeof(int) * 4 * 4);
            piece->type = Z_BLOCK;
            break;

        case R_Z_BLOCK:
            memcpy(piece->tetromino, tetrominos.R_Z_block_rot, sizeof(int) * 4 * 4);
            piece->type = R_Z_BLOCK_ROT;
            break;
        case R_Z_BLOCK_ROT:
            memcpy(piece->tetromino, tetrominos.R_Z_block, sizeof(int) * 4 * 4);
            piece->type = R_Z_BLOCK;
            break;

        default:
            memcpy(piece->tetromino, tetrominos.square_block, sizeof(int) * 4 * 4);
            piece->type = SQUARE_BLOCK;
            printf("Something went horribly wrong");
            break;
    }
}


void rotate_counter_clockwise(Piece *piece) {

    switch (piece->type) {
        case LINE_BLOCK:
            memcpy(piece->tetromino, tetrominos.line_block_rot, sizeof(int) * 4 * 4);
            piece->type = LINE_BLOCK_ROT;
            break;
        case LINE_BLOCK_ROT:
            memcpy(piece->tetromino, tetrominos.line_block, sizeof(int) * 4 * 4);
            piece->type = LINE_BLOCK;
            break;

        case T_BLOCK:
            memcpy(piece->tetromino, tetrominos.T_block_rot_3, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK_ROT_3;
            break;
        case T_BLOCK_ROT_3:
            memcpy(piece->tetromino, tetrominos.T_block_rot_2, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK_ROT_2;
            break;
        case T_BLOCK_ROT_2:
            memcpy(piece->tetromino, tetrominos.T_block_rot_1, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK_ROT_1;
            break;
        case T_BLOCK_ROT_1:
            memcpy(piece->tetromino, tetrominos.T_block, sizeof(int) * 4 * 4);
            piece->type = T_BLOCK;
            break;

        case L_BLOCK:
            memcpy(piece->tetromino, tetrominos.L_block_rot_3, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK_ROT_3;
            break;
        case L_BLOCK_ROT_3:
            memcpy(piece->tetromino, tetrominos.L_block_rot_2, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK_ROT_2;
            break;
        case L_BLOCK_ROT_2:
            memcpy(piece->tetromino, tetrominos.L_block_rot_1, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK_ROT_1;
            break;
        case L_BLOCK_ROT_1:
            memcpy(piece->tetromino, tetrominos.L_block, sizeof(int) * 4 * 4);
            piece->type = L_BLOCK;
            break;

        case R_L_BLOCK:
            memcpy(piece->tetromino, tetrominos.R_L_block_rot_3, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK_ROT_3;
            break;
        case R_L_BLOCK_ROT_3:
            memcpy(piece->tetromino, tetrominos.R_L_block_rot_2, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK_ROT_2;
            break;
        case R_L_BLOCK_ROT_2:
            memcpy(piece->tetromino, tetrominos.R_L_block_rot_1, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK_ROT_1;
            break;
        case R_L_BLOCK_ROT_1:
            memcpy(piece->tetromino, tetrominos.R_L_block, sizeof(int) * 4 * 4);
            piece->type = R_L_BLOCK;
            break;

        case Z_BLOCK:
            memcpy(piece->tetromino, tetrominos.Z_block_rot, sizeof(int) * 4 * 4);
            piece->type = Z_BLOCK_ROT;
            break;
        case Z_BLOCK_ROT:
            memcpy(piece->tetromino, tetrominos.Z_block, sizeof(int) * 4 * 4);
            piece->type = Z_BLOCK;
            break;

        case R_Z_BLOCK:
            memcpy(piece->tetromino, tetrominos.R_Z_block_rot, sizeof(int) * 4 * 4);
            piece->type = R_Z_BLOCK_ROT;
            break;
        case R_Z_BLOCK_ROT:
            memcpy(piece->tetromino, tetrominos.R_Z_block, sizeof(int) * 4 * 4);
            piece->type = R_Z_BLOCK;
            break;

        default:
            memcpy(piece->tetromino, tetrominos.square_block, sizeof(int) * 4 * 4);
            piece->type = SQUARE_BLOCK;
            printf("Something went horribly wrong");
            break;
    }
}

int *get_block_color(PieceColor color) {
    int *block_color = malloc(sizeof(int) * 3);

    switch (color) {
        case EMPTY:
            block_color[0] = 0;   
            block_color[1] = 0;   
            block_color[2] = 0;   
            break;
        case RED: 
            block_color[0] = 255;   
            block_color[1] = 0;   
            block_color[2] = 0;   
            break;
        case GREEN:
            block_color[0] = 0;   
            block_color[1] = 255;   
            block_color[2] = 0;   
            break;
        case BLUE:
            block_color[0] = 0;   
            block_color[1] = 0;   
            block_color[2] = 255;   
            break;
        case YELLOW:
            block_color[0] = 255;   
            block_color[1] = 255;   
            block_color[2] = 0;   
            break;
        case PURPLE:
            block_color[0] = 255;   
            block_color[1] = 0;   
            block_color[2] = 255;   
            break;
        case CYAN:
            block_color[0] = 0;   
            block_color[1] = 255;   
            block_color[2] = 255;   
            break;
        case ORANGE:
            block_color[0] = 255;   
            block_color[1] = 150;   
            block_color[2] = 50;   
            break;
        case GREY:
            block_color[0] = 128;
            block_color[1] = 128;
            block_color[2] = 128;
            break;
        default:
            block_color[0] = 255;   
            block_color[1] = 255;   
            block_color[2] = 255;   

    }

    return block_color;
}

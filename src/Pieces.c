#include "Pieces.h"
#include <stdlib.h>

Piece create_piece(Tetromino tetromino) {
    
    Piece I_block = { 
        .type = LINE_BLOCK,
        .tetromino = {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece S_block = { 
        .type = SQUARE_BLOCK,
        .tetromino = {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece T_block = { 
        .type = T_BLOCK,
        .tetromino = {
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece L_block = { 
        .type = L_BLOCK,
        .tetromino = {
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece R_L_block = { 
        .type = R_L_BLOCK,
        .tetromino = {
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece Z_block = { 
        .type = Z_BLOCK,
        .tetromino = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece R_Z_block = { 
        .type = R_Z_BLOCK,
        .tetromino = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}
    };

    Piece error_block = { 
        .type = EDGE,
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

int *get_block_color(Tetromino tetromino) {
    int *block_color = malloc(sizeof(int) * 3);

    switch (tetromino) {
        case EMPTY:
            block_color[0] = 0;   
            block_color[1] = 0;   
            block_color[2] = 0;   
            break;
        case LINE_BLOCK: 
            block_color[0] = 255;   
            block_color[1] = 0;   
            block_color[2] = 0;   
            break;
        case SQUARE_BLOCK:
            block_color[0] = 0;   
            block_color[1] = 255;   
            block_color[2] = 0;   
            break;
        case T_BLOCK:
            block_color[0] = 0;   
            block_color[1] = 0;   
            block_color[2] = 255;   
            break;
        case L_BLOCK:
            block_color[0] = 255;   
            block_color[1] = 255;   
            block_color[2] = 0;   
            break;
        case R_L_BLOCK:
            block_color[0] = 255;   
            block_color[1] = 0;   
            block_color[2] = 255;   
            break;
        case Z_BLOCK:
            block_color[0] = 0;   
            block_color[1] = 255;   
            block_color[2] = 255;   
            break;
        case R_Z_BLOCK:
            block_color[0] = 255;   
            block_color[1] = 150;   
            block_color[2] = 50;   
            break;
        case EDGE:
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

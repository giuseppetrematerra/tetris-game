//
// Created by giuse on 04/02/2021.
//

#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    uint8_t pos_x;
    uint8_t pos_y;
    bool visible;
} block_t;

block_t* generateBlock(uint8_t pos_x, uint8_t pos_y, bool visible);
bool compareBlock(block_t first, block_t second);

#endif //TETRIS_BLOCK_H

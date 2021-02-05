//
// Created by giuse on 04/02/2021.
//

#ifndef TETRIS_BLOCK_LIST_H
#define TETRIS_BLOCK_LIST_H

#include "block.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    block_t *array;
    uint8_t size;
} block_list_t;

void appendBlockList(block_list_t *array, block_t item);

bool containsBlock(block_list_t array, block_t block);

#endif //TETRIS_BLOCK_LIST_H

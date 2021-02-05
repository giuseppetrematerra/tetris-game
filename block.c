//
// Created by giuse on 04/02/2021.
//

#include "block.h"

block_t* generateBlock(uint8_t pos_x, uint8_t pos_y, bool visible)
{
    block_t* block = calloc(1, sizeof(block_t));
    block->pos_x = pos_x;
    block->pos_y = pos_y;
    block->visible = visible;
    return block;
}

bool compareBlock(block_t first, block_t second)
{
    return (first.pos_x == second.pos_x && first.pos_y == second.pos_y && first.visible == second.visible);
}

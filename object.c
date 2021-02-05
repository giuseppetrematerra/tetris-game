//
// Created by giuse on 03/02/2021.
//

#include "object.h"

bool compareObject(object_t first, object_t second)
{
    return (first.rotation == second.rotation && objectHasBlocks(first, *second.blocks));
}

bool objectHasBlocks(object_t obj, block_list_t blocks)
{
    if(obj.blocks->size != blocks.size) return false;
    uint8_t i;
    for(i = 0; i < obj.blocks->size; i++)
    {
        if(!containsBlock(blocks, obj.blocks->array[i]))
            return false;
    }
    return true;
}
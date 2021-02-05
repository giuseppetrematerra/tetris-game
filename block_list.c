//
// Created by giuse on 04/02/2021.
//

#include "block_list.h"

void appendBlockList(block_list_t *array, block_t item)
{
    block_t *block_pointer;

    array->size += 1;

    block_pointer = realloc(array->array, array->size * sizeof(block_t));

    array->array = block_pointer;
    array->array[array->size-1] = item;
}

bool containsBlock(block_list_t array, block_t block)
{
    uint8_t i;
    for(i = 0; i < array.size; i++)
    {
        if(compareBlock(array.array[i], block)) return true;
    }
    return false;
}

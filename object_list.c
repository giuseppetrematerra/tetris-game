//
// Created by giuse on 04/02/2021.
//

#include "object_list.h"

void appendObjectList(object_list_t *array, object_t *item)
{
    object_t **object_pointer;

    array->size += 1;

    object_pointer = realloc(array->array, array->size * sizeof(object_t));

    array->array = object_pointer;
    array->array[array->size-1] = item;
}

int8_t containsObject(object_list_t list, object_t object)
{
    uint8_t i;
    for(i = 0; i < list.size; i++)
    {
        if(compareObject(*list.array[i], object)) return i;
    }
    return -1;
}

bool hasBlock(object_list_t *list, block_t block)
{
    uint8_t i;
    for(i = 0; i < list->size; i++)
    {
        object_t *object = list->array[i];
        if(containsBlock(*object->blocks, block)) return true;
    }
    return false;
}

int8_t hasBlocks(object_list_t *array, block_list_t blocks)
{
    uint8_t i;
    for(i = 0; i < array->size; i++)
    {
        object_t *object = array->array[i];
        if(objectHasBlocks(*object, blocks)) return i;
    }
    return -1;
}
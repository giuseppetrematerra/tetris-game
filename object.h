//
// Created by giuse on 01/02/2021.
//



#ifndef TETRIS_OBJECT_H
#define TETRIS_OBJECT_H

#include "block_list.h"

typedef enum
{
    NoRotation,
    Horizontal,
    Vertical
} rotation_t;

typedef enum
{
    Left,
    Right,
    Bottom,
    Top
} direction_t;

typedef struct object
{
    block_list_t *blocks;
    rotation_t rotation;
    bool moveable;
} object_t;

bool compareObject(object_t first, object_t second);
bool objectHasBlocks(object_t obj, block_list_t blocks);

#endif //TETRIS_OBJECT_H

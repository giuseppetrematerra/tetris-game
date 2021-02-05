//
// Created by giuse on 04/02/2021.
//

#ifndef TETRIS_OBJECT_LIST_H
#define TETRIS_OBJECT_LIST_H

#include "object.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    object_t **array;
    uint8_t size;
} object_list_t;

void appendObjectList(object_list_t*, object_t*);

int8_t containsObject(object_list_t, object_t);

#endif //TETRIS_OBJECT_LIST_H

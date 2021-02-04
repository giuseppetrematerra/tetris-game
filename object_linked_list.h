//
// Created by giuse on 01/02/2021.
//

#ifndef TETRIS_OBJECT_LINKED_LIST_H
#define TETRIS_OBJECT_LINKED_LIST_H

#include "object.h"

typedef struct linked_object {
    object_t value;
    struct linked_object *next;
} linked_object_t;

void push(linked_object_t*, object_t);
void pop(linked_object_t *root, object_t obj);
object_t *getObject(linked_object_t *root, Rotation rotation, uint8_t position_x, uint8_t position_y);
bool hasObject(linked_object_t*, object_t);
#endif //TETRIS_OBJECT_LINKED_LIST_H

//
// Created by giuse on 01/02/2021.
//

#include "object_linked_list.h"
#include <stdlib.h>
void push(linked_object_t *root, object_t obj)
{
    linked_object_t *last = NULL;
    linked_object_t *current = root->next;

    while(current != NULL) {
        last = current;
        current = current->next;
    }

    linked_object_t *next = (linked_object_t*) calloc(1, sizeof(linked_object_t));
    next->value = obj;
    if(last == NULL) root->next = next;
    else last->next = next;
}

void pop(linked_object_t *root, object_t obj)
{
    linked_object_t *current = root;
    while(current != NULL)
    {
        linked_object_t *middle = current->next;
        if(middle != NULL)
        {
            linked_object_t *next = middle->next;
            if(next != NULL)
            {
                if(compare(middle->value, obj))
                {
                    current->next = next;
                    return;
                } else current = middle;
            } else {
                current->next = NULL;
                return;
            }
        }
    }
}

object_t *getObject(linked_object_t *root, Rotation rotation, uint8_t position_x, uint8_t position_y)
{
    object_t *result = calloc(1, sizeof(object_t));
    linked_object_t *current = root->next;
    bool found = false;
    while(current != NULL)
    {
        object_t value = current->value;
        if(value.rotation == rotation && value.position_x == position_x && value.position_y == position_y)
        {
            *result = value;
            found = true;
        }
        current = current->next;
    }
    if(!found) return NULL;
    else return result;
}

bool hasObject(linked_object_t *root, object_t obj)
{
    linked_object_t *current = root->next;
    while(current != NULL)
    {
        object_t value = current->value;
        if(value.rotation == obj.rotation && value.position_x == obj.position_x && value.position_y == obj.position_y)
            return true;
        current = current->next;
    }
    return false;
}


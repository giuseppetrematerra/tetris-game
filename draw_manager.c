//
// Created by giuse on 24/01/2021.
//

#include "draw_manager.h"
#include <stdio.h>
#include <stdlib.h>

void initGrid(uint8_t *grid_ptr)
{
    uint8_t y, x;
    for(y = 0; y < GRID_Y; y++)
    {
        for(x = 0; x < GRID_X; x++)
        {
            *(grid_ptr + x + (y * GRID_Y))  = EMPTY_CHAR;
        }
    }
}

object_t *generateObject(uint8_t position_x, uint8_t position_y, Shape shape, Rotation rotation)
{
    if(rotation == NoRotation && shape != Square) return NULL;
    object_t *object = calloc(1, sizeof(object_t));
    object->position_x = position_x;
    object->position_y = position_y;
    object->rotation = rotation;
    object->shape = shape;
    return object;
}

bool canDrawObject(object_t obj)
{
    switch (obj.rotation) {
        case Horizontal:
            if(obj.position_x >= 0 && obj.position_x < GRID_X - 2 && obj.position_y >= 0 && obj.position_y < GRID_Y)
                return true;
        case Vertical:
            if(obj.position_x >= 0 && obj.position_x < GRID_X && obj.position_y >= 0 && obj.position_y < GRID_Y - 2)
                return true;
        default:
            return false;
    }
}

void tryAddObject(linked_object_t *rootObject, object_t *object)
{
    if(object != NULL)
    {
        if(!hasObject(rootObject, *object) && canDrawObject(*object))
            push(rootObject, *object);
    } else {
        printf("[ERROR] You cant add a not-valid object.\n\n");
    }
}

void tryRemoveObject(linked_object_t *rootObject, object_t object)
{
    if(hasObject(rootObject, object))
        pop(rootObject, object);
}

void drawObject(uint8_t *grid_ptr, object_t obj)
{
    *(grid_ptr + obj.position_x + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
    switch (obj.rotation) {
        case NoRotation:
            *(grid_ptr + obj.position_x + 1 + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + (GRID_Y * (obj.position_y + 1))) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + 1 + (GRID_Y * (obj.position_y + 1))) = BLOCK_CHAR;
            break;
        case Horizontal:
            *(grid_ptr + obj.position_x + 1 + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + 2 + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
            break;
        case Vertical:
            *(grid_ptr + obj.position_x + (GRID_Y * (obj.position_y + 1))) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + (GRID_Y * (obj.position_y + 2))) = BLOCK_CHAR;
            break;
    }
}

void drawObjects(linked_object_t *rootObject, uint8_t *grid_ptr)
{
    linked_object_t *current = rootObject->next;
    while(current != NULL)
    {
        object_t value = current->value;
        drawObject(grid_ptr, value);
        current = current->next;
    }
}

void printGrid(const uint8_t *grid_ptr)
{
    int y, x;
    for(y = 0; y < GRID_Y; y++)
    {
        for(x = 0; x < GRID_X; x++)
        {
            printf("%c", *(grid_ptr + x + (y * (GRID_Y))));
        }
        printf("\n");
    }
    printf("\n");
}

void drawFinalGrid(const uint8_t *grid_ptr)
{
    int y, x, temp;
    for(y = 0; y < FULL_GRID_Y; y++)
    {
        for(x = 0; x < FULL_GRID_X; x++)
        {
            if(x == 0 && y == 0) {
                temp = TOPLEFT_CHAR;
            } else if(x == GRID_MARGIN_X && y == 0) {
                temp = TOPRIGHT_CHAR;
            } else if(x == 0 && y == GRID_MARGIN_Y) {
                temp = BOTTOMLEFT_CHAR;
            } else if(x == GRID_MARGIN_X && y == GRID_MARGIN_Y) {
                temp = BOTTOMRIGHT_CHAR;
            } else if(x == 0 || x == GRID_MARGIN_X) {
                temp = VERTICAL_MARGIN_CHAR;
            } else if(y == 0 || y == GRID_MARGIN_Y) {
                temp = HORIZZONTAL_MARGIN_CHAR;
            } else temp = *(grid_ptr + ((x - 1) + ((y - 1) * (GRID_Y))));
            printf("%c", temp);
        }
        printf("\n");
    }
    printf("\n");
}

void moveObject(linked_object_t *rootObject, object_t *obj, Direction direction)
{
    uint8_t end_x = obj->position_x, end_y = obj->position_y;
    switch (direction) {
        case Left:
            end_x -= 1;
            break;
        case Right:
            end_x += 1;
            break;
        case Bottom:
            end_y += 1;
            break;
    }
    object_t *temp = generateObject(end_x, end_y, obj->shape, obj->rotation);
    tryRemoveObject(rootObject, *obj);
    tryAddObject(rootObject, temp);
}


void clearConsole(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
//
// Created by giuse on 24/01/2021.
//

#include "draw_manager.h"
#include <stdio.h>
#include <stdlib.h>

void initGrid(wchar_t *grid_ptr)
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

object_t *generateObject(uint8_t position_x, uint8_t position_y, Rotation rotation)
{
    object_t *object = calloc(1, sizeof(object_t));
    object->position_x = position_x;
    object->position_y = position_y;
    object->rotation = rotation;
    return object;
}

bool canDrawObject(object_t obj)
{
    switch (obj.rotation) {
        case HorizontalLine:
            if(obj.position_x >= 0 && obj.position_x < GRID_X - 2 && obj.position_y >= 0 && obj.position_y < GRID_Y)
                return true;
        case VerticalLine:
            if(obj.position_x >= 0 && obj.position_x < GRID_X && obj.position_y >= 0 && obj.position_y < GRID_Y - 2)
                return true;
        default:
            return false;
    }
}

bool isValidPosition(uint8_t x, uint8_t y, Rotation rotation)
{
    return(x >= 0 && x < GRID_X && y >= 0 && y < GRID_Y);
}

bool isValidMove(uint8_t start_x, uint8_t start_y, Rotation rotation)
{
    uint8_t end_x = start_x, end_y = start_y;
    switch (rotation) {
        case NoRotation:
            end_x += 1;
            end_y += 1;
            break;
        case HorizontalLine:
            end_x += 2;
            break;
        case VerticalLine:
            end_y += 2;
            break;
    }

    return(start_x >= 0 && start_x < GRID_X && end_x < GRID_X && start_y >= 0 && start_y < GRID_Y && end_y < GRID_Y);
}

void tryAddObject(linked_object_t *rootObject, object_t *object)
{
    if(object != NULL)
    {
        if(!hasObject(rootObject, *object) && isValidMove(object->position_x, object->position_y, object->rotation))
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

void drawObject(wchar_t *grid_ptr, object_t obj)
{
    *(grid_ptr + obj.position_x + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
    switch (obj.rotation) {
        case NoRotation:
            *(grid_ptr + obj.position_x + 1 + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + (GRID_Y * (obj.position_y + 1))) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + 1 + (GRID_Y * (obj.position_y + 1))) = BLOCK_CHAR;
            break;
        case HorizontalLine:
            *(grid_ptr + obj.position_x + 1 + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + 2 + (GRID_Y * obj.position_y)) = BLOCK_CHAR;
            break;
        case VerticalLine:
            *(grid_ptr + obj.position_x + (GRID_Y * (obj.position_y + 1))) = BLOCK_CHAR;
            *(grid_ptr + obj.position_x + (GRID_Y * (obj.position_y + 2))) = BLOCK_CHAR;
            break;
    }
}

void drawObjects(linked_object_t *rootObject, wchar_t *grid_ptr)
{
    linked_object_t *current = rootObject->next;
    while(current != NULL)
    {
        object_t value = current->value;
        drawObject(grid_ptr, value);
        current = current->next;
    }
}

void printGrid(const wchar_t *grid_ptr)
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

void drawFinalGrid(const wchar_t *grid_ptr)
{
    int y, x, temp;
    printf("Punteggio: %d\n\n", score);
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
            printf("%lc", temp);
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
        case Top:
            end_y -= 1;
            break;
    }
    if(isValidMove(end_x, end_y, obj->rotation))
    {
        tryRemoveObject(rootObject, *obj);
        obj->position_x = end_x;
        obj->position_y = end_y;
        tryAddObject(rootObject, obj);
    }
}

void rotateObject(linked_object_t *rootObject, object_t *obj)
{
    if(obj->rotation == NoRotation) return;
    uint8_t end_x = obj->position_x, end_y = obj->position_y;
    if(isValidMove(end_x, end_y, obj->rotation))
    {
        tryRemoveObject(rootObject, *obj);
        obj->position_x = end_x;
        obj->position_y = end_y;
        obj->rotation = obj->rotation ^ 3;
        tryAddObject(rootObject, obj);
    }
}

void handleArrow(linked_object_t *rootObject, object_t *obj)
{
#if defined(_WIN32) || defined(_WIN64)
    int temp = getch();
    if (temp == 0 || temp == 224) {
        Direction direction;
        switch(getch()) {
            case 72:
                direction = Top;
                break;
            case 75:
                direction = Left;
                break;
            case 77:
                direction = Right;
                break;
            case 80:
                direction = Bottom;
                break;
        }
        moveObject(rootObject, obj, direction);
    } else if(temp == 32)
        rotateObject(rootObject, obj);
    else if(temp == 33)
        exit(0);
#elif
    printf("This function is not supported on any unix-like OS");
#endif
}

void clearConsole(void){
    system(CLEAR_CONSOLE);
}
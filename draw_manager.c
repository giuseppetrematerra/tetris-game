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
            *(grid_ptr + x + (y * GRID_Y)) = EMPTY_CHAR;
        }
    }
}

bool isBlockThere(object_list_t objects, uint8_t x, uint8_t y, object_t exclude)
{
    uint8_t i, j;
    for(i = 0; i < objects.size; i++)
    {
        object_t *object = objects.array[i];
        if(compareObject(*object, exclude)) continue;
        block_list_t blocks = *objects.array[i]->blocks;
        for(j = 0; j < blocks.size; j++)
        {
            block_t block = blocks.array[j];
            if(block.pos_x == x && block.pos_y == y && block.visible) return true;
        }
    }
    return false;
}

bool isValidPosition(uint8_t x, uint8_t y)
{
    return(x >= 0 && x < GRID_X && y >= 0 && y < GRID_Y);
}

bool isValidMove(object_list_t objects, object_t obj, direction_t direction)
{
    uint8_t i;
    int8_t extra_x = 0, extra_y = 0, final_x, final_y;

    switch (direction) {
        case Left:
            extra_x -= 1;
            break;
        case Right:
            extra_x += 1;
            break;
        case Bottom:
            extra_y += 1;
            break;
        case Top:
            extra_y -= 1;
            break;
    }

    for(i = 0; i < obj.blocks->size; i++)
    {
        block_t block = obj.blocks->array[i];
        final_x = block.pos_x + extra_x;
        final_y = block.pos_y + extra_y;
        if(!isValidPosition(final_x, final_y) || isBlockThere(objects, final_x, final_y, obj))
            return false;
    }
    return true;
}


bool canDrawBlock(object_list_t objects, block_t block)
{
    return isValidPosition(block.pos_x, block.pos_y);
}

bool canDrawObject(object_list_t objects, object_t obj)
{
    uint8_t i;
    for(i = 0; i < obj.blocks->size; i++)
    {
        block_t block = obj.blocks->array[i];
        if(!canDrawBlock(objects, block)) return false;
    }
    return true;
}

void drawBlock(wchar_t *grid_ptr, block_t block)
{
    *(grid_ptr + block.pos_x + (GRID_Y * block.pos_y)) = BLOCK_CHAR;
}

void drawObject(wchar_t *grid_ptr, object_t obj)
{
    uint8_t i;
    for(i = 0; i < obj.blocks->size; i++)
    {
        block_t block = obj.blocks->array[i];
        drawBlock(grid_ptr, block);
    }
}

void drawObjects(wchar_t *grid_ptr, object_list_t *list)
{
    uint8_t i;
    for(i = 0; i < list->size; i++)
    {
        drawObject(grid_ptr, *list->array[i]);
    }
}


void tryAddObject(object_list_t *list, object_t *object)
{
    if(containsObject(*list, *object) == -1 && canDrawObject(*list, *object))
    {
        appendObjectList(list, object);
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
                temp = HORIZONTAL_MARGIN_CHAR;
            } else temp = *(grid_ptr + ((x - 1) + ((y - 1) * (GRID_Y))));
            printf("%lc", temp);
        }
        printf("\n");
    }
    printf("\n");
}

void moveBlock(block_t *block, uint8_t pos_x, uint8_t pos_y)
{
    block->pos_x = pos_x;
    block->pos_y = pos_y;
}

void moveBlockDirection(block_t *block, direction_t direction)
{
    int8_t end_x = block->pos_x, end_y = block->pos_y;
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
    moveBlock(block, end_x, end_y);
}

void moveObject(object_list_t *objects, object_t *obj, direction_t direction)
{
    if(!obj->moveable) return;
    if(isValidMove(*objects, *obj, direction))
    {
        uint8_t i, next_y;
        for(i = 0; i < obj->blocks->size; i++)
        {
            block_t *block = &obj->blocks->array[i];
            moveBlockDirection(block, direction);
        }
        if(direction == Bottom)
        {
            for(i = 0; i < obj->blocks->size; i++)
            {
                block_t *block = &obj->blocks->array[i];
                next_y = block->pos_y + 1;
                if(obj->moveable)
                {
                    if(isBlockThere(*objects, block->pos_x, next_y, *obj))
                    {
                        collision(obj);
                    } else if(block->pos_y == GRID_Y - 1)
                    {
                        collision(obj);
                        checkForLastRow(objects);
                    }
                }
            }
        }
    } else if(direction == Bottom)
    {
        collision(obj);
    }
}

void collision(object_t *obj)
{
    obj->moveable = false;
}

void checkForLastRow(object_list_t *objects)
{
    uint8_t i, j;
    block_list_t *temp, *actual;
    temp = calloc(1, sizeof(block_list_t));
    temp->array = calloc(1, sizeof(block_t));
    actual = calloc(1, sizeof(block_list_t));
    temp->array = calloc(1, sizeof(block_t));
    for(i = 0; i < objects->size; i++)
    {
        object_t *object = objects->array[i];
        for(j = 0; j < object->blocks->size; j++)
        {
            block_t block = object->blocks->array[j];
            if(block.pos_y == GRID_Y - 1)
            {
                appendBlockList(temp, block);
            } else appendBlockList(actual, block);
        }
    }
    if(temp->size == GRID_X)
    {
        for(i = 0; i < temp->size; i++)
        {
            block_t *block = &temp->array[i];
            block->visible = false;
        }
        for(i = 0; i < actual->size; i++)
        {
            block_t *block = &actual->array[i];
            block->pos_y += 1;
        }
    }
}

bool isValidRotation(object_list_t objects, object_t obj, rotation_t rotation, direction_t direction)
{
    block_t block = obj.blocks->array[0], block2 = obj.blocks->array[1], block3 = obj.blocks->array[2];
    if(direction == Left)
    {
        if(rotation == Horizontal)
        {
            return (isValidPosition(block.pos_x - 2, block.pos_y + 2) &&
            isValidPosition(block2.pos_x - 1, block2.pos_y + 1) &&
            !isBlockThere(objects, block.pos_x - 2, block.pos_y + 2, obj) &&
            !isBlockThere(objects, block2.pos_x - 1, block2.pos_y + 1, obj));
        } else if(rotation == Vertical)
        {
            return (isValidPosition(block.pos_x, block.pos_y - 2) &&
            isValidPosition(block2.pos_x - 1, block2.pos_y - 1) &&
            isValidPosition(block3.pos_x - 2, block3.pos_y) &&
            !isBlockThere(objects, block.pos_x, block.pos_y - 2, obj) &&
            !isBlockThere(objects, block2.pos_x - 1, block2.pos_y - 1, obj) &&
            !isBlockThere(objects, block3.pos_x - 2, block3.pos_y, obj));
        }
    } else if(direction == Right)
    {
        if(rotation == Horizontal)
        {
            return (isValidPosition(block.pos_x, block.pos_y + 2) &&
            isValidPosition(block2.pos_x + 1, block2.pos_y + 1) &&
            isValidPosition(block3.pos_x + 2, block3.pos_y) &&
            !isBlockThere(objects, block.pos_x, block.pos_y + 2, obj) &&
            !isBlockThere(objects,block2.pos_x + 1, block2.pos_y + 1, obj) &&
            !isBlockThere(objects,block3.pos_x + 2, block3.pos_y, obj));
        } else if(rotation == Vertical)
        {
            return (isValidPosition(block.pos_x + 2, block.pos_y - 2) &&
            isValidPosition(block2.pos_x + 1, block2.pos_y - 1) &&
            !isBlockThere(objects,block.pos_x + 2, block.pos_y - 2, obj) &&
            !isBlockThere(objects,block2.pos_x + 1, block2.pos_y - 1, obj));
        }
    }
    return false;
}

void rotateObject(object_list_t objects, object_t *obj, direction_t direction)
{
    if(obj->rotation == NoRotation || !obj->moveable) return;
    rotation_t newRotation = obj->rotation ^ 3;
    if(isValidRotation(objects, *obj, newRotation, direction))
    {
        block_t *block = &obj->blocks->array[0], *block2 = &obj->blocks->array[1], *block3 = &obj->blocks->array[2];
        if(direction == Left)
        {
            if(newRotation == Horizontal)
            {
                moveBlock(block, block->pos_x - 2, block->pos_y + 2);
                moveBlock(block2, block2->pos_x - 1, block2->pos_y + 1);
            } else if(newRotation == Vertical)
            {
                moveBlock(block, block->pos_x, block->pos_y - 2);
                moveBlock(block2, block2->pos_x - 1, block2->pos_y - 1);
                moveBlock(block3, block3->pos_x - 2, block3->pos_y);
            }
        } else if(direction == Right)
        {
            if(newRotation == Horizontal)
            {
                moveBlock(block, block->pos_x, block->pos_y + 2);
                moveBlock(block2, block2->pos_x + 1, block2->pos_y + 1);
                moveBlock(block3, block3->pos_x + 2, block3->pos_y);
            } else if(newRotation == Vertical)
            {
                moveBlock(block, block->pos_x + 2, block->pos_y - 2);
                moveBlock(block2, block2->pos_x + 1, block2->pos_y - 1);
            }
        }
        obj->rotation = newRotation;
    }
}

void handleArrow(object_list_t *objects, object_t *obj)
{
#if defined(_WIN32) || defined(_WIN64)
    int temp = getch();
    if (temp == 0 || temp == 224) {
        direction_t direction;
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
        moveObject(objects, obj, direction);
    } else if(temp == 115) //Sinistra
        rotateObject(*objects, obj, Left);
    else if(temp == 100)
        rotateObject(*objects, obj, Right);
    else if(temp == 33)
        exit(0);
#elif
    printf("This function is not supported on any unix-like OS");
#endif
}

void clearConsole(void){
    system(CLEAR_CONSOLE);
}

void applyChanges(wchar_t *grid_ptr, object_list_t *objects)
{
    initGrid(grid_ptr);
    drawObjects(grid_ptr, objects);
    #if DEBUG == false
    clearConsole();
    #endif
    printGrid(grid_ptr);
}

bool isEnded(object_list_t *objects)
{
    uint8_t i, j;
    for(i = 0; i < objects->size; i++)
    {
        object_t *object = objects->array[i];
        for(j = 0; j < object->blocks->size; j++)
        {
            block_t block = object->blocks->array[j];
            if(block.pos_y == 0) return true;
        }
    }
    return false;
}

void endGame()
{
    printf("The game is ended.");
}

object_t *randomObject(object_list_t *objects)
{
    if(isEnded(objects)) return NULL;
    object_t *obj = generateObject(rand()%GRID_X, 0, rand()%3);
    return obj;
}

object_t* generateObject(uint8_t position_x, uint8_t position_y, rotation_t rotation)
{
    object_t *object = calloc(1, sizeof(object_t));
    object->blocks = calloc(1, sizeof(block_list_t));
    switch (rotation) {
        case NoRotation:
            appendBlockList(object->blocks, *generateBlock(position_x, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 1, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x, position_y + 1, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 1, position_y + 1, true));
            break;
        case Horizontal:
            appendBlockList(object->blocks, *generateBlock(position_x, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 1, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 2, position_y, true));
            break;
        case Vertical:
            appendBlockList(object->blocks, *generateBlock(position_x, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x, position_y + 1, true));
            appendBlockList(object->blocks, *generateBlock(position_x, position_y + 2, true));
            break;
    }
    object->rotation = rotation;
    object->moveable = true;
    return object;
}
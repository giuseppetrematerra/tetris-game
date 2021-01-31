//
// Created by giuse on 24/01/2021.
//

#include "draw_manager.h"
#include <stdio.h>
#include <stdlib.h>

void initObjects()
{
    int i, j;
    for(i = 0; i < SQUARE_Y; i++)
    {
        for(j = 0; j < SQUARE_X; j++)
        {
            $square.absolute_space[i][j] = BLOCK_CHAR;
        }
    }
    for(i = 0; i < LINE_Y; i++)
    {
        for(j = 0; j < LINE_X; j++)
        {
            $line.absolute_space[i][j] = BLOCK_CHAR;
        }
    }
}

void generateLine(struct Object *line, unsigned char x, enum LineRotation rotation)
{
    line->obj_ptr = $line.absolute_space;
    line->position_x = x;
    line->position_y = LINE_Y;
    line->dimension_x = LINE_X;
    line->dimension_y = LINE_Y;
    line->rotation = rotation;
}

void generateSquare(struct Object square, unsigned char x)
{
    square.obj_ptr = $square.absolute_space;
    square.position_x = x;
    square.position_y = SQUARE_Y;
    square.dimension_x = SQUARE_X;
    square.dimension_y = SQUARE_Y;
    square.rotation = NoRotation;
}
void initGrid(unsigned char *grid_ptr)
{
    int y, x, obj;

    *(grid_ptr) = TOPLEFT_CHAR;
    *(grid_ptr + GRID_MARGIN_X) = TOPRIGHT_CHAR;
    *(grid_ptr + ((GRID_MARGIN_Y) * (FULL_GRID_Y))) = BOTTOMLEFT_CHAR;
    *(grid_ptr + GRID_MARGIN_X + ((GRID_MARGIN_Y) * (FULL_GRID_Y))) = BOTTOMRIGHT_CHAR;

    for(y = 0; y < FULL_GRID_Y; y++)
    {
        for(x = 0; x < FULL_GRID_X; x++)
        {
            if(y == 0 || y == GRID_MARGIN_Y)
            {
                if(x == 0 || x == GRID_MARGIN_X)
                    continue;
                obj = HORIZZONTAL_MARGIN_CHAR;
            } else {
                if(x == 0 || x == GRID_MARGIN_X)
                    obj = VERTICAL_MARGIN_CHAR;
                else {
                    obj = EMPTY_CHAR;
                }
            }
            *(grid_ptr + x + (y * (FULL_GRID_Y)))  = obj;
        }
    }
}

int canPlace(struct Object object)
{
    enum Bool can = False;
    switch (object.rotation) {
        case NoRotation:
            break;
        case Horizontal:
            if(object.position_x > 0 && object.position_x < GRID_MARGIN_X - 2 && object.position_y > 0 && object.position_y < GRID_MARGIN_Y)
                can = True;
            break;
        case Vertical:
            break;
    }
    return can;
}

void placeObject(struct Object object, unsigned char *grid_ptr)
{
    switch (object.rotation) {
        case NoRotation:
            break;
        case Horizontal:
            *(grid_ptr + object.position_x + (GRID_MARGIN * (FULL_GRID_Y))) = *(object.obj_ptr);
            *(grid_ptr + object.position_x + 1 + (GRID_MARGIN * (FULL_GRID_Y))) = *(object.obj_ptr + 1);
            *(grid_ptr + object.position_x + 2 + (GRID_MARGIN * (FULL_GRID_Y))) = *(object.obj_ptr + 2);
            break;
        case Vertical:
            *(grid_ptr + object.position_x) = *(object.obj_ptr);
            *(grid_ptr + object.position_x + (1 * (FULL_GRID_Y))) = *(object.obj_ptr + 1);
            *(grid_ptr + object.position_x + (2 * (FULL_GRID_Y))) = *(object.obj_ptr + 2);
            break;
    }
}

void printGrid(const unsigned char *grid_ptr)
{
    int y, x;
    for(y = 0; y < FULL_GRID_Y; y++)
    {
        for(x = 0; x < FULL_GRID_X; x++)
        {
            printf("%c", *(grid_ptr + x + (y * (FULL_GRID_Y))));
        }
        printf("\n");
    }
}

void clearConsole(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
//
// Created by giuse on 24/01/2021.
//

#include "draw_manager.h"
#include <stdio.h>
#include <stdlib.h>

void initObjects()
{
    int y, x;
    for(y = 0; y < SQUARE_Y; y++)
    {
        for(x = 0; x < SQUARE_X; x++)
        {
            $square.absolute_space[y][x] = BLOCK_CHAR;
        }
    }
    for(y = 0; y < LINE_Y; y++)
    {
        for(x = 0; x < LINE_X; x++)
        {
            $line.absolute_space[y][x] = BLOCK_CHAR;
        }
    }
}

void generateLine(Object *line, unsigned char x, unsigned char y, enum LineRotation rotation)
{
    line->obj_ptr = $line.absolute_space;
    line->starting_x = x;
    line->starting_y = y;
    line->dimension_x = LINE_X;
    line->dimension_y = LINE_Y;
    line->rotation = rotation;
}

void generateSquare(Object *square, unsigned char x, unsigned char y)
{
    square->obj_ptr = $square.absolute_space;
    square->starting_x = x;
    square->starting_y = y;
    square->dimension_x = SQUARE_X;
    square->dimension_y = SQUARE_Y;
    square->rotation = NoRotation;
}
void initGrid(unsigned char *grid_ptr)
{
    int y, x;

    for(y = 0; y < GRID_Y; y++)
    {
        for(x = 0; x < GRID_X; x++)
        {
            *(grid_ptr + x + (y * GRID_Y))  = EMPTY_CHAR;
        }
    }
}

int canPlace(Object object)
{
    Bool can = false;
    switch (object.rotation) {
        case NoRotation:
            break;
        case Horizontal:
            if(object.starting_x > 0 && object.starting_x < GRID_MARGIN_X - 2 && object.starting_y > 0 && object.starting_y < GRID_MARGIN_Y)
                can = true;
            break;
        case Vertical:
            break;
    }
    return can;
}

void placeObject(Object object, unsigned char *grid_ptr)
{
    *(grid_ptr + object.starting_x + (GRID_Y * object.starting_y)) = *(object.obj_ptr);
    switch (object.rotation) {
        case NoRotation:
            *(grid_ptr + object.starting_x + 1 + (GRID_Y * object.starting_y)) = *(object.obj_ptr + 1);
            *(grid_ptr + object.starting_x + (GRID_Y * (object.starting_y + 1))) = *(object.obj_ptr + 2);
            *(grid_ptr + object.starting_x + 1 + (GRID_Y * (object.starting_y + 1))) = *(object.obj_ptr + 3);
            break;
        case Horizontal:
            *(grid_ptr + object.starting_x + 1 + (GRID_Y * object.starting_y)) = *(object.obj_ptr + 1);
            *(grid_ptr + object.starting_x + 2 + (GRID_Y * object.starting_y)) = *(object.obj_ptr + 2);
            break;
        case Vertical:
            *(grid_ptr + object.starting_x + (GRID_Y * (object.starting_y + 1))) = *(object.obj_ptr + 1);
            *(grid_ptr + object.starting_x + (GRID_Y * (object.starting_y + 2))) = *(object.obj_ptr + 2);
            break;
    }
}

void printEnclosureGrid(const unsigned char *grid_ptr)
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


void printGrid(const unsigned char *grid_ptr)
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

void clearConsole(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
//
// Created by giuse on 24/01/2021.
//
#include "object_linked_list.h"

#ifndef TETRIS_DRAW_MANAGER_H
#define TETRIS_DRAW_MANAGER_H

#define GRID_X 10
#define GRID_Y 10

#define GRID_MARGIN_X (GRID_X + 1)
#define GRID_MARGIN_Y (GRID_Y + 1)

#define FULL_GRID_X (GRID_MARGIN_X + 1)
#define FULL_GRID_Y (GRID_MARGIN_Y + 1)

#define EMPTY_CHAR 176
#define BLOCK_CHAR 219
#define TOPLEFT_CHAR 218
#define TOPRIGHT_CHAR 191
#define BOTTOMLEFT_CHAR 192
#define BOTTOMRIGHT_CHAR 217
#define VERTICAL_MARGIN_CHAR 179
#define HORIZZONTAL_MARGIN_CHAR 196

void initGrid(uint8_t *grid_ptr);
object_t *generateObject(uint8_t position_x, uint8_t position_y, Shape shape, Rotation rotation);
void tryAddObject(linked_object_t *rootObject, object_t *object);
void tryRemoveObject(linked_object_t *rootObject, object_t object);

bool canDrawObject(object_t object);
void drawObject(uint8_t *grid_ptr, object_t obj);
void drawObjects(linked_object_t *rootObject, uint8_t *grid_ptr);
void drawFinalGrid(const uint8_t *grid_ptr);

void printGrid(const uint8_t *grid_ptr);

void generateLine(object_t *line, Rotation rotation);
void generateSquare(object_t *square);
void moveObject(linked_object_t *rootObject, object_t *obj, Direction direction);
void clearConsole();
#endif //TETRIS_DRAW_MANAGER_H

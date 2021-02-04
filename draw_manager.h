//
// Created by giuse on 24/01/2021.
//
#include "object_linked_list.h"
#include <wchar.h>

#ifndef TETRIS_DRAW_MANAGER_H
#define TETRIS_DRAW_MANAGER_H

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#define EMPTY_CHAR 176
#define BLOCK_CHAR 219
#define TOPLEFT_CHAR 218
#define TOPRIGHT_CHAR 191
#define BOTTOMLEFT_CHAR 192
#define BOTTOMRIGHT_CHAR 217
#define VERTICAL_MARGIN_CHAR 179
#define HORIZZONTAL_MARGIN_CHAR 196
#define CLEAR_CONSOLE "cls"
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define EMPTY_CHAR L'\x2591'
#define BLOCK_CHAR L'\x2588'
#define TOPLEFT_CHAR L'\x256D'
#define TOPRIGHT_CHAR L'\x256E'
#define BOTTOMLEFT_CHAR L'\x2570'
#define BOTTOMRIGHT_CHAR L'\x256F'
#define VERTICAL_MARGIN_CHAR L'\x2502'
#define HORIZZONTAL_MARGIN_CHAR L'\x2500'
#define CLEAR_CONSOLE "clear"
#endif

#define GRID_X 10
#define GRID_Y 10

#define GRID_MARGIN_X (GRID_X + 1)
#define GRID_MARGIN_Y (GRID_Y + 1)

#define FULL_GRID_X (GRID_MARGIN_X + 1)
#define FULL_GRID_Y (GRID_MARGIN_Y + 1)


static int16_t score;

void initGrid(wchar_t *grid_ptr);
void tryAddObject(linked_object_t *rootObject, object_t *object);
void tryRemoveObject(linked_object_t *rootObject, object_t object);

object_t *generateObject(uint8_t position_x, uint8_t position_y, Rotation rotation);

bool canDrawObject(object_t object);
bool isValidMove(uint8_t start_x, uint8_t start_y, Rotation rotation);
void drawObject(wchar_t *grid_ptr, object_t obj);
void drawObjects(linked_object_t *rootObject, wchar_t *grid_ptr);
void drawFinalGrid(const wchar_t *grid_ptr);

void printGrid(const wchar_t *grid_ptr);

void generateLine(object_t *line, Rotation rotation);
void generateSquare(object_t *square);
void moveObject(linked_object_t *rootObject, object_t *obj, Direction direction);
void rotateObject(linked_object_t *rootObject, object_t *obj);
void handleArrow(linked_object_t *rootObject, object_t *obj);
void clearConsole(void);
#endif //TETRIS_DRAW_MANAGER_H

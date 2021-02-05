//
// Created by giuse on 24/01/2021.
//

#include <wchar.h>
#include "block_list.h"
#include "object_list.h"
#include <time.h>

#ifndef TETRIS_DRAW_MANAGER_H
#define TETRIS_DRAW_MANAGER_H

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#define EMPTY_CHAR 176//32//176
#define BLOCK_CHAR 35//254//219
#define TOPLEFT_CHAR 218
#define TOPRIGHT_CHAR 191
#define BOTTOMLEFT_CHAR 192
#define BOTTOMRIGHT_CHAR 217
#define VERTICAL_MARGIN_CHAR 179
#define HORIZONTAL_MARGIN_CHAR 196
#define CLEAR_CONSOLE "cls"
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define EMPTY_CHAR L'\x2591'
#define BLOCK_CHAR L'\x2588'
#define TOPLEFT_CHAR L'\x256D'
#define TOPRIGHT_CHAR L'\x256E'
#define BOTTOMLEFT_CHAR L'\x2570'
#define BOTTOMRIGHT_CHAR L'\x256F'
#define VERTICAL_MARGIN_CHAR L'\x2502'
#define HORIZONTAL_MARGIN_CHAR L'\x2500'
#define CLEAR_CONSOLE "clear"
#endif

#define GRID_X 10
#define GRID_Y 10

#define GRID_MARGIN_X (GRID_X + 1)
#define GRID_MARGIN_Y (GRID_Y + 1)

#define FULL_GRID_X (GRID_MARGIN_X + 1)
#define FULL_GRID_Y (GRID_MARGIN_Y + 1)

#define DEBUG true

static int16_t score;
static object_t *actualObject;

void initGrid(wchar_t*);
void tryAddObject(object_list_t*, object_t*);
void tryRemoveObject(object_list_t*, object_t);

bool isBlockThere(object_list_t objects, uint8_t x, uint8_t y, object_t exclude);
bool canDrawObject(object_list_t objects, object_t obj);
bool canDrawBlock(object_list_t objects, block_t block);
bool isValidPosition(uint8_t x, uint8_t y);
bool isValidMove(object_list_t objects, object_t obj, direction_t direction);
bool isValidRotation(object_list_t objects, object_t obj, rotation_t rotation, direction_t direction);
bool isEnded(object_list_t *objects);

void drawBlock(wchar_t *grid_ptr, block_t block);
void drawObject(wchar_t *grid_ptr, object_t obj);
void drawObjects(wchar_t *grid_ptr, object_list_t *list);
void drawFinalGrid(const wchar_t *grid_ptr);

void printGrid(const wchar_t *grid_ptr);

void moveBlock(block_t *block, uint8_t pos_x, uint8_t pos_y);
void moveBlockDirection(block_t *block, direction_t direction);
void moveObject(object_list_t *objects, object_t *obj, direction_t direction);
void collision(object_t *obj);
void checkForLastRow(object_list_t *objects);
void rotateObject(object_list_t objects, object_t *obj, direction_t direction);
void handleArrow(object_list_t *objects, object_t *obj);
void clearConsole(void);
void applyChanges(wchar_t *grid_ptr, object_list_t *objects);
void endGame();

object_t *randomObject(object_list_t *objects);
object_t* generateObject(uint8_t position_x, uint8_t position_y, rotation_t rotation);
#endif //TETRIS_DRAW_MANAGER_H

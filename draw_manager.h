//
// Created by giuse on 24/01/2021.
//

#ifndef TETRIS_DRAW_MANAGER_H
#define TETRIS_DRAW_MANAGER_H

#define SQUARE_X 2
#define SQUARE_Y 2

#define LINE_X 1
#define LINE_Y 3

#define GRID_X 10
#define GRID_Y 10

#define GRID_MARGIN 1

#define GRID_MARGIN_X GRID_X + GRID_MARGIN
#define GRID_MARGIN_Y GRID_Y + GRID_MARGIN

#define FULL_GRID_X GRID_MARGIN_X + GRID_MARGIN
#define FULL_GRID_Y GRID_MARGIN_Y + GRID_MARGIN

#define EMPTY_CHAR 176
#define BLOCK_CHAR 219
#define TOPLEFT_CHAR 218
#define TOPRIGHT_CHAR 191
#define BOTTOMLEFT_CHAR 192
#define BOTTOMRIGHT_CHAR 217
#define VERTICAL_MARGIN_CHAR 179
#define HORIZZONTAL_MARGIN_CHAR 196

enum LineRotation
{
    NoRotation,
    Horizontal,
    Vertical
};

enum Bool
{
    False,
    True
};

struct Object
{
    char *obj_ptr;
    unsigned char position_x;
    unsigned char position_y;
    unsigned char dimension_x;
    unsigned char dimension_y;
    enum LineRotation rotation;
};

struct Square
{
    unsigned char absolute_space[SQUARE_Y][SQUARE_X];
};

struct Line
{
    unsigned char absolute_space[LINE_Y][LINE_X];
};

static struct Square $square;
static struct Line $line;
static unsigned char $grid[FULL_GRID_Y][FULL_GRID_X];

void initObjects();
void initGrid(unsigned char *grid_ptr);
void printGrid(const unsigned char *grid_ptr);
void placeObject(struct Object object, unsigned char *grid_ptr);
int canPlace(struct Object object);

void generateLine(struct Object *line, unsigned char x, enum LineRotation rotation);
void generateSquare(struct Object square, unsigned char x);
void clearConsole();
#endif //TETRIS_DRAW_MANAGER_H

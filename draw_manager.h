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

enum LineRotation
{
    NoRotation,
    Horizontal,
    Vertical
};

typedef enum
{
    false,
    true
} Bool;

typedef struct
{
    char *obj_ptr;
    unsigned char starting_x;
    unsigned char starting_y;
    unsigned char dimension_x;
    unsigned char dimension_y;
    enum LineRotation rotation;
} Object;

typedef struct
{
    unsigned char absolute_space[SQUARE_Y][SQUARE_X];
} Square;

typedef struct
{
    unsigned char absolute_space[LINE_Y][LINE_X];
} Line;

static Square $square;
static Line $line;
static unsigned char $grid[FULL_GRID_Y][FULL_GRID_X];

void initObjects();
void initGrid(unsigned char *grid_ptr);
void printEnclosureGrid(const unsigned char *grid_ptr);
void printGrid(const unsigned char *grid_ptr);
void placeObject(Object object, unsigned char *grid_ptr);
int canPlace(Object object);

void generateLine(Object *line, unsigned char x, unsigned char y, enum LineRotation rotation);
void generateSquare(Object *square, unsigned char x, unsigned char y);
void clearConsole();
#endif //TETRIS_DRAW_MANAGER_H

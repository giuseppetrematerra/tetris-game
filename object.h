//
// Created by giuse on 01/02/2021.
//

#ifndef TETRIS_OBJECT_H
#define TETRIS_OBJECT_H

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    NoRotation,
    HorizontalLine,
    VerticalLine
} Rotation;

typedef enum
{
    Left,
    Right,
    Bottom,
    Top
} Direction;

typedef struct object
{
    uint8_t position_x;
    uint8_t position_y;
    Rotation rotation;
} object_t;

bool compare(object_t first, object_t second);

struct Utente
{
    char nome[30];
    char cognome[30];
    char domicilio[30];
    char telefono[30];
};

struct Elenco
{
    int index;
    struct Utente lista[30];
};

/*
 * utente[0] = Barbagianni Roberto, 3334549579845, Via Diaz, 1
 * utente[0] = Amato Tizio, 3333445757844, Via Lol, 2
 */

#endif //TETRIS_OBJECT_H

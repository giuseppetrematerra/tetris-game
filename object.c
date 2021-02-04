//
// Created by giuse on 03/02/2021.
//

#include "object.h"

bool compare(object_t first, object_t second)
{
    return (first.position_x == second.position_x && first.position_y == second.position_y && first.rotation == second.rotation);
}
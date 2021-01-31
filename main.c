#include <stdio.h>
#include "draw_manager.h"

int main()
{
    int y, x;
    unsigned char *ptr = (unsigned char *) $grid;
    initObjects();
    initGrid(ptr);
    printEnclosureGrid(ptr);
    Object line, square;
    generateLine(&line, 3, 2, Vertical);
    placeObject(line, ptr);
    generateSquare(&square, 3, 5);
    placeObject(square, ptr);
    printEnclosureGrid(ptr);
    //printf("%d\n", canPlace(line));
    return 0;
}

void tick()
{

}

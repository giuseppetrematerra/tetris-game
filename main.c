#include <stdio.h>
#include "draw_manager.h"

int main()
{
    int y, x;
    unsigned char *ptr = (unsigned char *) $grid;
    initObjects();
    initGrid(ptr);
    struct Object line;
    generateLine(&line, 12, Horizontal);
    printGrid(ptr);
    placeObject(line, ptr);
    printGrid(ptr);
    printf("%d\n", canPlace(line));
    return 0;
}

void tick()
{

}

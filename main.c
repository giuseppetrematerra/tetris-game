#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "draw_manager.h"

int main()
{
    object_t *line, *line2, *line3;
    linked_object_t *rootObject = calloc(1, sizeof(linked_object_t));
    uint8_t *ptr = calloc(GRID_Y * GRID_X, sizeof(uint8_t*));
    line = generateObject(3, 0, Line, Horizontal);
    line2 = generateObject(3, 2, Line, Horizontal);
    line3 = generateObject(3, 6, Line, Horizontal);
    initGrid(ptr);
    tryAddObject(rootObject, line);
    tryAddObject(rootObject, line2);
    tryAddObject(rootObject, line3);
    drawObjects(rootObject, ptr);
    drawFinalGrid(ptr);
    moveObject(rootObject, line2, Right);
    drawObjects(rootObject, ptr);
    drawFinalGrid(ptr);
    //printf("%d\n", canPlace(line));
/*    int test = getch();
    if (test == 0 || test == 224) {
        switch(getch()) {
            case 72:
                printf("Printed UP");
                break;
            case 75:
                printf("Printed LEFT");
                break;
            case 77:
                printf("Printed RIGHT");
                break;
            case 80:
                printf("Printed BOTTOM");
                break;
        }
    } else printf("%d", test);*/
    return 0;
}

void tick()
{

}

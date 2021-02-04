#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "draw_manager.h"

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    object_t *tempObject, *line2, *line3, *line4;
    linked_object_t *rootObject = calloc(1, sizeof(linked_object_t));
    wchar_t *tempGrid = calloc(GRID_Y * GRID_X, sizeof(wchar_t*));
    wchar_t *finalGrid = calloc(GRID_Y * GRID_X, sizeof(wchar_t*));
    tempObject = generateObject(0, 7, VerticalLine);
    line2 = generateObject(2, 2, HorizontalLine);
    line3 = generateObject(3, 3, HorizontalLine);
    line4 = generateObject(4, 4, HorizontalLine);
    initGrid(tempGrid);
    initGrid(finalGrid);
    tryAddObject(rootObject, tempObject);
    drawObjects(rootObject, tempGrid);
    printGrid(tempGrid);
/*//    moveObject(rootObject, tempObject, Top);
    rotateObject(rootObject, tempObject);
    initGrid(tempGrid);
    drawObjects(rootObject, tempGrid);
    printGrid(tempGrid);*/
    do {
        handleArrow(rootObject, tempObject);
        //moveObject(rootObject, tempObject, Right);
        initGrid(tempGrid);
        drawObjects(rootObject, tempGrid);
        clearConsole();
        drawFinalGrid(tempGrid);
    } while(true);

    return 0;
}

void tick()
{

}

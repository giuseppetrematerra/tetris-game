#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "draw_manager.h"

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(NULL) + 777);
    object_t *line2, *line3, *line4, *line5, *line6, *line7, *line8, *line9;
    object_list_t *objects = calloc(1, sizeof(object_list_t));
    wchar_t *tempGrid = calloc(GRID_Y * GRID_X, sizeof(wchar_t*));
    wchar_t *finalGrid = calloc(GRID_Y * GRID_X, sizeof(wchar_t*));
    //tempObject = generateObject(5, 3, Vertical);
    line2 = generateObject(0, 8, NoRotation);
    line3 = generateObject(2, 8, NoRotation);
    line4 = generateObject(4, 8, NoRotation);
    line5 = generateObject(6, 8, NoRotation);
    line6 = generateObject(8, 7, NoRotation);
    initGrid(tempGrid);
    initGrid(finalGrid);
    tryAddObject(objects, line2);
    tryAddObject(objects, line3);
    tryAddObject(objects, line4);
    tryAddObject(objects, line5);
    tryAddObject(objects, line6);
    actualObject = randomObject(objects);
    tryAddObject(objects, actualObject);
    applyChanges(tempGrid, objects);
#if DEBUG == true
    actualObject = line6;
    moveObject(objects, actualObject, Bottom);
    applyChanges(tempGrid, objects);
    moveObject(objects, actualObject, Bottom);
    applyChanges(tempGrid, objects);
    moveObject(objects, actualObject, Bottom);
    applyChanges(tempGrid, objects);
#else
    do {
        if(!actualObject->moveable)
        {
            actualObject = randomObject(objects);
            if(actualObject == NULL) break;
            tryAddObject(objects, actualObject);
            applyChanges(tempGrid, objects);
        }
        handleArrow(objects, actualObject);
        applyChanges(tempGrid, objects);
    } while(true);
    endGame();
#endif

    return 0;
}

void tick()
{

}

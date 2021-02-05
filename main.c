#include <locale.h>
#include "draw_manager.h"

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(NULL) + 777);
    object_list_t *objects = calloc(1, sizeof(object_list_t));
    wchar_t *grid = calloc(GRID_Y * GRID_X, sizeof(wchar_t*));
    bool won = false;
    printf("Benvenuti nel fantastico gioco del Tetris!\n");
    printf("Piazza 20 oggetti per vincere e fai attenzione a non finire lo spazio!\n");
    printf("Ogni volta che completi il fondo, riceverei 1 punto!\n");
    printf("Buon divertimento! :D\n");
    printf("Premi INVIO per cominciare...\n\n");
    getch();
    initGrid(grid);
    actualObject = randomObject(objects);
    tryAddObject(objects, actualObject);
    applyChanges(grid, objects);
    do {
        bool moved = false;
        if(!actualObject->moveable)
        {
            actualObject = randomObject(objects);
            if(actualObject == NULL) break;
            tryAddObject(objects, actualObject);
            applyChanges(grid, objects);
        }
        clock_t tstart = clock();
        while((clock() - tstart) / CLOCKS_PER_SEC < 1) {
            if(kbhit()) {
                handleKeyboard(objects, actualObject);
                checkForLastRow(objects);
                applyChanges(grid, objects);
                moved = true;
                break;
            }
        }
        if(!moved)
        {
            moveObject(objects, actualObject, Bottom);
            checkForLastRow(objects);
            applyChanges(grid, objects);
            moved = false;
        }
        if(objects->size == 20) {
            won = true;
            break;
        }
    } while(true);
    endGame(won);
    return 0;
}
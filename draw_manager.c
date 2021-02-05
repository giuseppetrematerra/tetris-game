//
// Created by giuse on 24/01/2021.
//

#include "draw_manager.h"

void initGrid(wchar_t *grid_ptr)
{
    uint8_t y, x;
    for(y = 0; y < GRID_Y; y++)
    {
        for(x = 0; x < GRID_X; x++)
        {
            *(grid_ptr + x + (y * GRID_Y)) = EMPTY_CHAR;
        }
    }
}


bool isBlockThere(object_list_t objects, uint8_t x, uint8_t y, object_t exclude)
{
    uint8_t i, j;
    for(i = 0; i < objects.size; i++)
    {
        object_t *object = objects.array[i];
        if(compareObject(*object, exclude)) continue;
        block_list_t blocks = *objects.array[i]->blocks;
        for(j = 0; j < blocks.size; j++)
        {
            block_t block = blocks.array[j];
            if(block.pos_x == x && block.pos_y == y && block.visible) return true;
        }
    }
    return false;
}


bool isValidPosition(uint8_t x, uint8_t y)
{
    return(x >= 0 && x < GRID_X && y >= 0 && y < GRID_Y);
}


bool isValidMove(object_list_t objects, object_t obj, direction_t direction)
{
    uint8_t i;
    int8_t extra_x = 0, extra_y = 0, final_x, final_y;

    switch (direction) {
        case Left:
            extra_x -= 1;
            break;
        case Right:
            extra_x += 1;
            break;
        case Bottom:
            extra_y += 1;
            break;
        case Top:
            extra_y -= 1;
            break;
    }

    for(i = 0; i < obj.blocks->size; i++)
    {
        block_t block = obj.blocks->array[i];
        final_x = block.pos_x + extra_x;
        final_y = block.pos_y + extra_y;
        if(!isValidPosition(final_x, final_y) || isBlockThere(objects, final_x, final_y, obj))
            return false;
    }
    return true;
}


bool canDrawBlock(object_list_t objects, block_t block, object_t exclude)
{
    return isValidPosition(block.pos_x, block.pos_y) && !isBlockThere(objects, block.pos_x, block.pos_y, exclude);
}


bool canDrawObject(object_list_t objects, object_t obj)
{
    uint8_t i;
    for(i = 0; i < obj.blocks->size; i++)
    {
        block_t block = obj.blocks->array[i];
        if(!canDrawBlock(objects, block, obj)) return false;
    }
    return true;
}


void drawBlock(wchar_t *grid_ptr, block_t block)
{
    *(grid_ptr + block.pos_x + (GRID_Y * block.pos_y)) = BLOCK_CHAR;
}


void drawObject(wchar_t *grid_ptr, object_t obj)
{
    uint8_t i;
    for(i = 0; i < obj.blocks->size; i++)
    {
        block_t block = obj.blocks->array[i];
        if(!block.visible) continue;
        drawBlock(grid_ptr, block);
    }
}


void drawObjects(wchar_t *grid_ptr, object_list_t *list)
{
    uint8_t i;
    for(i = 0; i < list->size; i++)
    {
        drawObject(grid_ptr, *list->array[i]);
    }
}


void tryAddObject(object_list_t *list, object_t *object)
{
    if(containsObject(*list, *object) == -1 && canDrawObject(*list, *object))
    {
        appendObjectList(list, object);
    }
}


void printGrid(const wchar_t *grid_ptr)
{
    int y, x;
    for(y = 0; y < GRID_Y; y++)
    {
        for(x = 0; x < GRID_X; x++)
        {
            printf("%c", *(grid_ptr + x + (y * (GRID_Y))));
        }
        printf("\n");
    }
    printf("\n");
}


void drawFinalGrid(const wchar_t *grid_ptr)
{
    int y, x, temp;
    printf("Punteggio: %d\n\n", score);
    for(y = 0; y < FULL_GRID_Y; y++)
    {
        for(x = 0; x < FULL_GRID_X; x++)
        {
            if(x == 0 && y == 0) {
                temp = TOPLEFT_CHAR;
            } else if(x == GRID_MARGIN_X && y == 0) {
                temp = TOPRIGHT_CHAR;
            } else if(x == 0 && y == GRID_MARGIN_Y) {
                temp = BOTTOMLEFT_CHAR;
            } else if(x == GRID_MARGIN_X && y == GRID_MARGIN_Y) {
                temp = BOTTOMRIGHT_CHAR;
            } else if(x == 0 || x == GRID_MARGIN_X) {
                temp = VERTICAL_MARGIN_CHAR;
            } else if(y == 0 || y == GRID_MARGIN_Y) {
                temp = HORIZONTAL_MARGIN_CHAR;
            } else temp = *(grid_ptr + ((x - 1) + ((y - 1) * (GRID_Y))));
            printf("%lc", temp);
        }
        printf("\n");
    }
    printf("\n");
}


void moveBlock(block_t *block, uint8_t pos_x, uint8_t pos_y)
{
    block->pos_x = pos_x;
    block->pos_y = pos_y;
}


void moveBlockDirection(block_t *block, direction_t direction)
{
    int8_t end_x = block->pos_x, end_y = block->pos_y;
    switch (direction) {
        case Left:
            end_x -= 1;
            break;
        case Right:
            end_x += 1;
            break;
        case Bottom:
            end_y += 1;
            break;
        case Top:
            end_y -= 1;
            break;
    }
    moveBlock(block, end_x, end_y);
}


void moveObject(object_list_t *objects, object_t *obj, direction_t direction)
{
    if(!obj->moveable) return;
    //Controlla se il movimento è valido
    if(isValidMove(*objects, *obj, direction))
    {
        uint8_t i, next_y;
        //Per ogni blocco dell'oggetto, esegue il movimento
        for(i = 0; i < obj->blocks->size; i++)
        {
            block_t *block = &obj->blocks->array[i];
            if(!block->visible) continue;
            moveBlockDirection(block, direction);
        }
        //Se la direzione è rivolta verso il basso, effettua due controlli:
        //- Se l'oggetto collide con un altro blocco
        //- Se l'oggetto tocca il fondo e quindi c'è bisogno di controllare il fondo
        if(direction == Bottom)
        {
            for(i = 0; i < obj->blocks->size; i++)
            {
                block_t *block = &obj->blocks->array[i];
                if(!block->visible) continue;
                next_y = block->pos_y + 1;
                if(obj->moveable)
                {
                    if(isBlockThere(*objects, block->pos_x, next_y, *obj))
                    {
                        obj->moveable = false;
                    } else if(block->pos_y == GRID_Y - 1)
                    {
                        obj->moveable = false;
                        checkForLastRow(objects);
                    }
                }
            }
        }
    } else if(direction == Bottom)
    {
        obj->moveable = false;
    }
}


void checkForLastRow(object_list_t *objects)
{
    uint8_t i, j, count = 0;
    //Conta ogni oggetto che si trova sul fondo e incrementa il conteggio
    for(i = 0; i < objects->size; i++)
    {
        object_t *object = objects->array[i];
        for(j = 0; j < object->blocks->size; j++)
        {
            block_t block = object->blocks->array[j];
            if(!block.visible) continue;
            if(block.pos_y == GRID_Y - 1)
            {
                count++;
            }
        }
    }
    //Se il conteggio è pari alla griglia, vuol dire che bisogna svuotare il fondo
    //e far scendere i blocchi di una riga
    if(count == GRID_X)
    {
        for(i = 0; i < objects->size; i++)
        {
            object_t *object = objects->array[i];
            for(j = 0; j < object->blocks->size; j++)
            {
                block_t *block = &object->blocks->array[j];
                if(block->pos_y == GRID_Y - 1)
                {
                    block->visible = false;
                } else
                {
                    block->pos_y += 1;
                }
            }
        }
        score++;
    }
}


bool isValidRotation(object_list_t objects, object_t obj, rotation_t rotation, direction_t direction)
{
    block_t block = obj.blocks->array[0], block2 = obj.blocks->array[1], block3 = obj.blocks->array[2];
    //Controlla per ogni direzione e rotazione se le nuove posizioni sono valide
    if(direction == Left)
    {
        if(rotation == Horizontal)
        {
            return (isValidPosition(block.pos_x - 2, block.pos_y + 2) &&
            isValidPosition(block2.pos_x - 1, block2.pos_y + 1) &&
            !isBlockThere(objects, block.pos_x - 2, block.pos_y + 2, obj) &&
            !isBlockThere(objects, block2.pos_x - 1, block2.pos_y + 1, obj));
        } else if(rotation == Vertical)
        {
            return (isValidPosition(block.pos_x, block.pos_y - 2) &&
            isValidPosition(block2.pos_x - 1, block2.pos_y - 1) &&
            isValidPosition(block3.pos_x - 2, block3.pos_y) &&
            !isBlockThere(objects, block.pos_x, block.pos_y - 2, obj) &&
            !isBlockThere(objects, block2.pos_x - 1, block2.pos_y - 1, obj) &&
            !isBlockThere(objects, block3.pos_x - 2, block3.pos_y, obj));
        }
    } else if(direction == Right)
    {
        if(rotation == Horizontal)
        {
            return (isValidPosition(block.pos_x, block.pos_y + 2) &&
            isValidPosition(block2.pos_x + 1, block2.pos_y + 1) &&
            isValidPosition(block3.pos_x + 2, block3.pos_y) &&
            !isBlockThere(objects, block.pos_x, block.pos_y + 2, obj) &&
            !isBlockThere(objects,block2.pos_x + 1, block2.pos_y + 1, obj) &&
            !isBlockThere(objects,block3.pos_x + 2, block3.pos_y, obj));
        } else if(rotation == Vertical)
        {
            return (isValidPosition(block.pos_x + 2, block.pos_y - 2) &&
            isValidPosition(block2.pos_x + 1, block2.pos_y - 1) &&
            !isBlockThere(objects,block.pos_x + 2, block.pos_y - 2, obj) &&
            !isBlockThere(objects,block2.pos_x + 1, block2.pos_y - 1, obj));
        }
    }
    return false;
}


void rotateObject(object_list_t objects, object_t *obj, direction_t direction)
{
    //Se è un quadrato oppure l'oggetto non è muovibile, non esiste rotazione
    if(obj->rotation == NoRotation || !obj->moveable) return;
    rotation_t newRotation = obj->rotation ^ 3;
    //Controlla se la rotazione voluta è valida per il determinato oggetto
    if(isValidRotation(objects, *obj, newRotation, direction))
    {
        block_t *block = &obj->blocks->array[0], *block2 = &obj->blocks->array[1], *block3 = &obj->blocks->array[2];
        //Per ogni direzione, muove i blocchi dell'oggetto in modo da ottenere la rotazione voluta
        if(direction == Left)
        {
            if(newRotation == Horizontal)
            {
                moveBlock(block, block->pos_x - 2, block->pos_y + 2);
                moveBlock(block2, block2->pos_x - 1, block2->pos_y + 1);
            } else if(newRotation == Vertical)
            {
                moveBlock(block, block->pos_x, block->pos_y - 2);
                moveBlock(block2, block2->pos_x - 1, block2->pos_y - 1);
                moveBlock(block3, block3->pos_x - 2, block3->pos_y);
            }
        } else if(direction == Right)
        {
            if(newRotation == Horizontal)
            {
                moveBlock(block, block->pos_x, block->pos_y + 2);
                moveBlock(block2, block2->pos_x + 1, block2->pos_y + 1);
                moveBlock(block3, block3->pos_x + 2, block3->pos_y);
            } else if(newRotation == Vertical)
            {
                moveBlock(block, block->pos_x + 2, block->pos_y - 2);
                moveBlock(block2, block2->pos_x + 1, block2->pos_y - 1);
            }
        }
        obj->rotation = newRotation;
    }
}


void handleKeyboard(object_list_t *objects, object_t *obj)
{
#if defined(_WIN32) || defined(_WIN64)
    int temp = getch();
    if (temp == 0 || temp == 224) {
        direction_t direction;
        switch(getch()) {
            /*case 72:
                direction = Top;
                break;*/
            case 75:
                direction = Left;
                break;
            case 77:
                direction = Right;
                break;
            case 80:
                direction = Bottom;
                break;
        }
        moveObject(objects, obj, direction);
    } else if(temp == 115) //Sinistra
        rotateObject(*objects, obj, Left);
    else if(temp == 100)
        rotateObject(*objects, obj, Right);
    else if(temp == 33)
        exit(0);
#elif
    printf("This function is not supported on any unix-like OS");
#endif
}


void clearConsole(){
    system(CLEAR_CONSOLE);
}


void applyChanges(wchar_t *grid_ptr, object_list_t *objects)
{
    initGrid(grid_ptr);
    drawObjects(grid_ptr, objects);
    #if DEBUG == false
    clearConsole();
    #endif
    drawFinalGrid(grid_ptr);
}


bool isEnded(object_list_t *objects)
{
    uint8_t i, j;
    for(i = 0; i < objects->size; i++)
    {
        object_t *object = objects->array[i];
        for(j = 0; j < object->blocks->size; j++)
        {
            block_t block = object->blocks->array[j];
            if(block.pos_y == 0) return true;
        }
    }
    return false;
}


void endGame(bool won)
{
    printf("Il gioco \x8A terminato.\n");
    if(won) printf("Hai vinto! Congratulazioni!");
    else printf("Hai perso. Mi dispiace :(");
}


object_t *randomObject(object_list_t *objects)
{
    if(isEnded(objects)) return NULL;
    object_t *obj = generateObject(rand()%GRID_X, 0, rand()%3);
    return obj;
}


object_t *generateObject(uint8_t position_x, uint8_t position_y, rotation_t rotation)
{
    object_t *object = calloc(1, sizeof(object_t));
    object->blocks = calloc(1, sizeof(block_list_t));
    switch (rotation) {
        case NoRotation:
            appendBlockList(object->blocks, *generateBlock(position_x, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 1, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x, position_y + 1, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 1, position_y + 1, true));
            break;
        case Horizontal:
            appendBlockList(object->blocks, *generateBlock(position_x, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 1, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x + 2, position_y, true));
            break;
        case Vertical:
            appendBlockList(object->blocks, *generateBlock(position_x, position_y, true));
            appendBlockList(object->blocks, *generateBlock(position_x, position_y + 1, true));
            appendBlockList(object->blocks, *generateBlock(position_x, position_y + 2, true));
            break;
    }
    object->rotation = rotation;
    object->moveable = true;
    return object;
}
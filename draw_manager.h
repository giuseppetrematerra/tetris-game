//
// Created by giuse on 24/01/2021.
//

#include <wchar.h>
#include "block_list.h"
#include "object_list.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TETRIS_DRAW_MANAGER_H
#define TETRIS_DRAW_MANAGER_H

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <Windows.h>
#define EMPTY_CHAR 32//32//176
#define BLOCK_CHAR 35//254//219
#define TOPLEFT_CHAR 218
#define TOPRIGHT_CHAR 191
#define BOTTOMLEFT_CHAR 192
#define BOTTOMRIGHT_CHAR 217
#define VERTICAL_MARGIN_CHAR 179
#define HORIZONTAL_MARGIN_CHAR 196
#define CLEAR_CONSOLE "cls"
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define EMPTY_CHAR L'\x2591'
#define BLOCK_CHAR L'\x2588'
#define TOPLEFT_CHAR L'\x256D'
#define TOPRIGHT_CHAR L'\x256E'
#define BOTTOMLEFT_CHAR L'\x2570'
#define BOTTOMRIGHT_CHAR L'\x256F'
#define VERTICAL_MARGIN_CHAR L'\x2502'
#define HORIZONTAL_MARGIN_CHAR L'\x2500'
#define CLEAR_CONSOLE "clear"
#endif

#define GRID_X 10
#define GRID_Y 10

#define GRID_MARGIN_X (GRID_X + 1)
#define GRID_MARGIN_Y (GRID_Y + 1)

#define FULL_GRID_X (GRID_MARGIN_X + 1)
#define FULL_GRID_Y (GRID_MARGIN_Y + 1)

#define DEBUG false

static int16_t score;
static object_t *actualObject;

/*
 * Questa funzione ha il compito di inizializzare la griglia con il carattere vuoto predefinito.
 * @input wchar_t grid_ptr: puntatore alla griglia che sarà poi inizializzata
 */
void initGrid(wchar_t*);
/*
 * Questa funzione ha il compito di aggiungere alla lista dei oggetti un oggetto.
 * Controlla prima se non è contenuto e se è possibile disegnarlo
 * @input object_list_t list: oggetti del gioco
 * @input object_t object: oggetto da aggiungere
 */
void tryAddObject(object_list_t*, object_t*);
/*
 * Questa funzione ha il compito di controllare se tra gli oggetti della lista
 * è presente un blocco di cordinate x e y ad esclusione dell'oggetto che viene preso
 * in considerazione. Questa funzione viene chiamata proprio per piazzare l'oggetto
 * prevenendo qualche collisione.
 * @input object_list_t objects: lista contenente tutti gli oggetti del gioco
 * @input uint8_t x: coordinata da confrontare con quella di ogni blocco degli oggetti presenti
 * @input uint8_t y: coordinata da confrontare con quella di ogni blocco degli oggetti presenti
 * @input object_t exclude: oggetto da escludere nel confronto delle coordinate
 * @output bool: true se viene trovato almeno un blocco, altrimenti false
 */
bool isBlockThere(object_list_t objects, uint8_t x, uint8_t y, object_t exclude);
/*
 * Questa funzione ha il compito di controllare se un oggetto può essere disegnato.
 * Non fa altro che controllare se tutti i suoi blocchi possono essere disegnati
 * @input object_list_t objects: lista contenente tutti gli oggetti del gioco
 * @input object_t obj: oggetto da controllare
 * @output bool: true se si può disegnare l'oggetto, altrimenti false
 */
bool canDrawObject(object_list_t objects, object_t obj);
/*
 * Questa funzione ha il compito di controllare se un blocco può essere disegnato.
 * Non fa altro che controllare se la posizione di un blocco è valida e se non collide con altri.
 * @input object_list_t objects: lista contenente tutti gli oggetti del gioco
 * @input block block: block da controllare
 * @input object_t exclude: oggetto da escludere nel controllo
 * @output bool: true se si può disegnare il blocco, altrimenti false
 */
bool canDrawBlock(object_list_t objects, block_t block, object_t exclude);
/*
 * Questa funzione ha il compito di controllare se delle coordinate sono valide
 * per essere poi utilizzate e posizionare un oggetto
 * @input uint8_t x: coordinata da controllare
 * @input uint8_t y: coordinata da controllare
 * @output bool: true se la posizione è valida, altrimenti false
 */
bool isValidPosition(uint8_t x, uint8_t y);
/*
 * Questa funzione ha il compito di controllare se un oggetto
 * può muoversi in una determina direzione
 * @input object_list_t objects: lista contenente tutti gli oggetti del gioco
 * @input object_t obj: oggetto da controllare
 * @input direction_t direction: direzione che si vuole controllare
 * @output bool: true se il movimento è valido, altrimenti false
 */
bool isValidMove(object_list_t objects, object_t obj, direction_t direction);
/*
 * Questa funzione ha il compito di controllare se un oggetto
 * può compiere una determinata rotazione in una determinata direzione
 * @input object_list_t objects: oggetti del gioco
 * @input object_t obj: oggetto da ruotare
 * @input rotation_t rotation: rotazione finale
 * @input direction_t direction: direzione finale
 */
bool isValidRotation(object_list_t objects, object_t obj, rotation_t rotation, direction_t direction);
/*
 * Questa funzione ha il compito di controllare se il gioco è terminato
 * Quindi se non c'è sufficiente spazio per poter piazzare un oggetto randomico
 * @input object_list_t objects: oggetti del gioco
 * @output bool: true se il gioco è terminato, altrimenti false
 */
bool isEnded(object_list_t *objects);
/*
 * Questa funzione ha il compito di disegnare l'effettivo blocco nella griglia
 * @input wchar_t grid_ptr: griglia del gioco
 * @input block_t block: blocco da disegnare
 */
void drawBlock(wchar_t *grid_ptr, block_t block);
/*
 * Questa funzione ha il compito di disegnare l'effettivo oggeto nella griglia
 * @input wchar_t grid_ptr: griglia del gioco
 * @input object_t obj: oggetto da disegnare
 */
void drawObject(wchar_t *grid_ptr, object_t obj);
/*
 * Questa funzione ha il compito di disegnare gli effetti oggetti nella griglia
 * @input wchar_t grid_ptr: griglia del gioco
 * @input object_list_t list: oggetti da disegnare
 */
void drawObjects(wchar_t *grid_ptr, object_list_t *list);
/*
 * Questa funzione ha il compito di stampare a video l'intera griglia in modo carino
 * @input wchar_t grid_ptr: griglia del gioco
 */
void drawFinalGrid(const wchar_t *grid_ptr);
/*
 * Questa funzione ha il compito di stampare a video l'intera griglia
 * @input wchar_t grid_ptr: griglia del gioco
 */
void printGrid(const wchar_t *grid_ptr);
/*
 * Questa funzione ha il compito di spostare un blocco ad una determinata posizione
 * @input block_t block: blocco da spostare
 * @input uint8_t pos_x: coordinata finale
 * @input uint8_t pos_y: coordinata finale
 */
void moveBlock(block_t *block, uint8_t pos_x, uint8_t pos_y);
/*
 * Questa funzione ha il compito di spostare un blocco verso una determinata direzione
 * @input block_t block: blocco da spostare
 * @input direction_t direction: direzione finale
 */
void moveBlockDirection(block_t *block, direction_t direction);
/*
 * Questa funzione ha il compito di spostare un oggetto verso una determinata direzione.
 * Controlla prima se tale oggetto colliderebbe con un altro
 * @input object_list_t objects: oggetti del gioco
 * @input object_t obj: oggetto da spostare
 * @input direction_t direction: direzione finale
 */
void moveObject(object_list_t *objects, object_t *obj, direction_t direction);
/*
 * Questa funzione ha il compito di controllare se l'ultima linea è stata completata
 * in modo da assegnare un punto al giocatore
 * @input object_list_t objects: oggetti del gioco
 */
void checkForLastRow(object_list_t *objects);
/*
 * Questa funzione ha il compito di far ruotare un determinato oggetto
 * La rotazione viene calcolata automaticamente tramite un'operazione logica di tipo XOR
 * @input object_list_t objects: oggetti del gioco
 * @input object_t obj: oggetto da ruotare
 * @input direction_t direction: direzione finale
 */
void rotateObject(object_list_t objects, object_t *obj, direction_t direction);
/*
 * Questa funzione ha il compito di controllare di gestire l'input dell'utente
 * Ed eventualmente eseguire il comando
 * @input object_list_t objects: oggetti del gioco
 * @input object_t obj: oggetto selezionato
 */
void handleKeyboard(object_list_t *objects, object_t *obj);
/*
 * Questa funzione ha il compito di cancellare la console in modo da
 * ottenere una schermata pulita e tranquilla per il gioco
 */
void clearConsole();
/*
 * Questa funzione ha il compito di aggiornare la griglia e di applicare eventuali
 * cambiamenti che sono avvenuti agli oggetti
 * @input wchar_t grid_ptr: griglia del gioco
 * @input object_list_t objects: oggetti del gioco
 */
void applyChanges(wchar_t *grid_ptr, object_list_t *objects);
/*
 * Questa funzione ha il compito di far sapere all'utnete che il gioco
 * è effettivamente terminato
 * @input bool won: indica se il gioco è stato vincente
 */
void endGame(bool won);
/*
 * Questa funzione ha il compito di generare un oggetto casuale e controllare
 * se il gioco è finito. In tal caso, ritornare un puntatore nullo in modo da
 * indicare al programma principale che il gioco è terminato.
 * @input object_list_t objects: oggetti del gioco
 * @output object_t: puntatore all'oggetto generato se il gioco è ancora attivo, altrimenti NULL
 */
object_t *randomObject(object_list_t *objects);
/*
 * Questa funzione ha il compito di generare un oggetto dati alcuni parametri come
 * le coordinate x,y e la rotazione
 * La rotazione viene calcolata automaticamente tramite un'operazione logica di tipo XOR
 * @input uint8_t position_x: coordinata dell'oggetto
 * @input uint8_t position_y: coordinata dell'oggetto
 * @input rotation_t direction: rotazione dell'oggetto
 * @output object_t: puntatore all'oggetto generato
 */
object_t* generateObject(uint8_t position_x, uint8_t position_y, rotation_t rotation);
#endif //TETRIS_DRAW_MANAGER_H

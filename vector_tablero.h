#ifndef VECTOR_TABLERO_H_INCLUDED
#define VECTOR_TABLERO_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "VentanaJuego.h"
#include "Errores.h"
//#include "configuracion.h"

//estructura de la carta
typedef enum{
    CARTA_TAPADA, //0
    CARTA_VOLTEADA, //1
    CARTA_ENCONTRADA //2
}estadoCarta;

typedef struct
{
    int idFigura; //id imagen cargada
    int puntos; //cuanto suma cada par
    estadoCarta estado; // tapada, volteada o encontrada
    SDL_Rect posicion; // posicion y tamaño en pantalla
    //set de figuras? para ver cual tiene
    bool hover;
}carta;

//tablero con tda vector
typedef struct
{
    carta* vec;
    int tam;
    int capacidad;
    int clicks;
    int primerclick;
    int segclick;

    int pares_encontrados;
    int racha;
    int bonus;

}juego;

juego* vector_crear(int cantidad);
void vector_prepararTablero(juego* v, int filas, int col, int setElegido);
void vector_mezclar(juego* v);
void vector_destruir(juego* v);

#endif // VECTOR_TABLERO_H_INCLUDED

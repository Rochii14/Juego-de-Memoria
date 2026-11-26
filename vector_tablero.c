#include "vector_tablero.h"
#include "juego.h"
#include <stdio.h>


juego* vector_crear(int cantCartas)
{
    // reservar memoria para la estructura controladora (tda)
    juego* v = malloc(sizeof(juego));
    if (!v) return NULL;

    // reservar memoria para el array de cartas que está adentro
    v->vec = malloc(sizeof(carta) * cantCartas);
    if (!v->vec) {
        free(v);
        return NULL;
    }

    v->tam = cantCartas;
    v->capacidad = cantCartas;
    v->clicks = 0;
    v->primerclick = -1;
    v->segclick = -1;

    return v;

}
void vector_mezclar(juego* v)
{
    carta temp;
    srand(time(NULL)); //de la biblio rand
    for(int i = v->tam -1; i > 0;i--){
        int j = rand() % i; //nro aleatorio
        //intercambiamos con la posicion random
        temp = v->vec[i];
        v->vec[i] = v->vec[j];
        v->vec[j] = temp;
    }
}
void vector_destruir(juego* v)
{
    if(v){
        //liberamos el vector y la estructura tda
        free(v->vec);
        free(v);
    }
}


void vector_prepararTablero(juego* v, int filas, int col, int setElegido)
{
    int totalCartas = filas * col;
    int cantPares = totalCartas / 2;
    int puntosAsignado;
    int index,id;
    //i arranca dependiento el set configurado en 0 o en 10.
    //if()...

    if (setElegido == 1){
        index = 0;
    }else{
        index = 10;
    }


    //INICIALIZO CARTAS
    for(int i = 0; i <cantPares; i++){
        //puntaje aleatorio para el primer par. Entre 10 y 100
        puntosAsignado = (rand() % 10 +1) * 10;
        id = index + i; //base + offset
        printf("ID figura: %d\n", id);


        //primera carta del par
        v->vec[i * 2].idFigura = id;
        v->vec[i * 2].puntos = puntosAsignado;
        v->vec[i * 2].estado = CARTA_TAPADA;
        v->vec[i * 2].hover = DESACTIVO;
        //segunda carta del par. mismo id y puntos
        v->vec[i * 2 + 1].idFigura = id;
        v->vec[i * 2 + 1].puntos = puntosAsignado;
        v->vec[i * 2 + 1].estado = CARTA_TAPADA;
        v->vec[i * 2 + 1].hover = DESACTIVO;

    }

    //mezclamos
    vector_mezclar(v);

    //posicion de cada carta. despues de mezclar

    int anchoCarta = 150;
    int altoCarta = 120;
    int espacio = 20;

    int anchoTablero = col * (anchoCarta + espacio) - espacio;
    int altoTablero = filas * (altoCarta + espacio) - espacio;

    int margenX = (ANCHO_VENTANA - anchoTablero) / 2;
    int margenY = (ALTO_VENTANA - altoTablero) / 2;

    for (int i = 0; i < totalCartas; i++) {
        int f = i / col;
        int c = i % col;

        v->vec[i].posicion.x = margenX + c * (anchoCarta + espacio);
        v->vec[i].posicion.y = margenY + f * (altoCarta + espacio);
        v->vec[i].posicion.w = anchoCarta;
        v->vec[i].posicion.h = altoCarta;
    }

}

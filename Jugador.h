#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "VentanaJuego.h"
#include <stdio.h>
#include "juego.h"
#include "hud.h"
#define TAM_NOMBRE 50

typedef struct Jugador
{
    int PuntajeAcum;
    char Nombre[TAM_NOMBRE] ; // es un arreglo hasta  49 caracteres y el \0.
    int posNombre;   //  posicion actual del nombre --->me sirve para usarlo de puntero al ir escribiendo y luego lo guardo en Nombre
}Jugador;

void iniciarIngresoNombre(Jugador *j);//inicializar jugador
void manejarEventosPedirNombre(SDL_Event* evento, EstadoJuego* estadoActual,recursos_graficos *r, Jugador *jugador,int *jugadorActual, int cantidadJugadores);
void renderizarIngresoNombre(VentanaGrafica *ventana, recursos_graficos *r, Jugador *jugador);


#endif // JUGADOR_H_INCLUDED

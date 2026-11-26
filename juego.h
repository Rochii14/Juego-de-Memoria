#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

// 1. Librerias del sistema primero
//#include <SDL2/SDL.h>
#include <stdbool.h>

// 2. Tus definiciones b�sicas
#include "Errores.h"
#include "VentanaJuego.h"
#include "vector_tablero.h"
#include "hud.h"
#include "Texto.h"
#include "sonido.h"

#define RECT(x, y, w, h) (&(SDL_Rect){x, y, w, h}) ///definir posicion de objeto para el 4 parametro de SDL_RenderCopy
#define TETRIS 0
#define MARIO 1
#define ACTIVO 1
#define DESACTIVO 0


#define max_tablero 20
#define max_figuras 8
#define max_set 2///AGUSSS
#define puntosxracha 5

typedef struct Jugador Jugador;

typedef struct
{
    SDL_Texture *tex_fondo; // backround
    SDL_Texture *tex_fondo_modojuego[max_set];//backround modojuego
    // menu principal
    tHUD *jugar;
    tHUD *config;
    tHUD *estadisticas;

    /* Men� configuraci�n */
    tHUD *nivel;          // 3x4 / 4x4 / 4x5
    tHUD *setFiguras;     // Set 1 / Set 2
    tHUD *cantJugadores;  // 1 / 2
    SDL_Texture* tex_logo[max_set];///AGUSSS
    SDL_Texture* tex_pointer;///AGUSSS
    tHUD *volver;
    tHUD* salir;

    /* IMAGENES DEL SET */
    SDL_Texture* tex_dorso; //parte de atras de la carta
    SDL_Texture* figuras[max_tablero]; //vector para imagenes, max 10 pares

    //puntaje
    //tHUD* puntaje_solitario;
    tHUD* racha;

    //puntaje
    tHUD* puntaje;
    tHUD* puntaje2;
    tHUD* turno;

    //GANASTE
    tHUD* victoria;
    SDL_Texture* tex_vida;///AGUSSS
    SDL_Texture* tex_vidaVacia;///AGUSSS

}recursos_graficos;
/*
typedef struct
{
    int clicks; // 0 - reposo | 1 - esperando segundo click | 2 - termino el turno
    bool bloqueado; //para evitar clicks en mensajes
}logica_juego;
*/

SDL_Texture* actualizar_texto(SDL_Renderer *renderer, void *datoAntiguo, void *datoNuevo, void *extra);
Error inicializar_recursos(VentanaGrafica *ventana, recursos_graficos* r_pres);
void renderizar_tablero(SDL_Renderer* renderer, juego* v, recursos_graficos* rec);
void renderizar_hover(SDL_Renderer* renderer, SDL_Rect* rect);
void manejarEventosJuego(SDL_Event* evento, juego* tableroJuego, recursos_graficos* rec_graficos, EstadoJuego* estadoActual);
void manejarClickTablero(int mx, int my, juego* tableroJuego);
int verificarMatch(juego* tableroJuego, Jugador* jugador, recursos_graficos* rec);
void actualizar_visual_puntaje(recursos_graficos* rec, Jugador* jugador);
void actualizar_racha_juego(recursos_graficos* rec, juego* tablero);
void actualizar_visual_2puntajes(recursos_graficos* rec, Jugador* j1, Jugador* j2);
void actualizar_visual_turno(recursos_graficos* rec, Jugador* jugadorActual);


#endif // JUEGO_H_INCLUDED

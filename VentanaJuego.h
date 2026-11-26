#ifndef VENTANAJUEGO_H_INCLUDED
#define VENTANAJUEGO_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdint.h>
#include "Errores.h"

#define ANCHO_VENTANA 1366
#define ALTO_VENTANA 768

typedef struct
{
    SDL_Window *ventana;                    // Puntero a la ventana
    SDL_Renderer *renderer;                 // Puntero al renderizador de SDL
    uint32_t anchoVentana;                  // Dimension horizontal de la ventana
    uint32_t altoVentana;                   // Dimension vertical  de la ventana
    uint8_t corriendo;
    TTF_Font *fuenteTTF;
}VentanaGrafica; //ESTRUCTURA DE LA VENTANA GRAFICA EN LA QUE CORRE EL JUEGO

typedef enum {
    ESTADO_PRESENTACION, //0
    ESTADO_JUEGO,   //1
    ESTADO_CONFIGURACION, ///esto es para manejo de pantallas no para la lógica que interfiere con el juego  2
    ESTADO_PEDIR_NOMBRE,//3
    ESTADO_SALIR, //4
    ESTADO_GANASTE, //5
    ESTADO_ESTADISTICAS
} EstadoJuego;         //para distinguir el flujo

Error InicializarVentana(VentanaGrafica * ventana);//inicalizar ventana
void graficos_borrar_pantalla(VentanaGrafica *ventana, const SDL_Color *color);
void  destruirVentana(VentanaGrafica * ventana);//destruir ventana

#endif // VENTANAJUEGO_H_INCLUDED

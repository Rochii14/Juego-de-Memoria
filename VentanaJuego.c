#include "VentanaJuego.h"
#include "Texto.h"
#include <stdio.h>

#define TAM_BUFFER 100

Error InicializarVentana(VentanaGrafica * ventana)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != TODO_OK) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERR_SDL;
    }

    Error err;
    char nombreVentana[TAM_BUFFER]="Memoria";
    ventana->anchoVentana = ANCHO_VENTANA;
    ventana->altoVentana = ALTO_VENTANA;

    // Crea la ventana del juego
    ventana->ventana = SDL_CreateWindow(nombreVentana,
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           ventana->anchoVentana,
                                           ventana->altoVentana,
                                           SDL_WINDOW_SHOWN);
    if (!ventana->ventana) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERR_SDL;
    }

    // Crea el renderer para la ventana
    ventana->renderer = SDL_CreateRenderer(ventana->ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!ventana->renderer) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERR_SDL;
    }
    SDL_SetRenderDrawBlendMode(ventana->renderer, SDL_BLENDMODE_BLEND); // Habilita la transparencia en el renderer

    ///FALTA INICIALIZAR SONIDO

     if ((err = texto_inicializar()) != TODO_OK) {
        return err;
    }
    ventana->fuenteTTF=texto_cargar_fuente("fnt/AlanSans.ttf",38);
    if (!ventana->fuenteTTF)
        {
        return ERR_SDL_TTF;
        }
    ventana->corriendo = 1;
    return err;
}
void  destruirVentana(VentanaGrafica * ventana)
{
    if (ventana->fuenteTTF)
       {
          texto_destruir_fuente(ventana->fuenteTTF);
       }

    texto_finalizar();
    if (ventana->renderer)
        {SDL_DestroyRenderer(ventana->renderer);}


    if (ventana->ventana)
       {
           SDL_DestroyWindow(ventana->ventana);
       }

    SDL_Quit();
}
void graficos_borrar_pantalla(VentanaGrafica *ventana, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(ventana->renderer, color->r, color->g, color->b, color->a);
    SDL_RenderClear(ventana->renderer);
}


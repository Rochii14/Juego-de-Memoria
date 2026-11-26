#ifndef IMAGEN_H_INCLUDED
#define IMAGEN_H_INCLUDED

#include "juego.h"
//#include "VentanaJuego.h"
#include <SDL2/SDL_image.h>


typedef enum
{
    //SET 1 : 0 - 9
    F0,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    //SET 2 : del 10 - 19
    E0,
    E1,
    E2,
    E3,
    E4,
    E5,
    E6,
    E7,
    E8,
    E9
}id_figuras;


Error imagen_inicializar();
SDL_Texture * imagen_cargar (const char *ruta, VentanaGrafica * ventana);
void imagen_destruir( SDL_Texture * imagen_texture);
void imagen_finalizar();
void liberar_imagenes(recursos_graficos* r_pres);

#endif // IMAGEN_H_INCLUDED

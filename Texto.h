#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED

#include "VentanaJuego.h"
#include "Errores.h"
#include <stdint.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>




Error texto_inicializar();
TTF_Font* texto_cargar_fuente(const char *ruta, uint32_t tamLetra);
SDL_Texture* texto_crear_textura(VentanaGrafica *ventana, const char* texto, SDL_Color color);
void texto_destruir_fuente(TTF_Font *fuente);
void texto_finalizar();
#endif // TEXTO_H_INCLUDED

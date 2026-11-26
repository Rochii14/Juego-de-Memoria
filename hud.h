#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

//#include <SDL2/SDL.h>
#include <stdint.h>
#include "Errores.h"
#include "VentanaJuego.h"


// dinamica para la actualizacion
typedef SDL_Texture* (*tActualizarHUD)(SDL_Renderer*, void*, void*, void*);
typedef void (*tDestruirHUD)(void*);

typedef struct sHUD tHUD;

tHUD* hud_inicializar(SDL_Renderer *renderer, int32_t posX, int32_t posY, void *dato, size_t tamDato, void *extra, tActualizarHUD actualizar, tDestruirHUD destruir);
void hud_dibujar(const tHUD *hud);
void hud_obtener_rectangulo(const tHUD *hud, SDL_Rect *rect);
Error hud_actualizar_dato(tHUD *hud, void *datoNuevo);
void hud_destruir(tHUD *hud);


#endif // HUD_H_INCLUDED

#ifndef PRESENTACION_H_INCLUDED
#define PRESENTACION_H_INCLUDED
#include "VentanaJuego.h"
#include "hud.h"
#include "configuracion.h"
#include "vector_tablero.h"



void manejarEventosPresentacion(SDL_Event *evento, EstadoJuego *EstadoActual,recursos_graficos* r_pres, config_logica* config, juego** tableroJuego);
void renderizarPresentacion(VentanaGrafica *ventana, SDL_Texture *texPresentacion);
void dibujar_fondo_hud(SDL_Renderer* renderer, const tHUD* hud, SDL_Color* color,int padding );
void renderizar_boton_opcion(SDL_Renderer* renderer, tHUD* hud, int esSeleccionado);


#endif // PRESENTACION_H_INCLUDED

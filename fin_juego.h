#ifndef FIN_JUEGO_H_INCLUDED
#define FIN_JUEGO_H_INCLUDED

#include "Jugador.h"
#include "configuracion.h"

void eventos_finjuego(SDL_Event* evento,EstadoJuego* estadoActual, recursos_graficos* r_pres);
void mensaje_victoria(config_logica* config, Jugador* j1, Jugador* j2, recursos_graficos* r_pres);


#endif // FIN_JUEGO_H_INCLUDED

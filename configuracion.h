#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

#include <stdbool.h>
#include "VentanaJuego.h"
#include <stdio.h>
#include "hud.h"
#include "juego.h"

typedef struct
{
    bool mostrarconfig;
    int filas;
    int col;
    int setElegido;
    int cantJugadores;
}config_logica;

void manejarEventosConfig(SDL_Event* evento, EstadoJuego* estadoActual,config_logica* config, recursos_graficos *r);
void renderizarConfiguracion(VentanaGrafica *ventana,recursos_graficos *r);
bool cargarUltimaConfiguracion(config_logica* config);
void actualizar_textoCONFIG(recursos_graficos* r, config_logica* config);
#endif // CONFIGURACION_H_INCLUDED

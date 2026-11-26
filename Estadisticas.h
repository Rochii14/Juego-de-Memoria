#ifndef ESTADISTICAS_H_INCLUDED
#define ESTADISTICAS_H_INCLUDED
#include "TDA_Vector.h"
#include "VentanaJuego.h"
#include "juego.h"

typedef struct {
    SDL_Texture* titulo;
    SDL_Texture* jugadores[5];
    int cantidad;
} RankingRender;

void manejarEventosEstadisticas(SDL_Event *evento, EstadoJuego *EstadoActual,recursos_graficos* r_pres);
void prepararRankingTexturas(VentanaGrafica* ventana, t_Vector* ranking, RankingRender* rr);
void renderizarRanking(VentanaGrafica* ventana, RankingRender* rr);
void destruirRankingTexturas(RankingRender* rr);

#endif // ESTADISTICAS_H_INCLUDED

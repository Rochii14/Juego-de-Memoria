#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Estadisticas.h"
#include "TDA_Vector.h"
#include "Texto.h"
#include "Jugador.h"

void manejarEventosEstadisticas(SDL_Event *evento, EstadoJuego *EstadoActual,recursos_graficos* r_pres)
{
        if(evento->type == SDL_MOUSEBUTTONDOWN){
        int mx = evento->button.x;
        int my = evento->button.y;
        SDL_Rect rect;
        hud_obtener_rectangulo(r_pres->volver, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {

            *EstadoActual = ESTADO_PRESENTACION;
            return;
        }
        hud_obtener_rectangulo(r_pres->salir, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
        {
            *EstadoActual = ESTADO_SALIR;
        }
    }

}
void prepararRankingTexturas(VentanaGrafica* ventana, t_Vector* ranking, RankingRender* rr)
{
    SDL_Color blanco = {255,255,255,255};

    rr->titulo = texto_crear_textura(ventana, "Top 5 jugadores", blanco);

    int cant = (ranking->ce > 5) ? 5 : ranking->ce;
    rr->cantidad = cant;

    char buffer[100];
    char* base = (char*)ranking->vec;

    for(int i = 0; i < cant; i++)
    {
        Jugador* j = (Jugador*)(base + i * ranking->tamElem);

        sprintf(buffer, "%3d. %-10s %5d", i+1, j->Nombre, j->PuntajeAcum);

        rr->jugadores[i] = texto_crear_textura(ventana, buffer, blanco);
    }
}

void renderizarRanking(VentanaGrafica* ventana,  RankingRender* rr)
{
    int altoFila = 60;
    int yInicioAbajo = ventana->altoVentana - (rr->cantidad * altoFila) - 100;
    int anchoPanel = 500;
    int altoPanel  = rr->cantidad * altoFila + 40;

    SDL_Rect fondo = {
        ventana->anchoVentana/2 - anchoPanel/2,
        yInicioAbajo - 20,
        anchoPanel,
        altoPanel
    };

    SDL_SetRenderDrawBlendMode(ventana->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ventana->renderer, 30,30,30,150);
    SDL_RenderFillRect(ventana->renderer, &fondo);

    // -------- TITULO --------
    if(rr->titulo)
    {
        int w, h;
        SDL_QueryTexture(rr->titulo, NULL, NULL, &w, &h);

        int x = (ventana->anchoVentana / 2) - (w / 2);
        int y = 150;

        SDL_Rect dstTitulo = { x, y, w, h };
        SDL_RenderCopy(ventana->renderer, rr->titulo, NULL, &dstTitulo);
    }

    // -------- JUGADORES --------
    for(int i = 0; i < rr->cantidad; i++)
    {
        if(rr->jugadores[i])
        {
            int w, h;
            SDL_QueryTexture(rr->jugadores[i], NULL, NULL, &w, &h);

            int x = (ventana->anchoVentana / 2) - (w / 2);

            SDL_Rect dst = {  x, yInicioAbajo + i * altoFila, w, h };

            SDL_RenderCopy(ventana->renderer, rr->jugadores[i], NULL, &dst);
        }
    }
}
void destruirRankingTexturas(RankingRender* rr)
{
    if(rr->titulo)
        SDL_DestroyTexture(rr->titulo);

    for(int i = 0; i < rr->cantidad; i++)
    {
        if(rr->jugadores[i])
            SDL_DestroyTexture(rr->jugadores[i]);
    }
}

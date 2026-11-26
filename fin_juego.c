#include "fin_juego.h"

void eventos_finjuego(SDL_Event* evento,EstadoJuego* estadoActual, recursos_graficos* r_pres)
{
    if(evento->type == SDL_MOUSEBUTTONDOWN)
    {
        int mx = evento->button.x;
        int my = evento->button.y;
        SDL_Rect rect;

        hud_obtener_rectangulo(r_pres->volver, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {

            *estadoActual = ESTADO_PRESENTACION;
            return;
        }
        hud_obtener_rectangulo(r_pres->salir, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
        {
            *estadoActual = ESTADO_SALIR;
        }


    }

}
void mensaje_victoria(config_logica* config, Jugador* j1, Jugador* j2, recursos_graficos* r_pres)
{
    // PREPARAMOS EL MENSAJE DE VICTORIA SEGÚN EL MODO
    char mensajeVictoria[100];
    if(config->cantJugadores == 2)
    {
        // Comparamos puntajes para ver quién ganó o si hubo empate
        if(j1->PuntajeAcum > j2->PuntajeAcum)
            sprintf(mensajeVictoria, " ¡Gano '%s' con %d! ", j1->Nombre, j1->PuntajeAcum);
        else if(j2->PuntajeAcum > j1->PuntajeAcum)
            sprintf(mensajeVictoria, " ¡Gano '%s' con %d! ", j2->Nombre, j2->PuntajeAcum);
        else
            sprintf(mensajeVictoria, " ¡EMPATE TECNICO! %d ", j1->PuntajeAcum);
    }
    else
    {
        sprintf(mensajeVictoria, " %10s TERMINASTE EL JUEGO! PUNTOS: %d ", j1->Nombre, j1->PuntajeAcum);
    }
    // Actualizamos el HUD de "ganaste" con el texto personalizado
    hud_actualizar_dato(r_pres->victoria, mensajeVictoria);
}

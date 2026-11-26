#include <stdio.h>
#include "Presentacion.h"
#include "VentanaJuego.h"
#include "Imagen.h"

void manejarEventosPresentacion(SDL_Event *evento, EstadoJuego *EstadoActual,recursos_graficos* r_pres, config_logica* config, juego** tableroJuego)
{
    if(evento->type == SDL_MOUSEBUTTONDOWN){
        int mx = evento->button.x;
        int my = evento->button.y;
        SDL_Rect rect;

        hud_obtener_rectangulo(r_pres->salir, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
        {
            *EstadoActual = ESTADO_SALIR;
        }


        //PREGUNTAR POR EL BOTÓN PRINCIPAL (Toggle)
        //click en configuracion?
        hud_obtener_rectangulo(r_pres->config, &rect);//obtengo posicion del rectangulo del boton config
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {

            printf("Menu abierto:\n");
            *EstadoActual = ESTADO_CONFIGURACION;
            return;
        }

        //click en estaditicas?
        hud_obtener_rectangulo(r_pres->estadisticas, &rect);//obtengo posicion del rectangulo del boton config
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {

            printf("Estaditicas\n");
            *EstadoActual = ESTADO_ESTADISTICAS;
            return;
        }

        //vemos si hizo click en volver?
        hud_obtener_rectangulo(r_pres->volver, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {

            *EstadoActual = ESTADO_PEDIR_NOMBRE;
            return;
        }

        hud_obtener_rectangulo(r_pres->jugar, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
        {
            //CLICK EN JUGAR
            //recalculo las filas y columnas para cuando cambia de tablero
            int total = config->filas * config->col;

            //destruyo si hay un vector viejo
            if(*tableroJuego){
                vector_destruir(*tableroJuego);
                *tableroJuego = NULL;
            }

            //creo tablero nuevo
            *tableroJuego = vector_crear(total);
            if (!*tableroJuego) {
                printf("ERROR sin memoria\n");
                return ;
            }
            //Preparar
            vector_prepararTablero(*tableroJuego,config->filas,config->col, config->setElegido);
            //flujo pedir nombre
            *EstadoActual = ESTADO_PEDIR_NOMBRE;
        }

    }
}
void renderizarPresentacion(VentanaGrafica *ventana, SDL_Texture *texPresentacion) {
    SDL_RenderClear(ventana->renderer);
    SDL_RenderCopy(ventana->renderer, texPresentacion, NULL, NULL);
    SDL_RenderPresent(ventana->renderer);
}

void dibujar_fondo_hud(SDL_Renderer* renderer, const tHUD* hud, SDL_Color* color,int padding )
{
    SDL_Rect rectTexto;
    hud_obtener_rectangulo(hud, &rectTexto); //obtenemos la textura y posicion

    //creo el rectangulo + grande q el texto con el padding
    SDL_Rect rectFondo = {
        rectTexto.x - padding,
        rectTexto.y - padding,
        rectTexto.w + (padding *2),
        rectTexto.h + (padding * 2),
    };

    //transparencia (blendmode es un entero de blendmode)
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    //color
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

    //dibujamos fondo
    SDL_RenderFillRect(renderer, &rectFondo);

    //borde mas claro
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rectFondo);

}
void renderizar_boton_opcion(SDL_Renderer* renderer, tHUD* hud, int esSeleccionado)
{
    SDL_Color colorSeleccionado = {0, 200, 0, 255}; // Verde
    SDL_Color colorNormal = {50, 50, 50, 200};     // Gris

    // Usamos el color según el estado
    SDL_Color* colorFinal = esSeleccionado ? &colorSeleccionado : &colorNormal;



    dibujar_fondo_hud(renderer, hud, colorFinal, 10);
    hud_dibujar(hud);
}

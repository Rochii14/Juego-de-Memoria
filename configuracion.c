#include "configuracion.h"
#include <stdlib.h>
#include <stdio.h>


void manejarEventosConfig(SDL_Event* evento, EstadoJuego* estadoActual,config_logica* config, recursos_graficos *r)
{


if (evento->type != SDL_MOUSEBUTTONDOWN)
        return;

    int mx = evento->button.x;
    int my = evento->button.y;
    SDL_Rect rect;

    hud_obtener_rectangulo(r->salir, &rect);
    if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
    {
        *estadoActual = ESTADO_SALIR;
    }

    //BOTÓN NIVEL
        hud_obtener_rectangulo(r->nivel, &rect);
    if (mx >= rect.x && mx <= rect.x + rect.w &&
        my >= rect.y && my <= rect.y + rect.h)
    {
        printf("click en nivel!\n");
        if (config->filas == 3 && config->col == 4) {
            config->filas = 4;
            config->col   = 4;
            hud_actualizar_dato(r->nivel, "TABLERO: 4x4");
            printf("click en 4x4\n");
        }
        else if (config->filas == 4 && config->col == 4) {
            config->filas = 4;
            config->col   = 5;
            hud_actualizar_dato(r->nivel, "TABLERO: 4x5");
            printf("click en 4x5\n");
        }
        else {
            config->filas = 3;
            config->col   = 4;
            hud_actualizar_dato(r->nivel, "TABLERO: 3x4");
            printf("click en 3x4\n");
        }

    }

        printf("Nivel seleccionado: %dx%d\n", config->filas, config->col);



    //BOTÓN SET DE FIGURAS
   hud_obtener_rectangulo(r->setFiguras, &rect);
    if (mx >= rect.x && mx <= rect.x + rect.w &&
        my >= rect.y && my <= rect.y + rect.h)
    {
        printf("click en set %d\n", config->setElegido);
        if (config->setElegido == 1) {
            config->setElegido = 2;
            hud_actualizar_dato(r->setFiguras, "SET: 2");
            printf("click en set %d\n", config->setElegido);
        } else {
            config->setElegido = 1;
            hud_actualizar_dato(r->setFiguras, "SET: 1");
            printf("click en set %d\n", config->setElegido);
        }

    }
      // BOTÓN CANTIDAD JUGADORES
    hud_obtener_rectangulo(r->cantJugadores, &rect);
    if (mx >= rect.x && mx <= rect.x + rect.w &&
        my >= rect.y && my <= rect.y + rect.h)
    {
        if (config->cantJugadores == 1) {
            config->cantJugadores = 2;
            hud_actualizar_dato(r->cantJugadores, "JUGADORES: 2");
        } else {
            config->cantJugadores = 1;
            hud_actualizar_dato(r->cantJugadores, "JUGADORES: 1");
        }

    }


       //BOTÓN VOLVER
   hud_obtener_rectangulo(r->volver, &rect);
    if (mx >= rect.x && mx <= rect.x + rect.w &&
        my >= rect.y && my <= rect.y + rect.h)
    {
        *estadoActual = ESTADO_PRESENTACION;
        config->mostrarconfig = false;
        printf("jugadores: %d\t cant col:%d \t cant filas: %d \t, set:%d\n",config->cantJugadores,config->col,config->filas,config->setElegido);
        /// guardar en un archivo
        FILE *archivoConfiguracion= fopen("Configuracion.txt","a"); //"a" = crear si no existe + escribir al final siempre
        if(!archivoConfiguracion)
        {
            puts("Error de apertura de archivos.\n");
            return;
        }
        fprintf(archivoConfiguracion,"%d %d %d %d\n",config->cantJugadores,config->col,config->filas,config->setElegido);
        fclose(archivoConfiguracion);
        puts("archivo: Configuracion creado\n");
        return;
    }

    //BOTON JUGAR
    hud_obtener_rectangulo(r->jugar, &rect);
    if (mx >= rect.x && mx <= rect.x + rect.w &&
        my >= rect.y && my <= rect.y + rect.h)
    {
        *estadoActual = ESTADO_PEDIR_NOMBRE;
        printf("jugadores: %d\t cant col:%d \t cant filas: %d \t, set:%d\n",config->cantJugadores,config->col,config->filas,config->setElegido);
        /// guardar en un archivo
        FILE *archivoConfiguracion= fopen("Configuracion.txt","a"); //"a" = crear si no existe + escribir al final siempre
        if(!archivoConfiguracion)
        {
            puts("Error de apertura de archivos.\n");
            return;
        }
        fprintf(archivoConfiguracion,"%d %d %d %d\n",config->cantJugadores,config->col,config->filas,config->setElegido);
        fclose(archivoConfiguracion);
        puts("archivo: Configuracion creado\n");
        printf("Estado actual: %d", *estadoActual);
        return;
    }

}
void renderizarConfiguracion(VentanaGrafica *ventana,recursos_graficos *r)
{
    SDL_RenderCopy(
        ventana->renderer,
        r->tex_fondo,
        NULL,
        NULL
    );

    hud_dibujar(r->nivel);
    hud_dibujar(r->setFiguras);
    hud_dibujar(r->cantJugadores);
    hud_dibujar(r->volver);
}
bool cargarUltimaConfiguracion(config_logica* config)
{
    FILE* archivo = fopen("Configuracion.txt", "r");
    if (!archivo)
        return false; // no existe archivo → usar default

    int cantJug, col, filas, set;
    int leidos;
    bool hayDatos = false;

    // Leo hasta el final para quedarme con la última línea
    while ((leidos = fscanf(archivo, "%d %d %d %d",
                            &cantJug, &col, &filas, &set)) == 4)
    {
        config->cantJugadores = cantJug;
        config->col = col;
        config->filas = filas;
        config->setElegido = set;
        hayDatos = true;
    }
    printf("\n configuracion seteada: %d %d %d %d", config->cantJugadores,config->col,config->filas,config->setElegido);

    fclose(archivo);

    return hayDatos; // true si había al menos una config válida
}

void actualizar_textoCONFIG(recursos_graficos* r, config_logica* config)
{
    char buffer[50];

    sprintf(buffer, "TABLERO: %dx%d", config->filas, config->col);
    hud_actualizar_dato(r->nivel, buffer);

    sprintf(buffer, "SET: %d", config->setElegido);
    hud_actualizar_dato(r->setFiguras, buffer);

    sprintf(buffer, "JUGADORES: %d", config->cantJugadores);
    hud_actualizar_dato(r->cantJugadores, buffer);
}

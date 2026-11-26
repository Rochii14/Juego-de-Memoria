/*
Apellido: Guevara, Agostina
DNI: 42283585
Entrega: Si

Apellido: Eguia Camejo, Agustin
DNI: 44870705
Entrega: Si

Apellido: Valdevieso, Rocio Elizabeth
DNI: 44588998
Entrega:Si

Apellido: Arriola , Santiago Ezequiel
DNI: 41743980
Entrega:Si
*/




#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "hud.h"
#include "Presentacion.h"
#include "Imagen.h"
#include "Texto.h"
#include "Jugador.h"
#include "Errores.h"
#include "juego.h"
#include "TDA_Vector.h"
#include "Estadisticas.h"
#include "fin_juego.h"


int main(int argc, char* argv[])
{
    VentanaGrafica ventana;
    recursos_graficos r_pres;
    int error;
    error = inicializar_recursos(&ventana, &r_pres);
    if (error != TODO_OK) {
        printf("Error al inicializar recursos: %d\n", error);
        return -1;
    }
    sonidos_inicializar();
    sonidos_cargar();

    SDL_Event evento;
    int banJugador = 0;
    EstadoJuego estadoActual = ESTADO_PRESENTACION;
    EstadoJuego estadoAnterior = ESTADO_PRESENTACION;
    config_logica config = {true,3,4,1,1}; // valores por defecto

    if (cargarUltimaConfiguracion(&config))
    {
        printf("Configuracion cargada desde archivo.\n");
        actualizar_textoCONFIG(&r_pres,&config );
    }
    else
    {
        printf("Usando configuracion por defecto.\n");
    }

    Jugador Jugador1, Jugador2;
    iniciarIngresoNombre(&Jugador1);
    iniciarIngresoNombre(&Jugador2);

    juego* tableroJuego = NULL;

    t_Vector vecJugadores;
    int rankingCargado = 0;
    RankingRender rankingRender = {0};

    Jugador* jugadorActual = &Jugador1;
    actualizar_visual_turno(&r_pres, jugadorActual);

    Uint32 frameStart;
    int frameTime;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    while (ventana.corriendo)
    {
        frameStart = SDL_GetTicks();
        // =============================
        // 1) MANEJO DE EVENTOS
        // =============================
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
                ventana.corriendo = 0;
            switch (estadoActual)
            {
                case ESTADO_PRESENTACION:
                    manejarEventosPresentacion(&evento, &estadoActual, &r_pres, &config, &tableroJuego);
                    break;
                case ESTADO_CONFIGURACION:
                    manejarEventosConfig(&evento, &estadoActual, &config, &r_pres);
                    break;
                case ESTADO_PEDIR_NOMBRE:
                    if (banJugador == 0)
                        manejarEventosPedirNombre(&evento, &estadoActual, &r_pres, &Jugador1, &banJugador, config.cantJugadores);
                    else
                        manejarEventosPedirNombre(&evento, &estadoActual, &r_pres, &Jugador2, &banJugador, config.cantJugadores);
                    break;
                case ESTADO_JUEGO:
                    if (tableroJuego)
                        manejarEventosJuego(&evento, tableroJuego, &r_pres, &estadoActual);
                    break;
                case ESTADO_ESTADISTICAS:
                    manejarEventosEstadisticas(&evento,&estadoActual,&r_pres);
                    break;
                case ESTADO_SALIR:
                    ventana.corriendo = 0;
                    break;
                case ESTADO_GANASTE:
                    eventos_finjuego(&evento, &estadoActual, &r_pres);
                    break;
                 default:
                    break;
            }
        }
        // 2) CREAR TABLERO AL ENTRAR A JUEGO
        if (estadoActual != estadoAnterior)
        {
            switch (estadoActual)
            {
                case ESTADO_PRESENTACION:
                    SDL_StopTextInput();
                    if(estadoAnterior == ESTADO_JUEGO)
                        apagar_musica();
                    break;

                case ESTADO_CONFIGURACION:
                    SDL_StopTextInput();
                    break;

                case ESTADO_PEDIR_NOMBRE:
                    banJugador = 0;
                    iniciarIngresoNombre(&Jugador1);
                    iniciarIngresoNombre(&Jugador2);
                    SDL_StartTextInput();
                    break;
                case ESTADO_SALIR:
                    ventana.corriendo = 0;
                    break;
                 case ESTADO_ESTADISTICAS:
                   {
                       if (rankingCargado)
                        {vectorJugadoresDestruir(&vecJugadores);}

                        vectorJugadoresCrear(&vecJugadores);
                        cargarVectorDeArchivoTxT(&vecJugadores);
                        prepararRankingTexturas(&ventana, &vecJugadores, &rankingRender);
                        rankingCargado = 1;
                        break;
                   }
                case ESTADO_JUEGO:
                {
                    SDL_StopTextInput();
                    int total = config.filas * config.col;
                    if (tableroJuego)
                        vector_destruir(tableroJuego);

                    tableroJuego = vector_crear(total);
                    vector_prepararTablero(tableroJuego, config.filas, config.col, config.setElegido);
                    Jugador1.PuntajeAcum = 0;
                    Jugador2.PuntajeAcum = 0;
                    tableroJuego->racha = 0;
                    jugadorActual = &Jugador1;
                    tableroJuego->pares_encontrados = 0;
                    actualizar_visual_puntaje(&r_pres, &Jugador1);
                    actualizar_racha_juego(&r_pres, tableroJuego);
                    reproducir_musica();
                    break;
                }
                case ESTADO_GANASTE:
                {
                    apagar_musica();
                    reproducir_win();
                    break;
                }

                default:
                    break;
            }
        }
        estadoAnterior = estadoActual;
        // =============================
        // 3) RENDER
        // =============================
        graficos_borrar_pantalla(&ventana, &(SDL_Color){0,0,0,255});
            // -------- PRESENTACION --------
            if (estadoActual == ESTADO_PRESENTACION)
            {
                SDL_RenderCopy(ventana.renderer, r_pres.tex_fondo, NULL, NULL);
                SDL_Color colorFondo = {0,0,0,180};
                dibujar_fondo_hud(ventana.renderer, r_pres.jugar, &colorFondo, 20);
                hud_dibujar(r_pres.jugar);
                dibujar_fondo_hud(ventana.renderer, r_pres.config, &colorFondo, 10);
                hud_dibujar(r_pres.config);
                dibujar_fondo_hud(ventana.renderer, r_pres.estadisticas, &colorFondo, 10);
                hud_dibujar(r_pres.estadisticas);
                renderizar_boton_opcion(ventana.renderer, r_pres.salir,0);
            }
            // -------- CONFIGURACION --------
            else if (estadoActual == ESTADO_CONFIGURACION)
            {
                renderizarConfiguracion(&ventana, &r_pres);
                actualizar_textoCONFIG(&r_pres,&config );
                renderizar_boton_opcion(ventana.renderer, r_pres.nivel, 0);
                renderizar_boton_opcion(ventana.renderer, r_pres.setFiguras, 0);
                renderizar_boton_opcion(ventana.renderer, r_pres.cantJugadores, 0);
                renderizar_boton_opcion(ventana.renderer, r_pres.volver, 0);
                renderizar_boton_opcion(ventana.renderer, r_pres.jugar, 0);
                renderizar_boton_opcion(ventana.renderer, r_pres.salir,0);
                SDL_RenderCopy(ventana.renderer, r_pres.tex_logo[TETRIS], NULL, RECT(956, 250, 256, 256));
                SDL_RenderCopy(ventana.renderer, r_pres.tex_logo[MARIO], NULL, RECT(150, 250, 256, 256));
                if(config.setElegido == 2 )
                    SDL_RenderCopy(ventana.renderer, r_pres.tex_pointer, NULL, RECT(956, 100, 256, 256)); ///si no coincide se switchea
                else
                    SDL_RenderCopy(ventana.renderer, r_pres.tex_pointer, NULL, RECT(150, 100, 256, 256));
                }

            // -------- PEDIR NOMBRE --------
            else if (estadoActual == ESTADO_PEDIR_NOMBRE)
            {
                if (banJugador == 0)
                    renderizarIngresoNombre(&ventana, &r_pres, &Jugador1);
                else
                    renderizarIngresoNombre(&ventana, &r_pres, &Jugador2);
                renderizar_boton_opcion(ventana.renderer, r_pres.volver, 0);
                renderizar_boton_opcion(ventana.renderer, r_pres.jugar, 0);
            }
            // -------- JUEGO --------
            else if (estadoActual == ESTADO_JUEGO)
            {
                if(config.setElegido == 1)
                    SDL_RenderCopy(ventana.renderer, r_pres.tex_fondo_modojuego[TETRIS], NULL, NULL);
                else
                    SDL_RenderCopy(ventana.renderer, r_pres.tex_fondo_modojuego[MARIO], NULL, NULL);
                renderizar_tablero(ventana.renderer, tableroJuego, &r_pres);
                //racha??
                if(tableroJuego->racha > 1)
                    renderizar_boton_opcion(ventana.renderer,r_pres.racha,0);
                if(config.cantJugadores == 1){
                    renderizar_boton_opcion(ventana.renderer, r_pres.puntaje, 1);
                }else{
                //modo competitivo, los muestro
                renderizar_boton_opcion(ventana.renderer, r_pres.puntaje,1);
                renderizar_boton_opcion(ventana.renderer, r_pres.puntaje2,1);
                renderizar_boton_opcion(ventana.renderer, r_pres.turno,1);
                }
                if(tableroJuego != NULL && tableroJuego->clicks == 2)
                {
                    SDL_RenderPresent(ventana.renderer); // dibuja las 2 dadas vuelta
                    SDL_Delay(500);                      // espera para verlas
                    int huboMatch = verificarMatch(tableroJuego, jugadorActual, &r_pres);// compara
                    if(config.cantJugadores == 2 && !huboMatch)
                    {
                        if(jugadorActual == &Jugador1)
                            jugadorActual = &Jugador2;
                        else
                            jugadorActual = &Jugador1;
                        actualizar_visual_turno(&r_pres, jugadorActual);
                    }
                    if(tableroJuego->pares_encontrados == (tableroJuego->tam /  2))
                    {//FIN JUEGO
                        printf("\n GANASTE!");
                        mensaje_victoria(&config, &Jugador1,&Jugador2, &r_pres);
                        //use el vector declarado al principio
                        if (rankingCargado) {
                            vectorJugadoresDestruir(&vecJugadores);
                        }
                        vectorJugadoresCrear(&vecJugadores);
                        cargarVectorDeArchivoTxT(&vecJugadores);
                        // insertamos ambos jugadores en la estadistica
                        vectorJugadoresInsertarOrdenado(&vecJugadores, &Jugador1, sizeof(Jugador), cmpJugador);
                        if(config.cantJugadores == 2) {
                            vectorJugadoresInsertarOrdenado(&vecJugadores, &Jugador2, sizeof(Jugador), cmpJugador);
                        }
                        rankingGuardar(&vecJugadores);

                        destruirRankingTexturas(&rankingRender);
                        prepararRankingTexturas(&ventana, &vecJugadores, &rankingRender);

                        rankingCargado =1;
                        renderizar_boton_opcion(ventana.renderer, r_pres.salir,0);
                        estadoActual = ESTADO_GANASTE;
                    }
                }
                //muestro puntos
                actualizar_visual_2puntajes(&r_pres, &Jugador1, &Jugador2);
                actualizar_visual_turno(&r_pres, jugadorActual);
                renderizar_boton_opcion(ventana.renderer, r_pres.volver, 0);
            }
            else if (estadoActual == ESTADO_GANASTE){
                if(config.setElegido == 2 ){
                    SDL_RenderCopy(ventana.renderer, r_pres.tex_fondo_modojuego[MARIO], NULL, NULL);
                }
                else{
                    SDL_RenderCopy(ventana.renderer, r_pres.tex_fondo_modojuego[TETRIS], NULL, NULL);
                }
                renderizar_boton_opcion(ventana.renderer, r_pres.victoria,1);
                renderizar_boton_opcion(ventana.renderer, r_pres.volver, 0);
                //mostramos estadisticas
                renderizarRanking(&ventana, &rankingRender);
                renderizar_boton_opcion(ventana.renderer, r_pres.salir,0);
            }
            // -------- ESTADISTICAS --------
            else if (estadoActual == ESTADO_ESTADISTICAS)
            {
                renderizarRanking(&ventana, &rankingRender);
                renderizar_boton_opcion(ventana.renderer, r_pres.volver, 0);
                renderizar_boton_opcion(ventana.renderer, r_pres.salir,0);
            }
            SDL_RenderPresent(ventana.renderer);

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime)
                SDL_Delay(frameDelay - frameTime);
               }
    // =============================
    // 4) LIMPIEZA DE MEMORIA
    // =============================

    if (tableroJuego)
        vector_destruir(tableroJuego);
    if(rankingCargado)
        vectorJugadoresDestruir(&vecJugadores);

    hud_destruir(r_pres.jugar);
    hud_destruir(r_pres.config);
    hud_destruir(r_pres.estadisticas);
    hud_destruir(r_pres.nivel);
    hud_destruir(r_pres.setFiguras);
    hud_destruir(r_pres.volver);

    liberar_imagenes(&r_pres);
    imagen_finalizar();

    destruirVentana(&ventana);
    return 0;
}

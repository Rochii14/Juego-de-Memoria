#include <stdio.h>
#include "juego.h"
#include "sonido.h"
#include "Imagen.h"
#include "Jugador.h"


//convierte un dato generico a una textura para escribir/dibujar en sdl
SDL_Texture* actualizar_texto(SDL_Renderer *renderer, void *datoAntiguo, void *datoNuevo, void *extra) {
    VentanaGrafica *ventana = (VentanaGrafica*)extra;
    SDL_Color blanco = {255, 255, 255, 255};
    return texto_crear_textura(ventana, (char*)datoNuevo, blanco);
}

Error inicializar_recursos(VentanaGrafica *ventana, recursos_graficos* r_pres) {
    Error err;

    // 1. Inicializar Ventana y Renderer
    err = InicializarVentana(ventana);
    if (err != TODO_OK) return err;

    // 2. Inicializar imagenes
    imagen_inicializar();
    r_pres->tex_fondo = imagen_cargar("img/FondoJuego.png", ventana);
    if (!r_pres->tex_fondo) return ERR_IMAGEN;

    ///set 1
    r_pres->figuras[F0] = imagen_cargar("img/figuras/blockbrillante.png", ventana);
    r_pres->figuras[F1] = imagen_cargar("img/figuras/bowser.png", ventana);
    r_pres->figuras[F2] = imagen_cargar("img/figuras/estrella.png", ventana);
    r_pres->figuras[F3] = imagen_cargar("img/figuras/Luigi.png", ventana);
    r_pres->figuras[F4] = imagen_cargar("img/figuras/Mario.png", ventana);
    r_pres->figuras[F5] = imagen_cargar("img/figuras/peachblanca.png", ventana);
    r_pres->figuras[F6] = imagen_cargar("img/figuras/toad.png", ventana);
    r_pres->figuras[F7] = imagen_cargar("img/figuras/Tuboverde.png", ventana);
    r_pres->figuras[F8] = imagen_cargar("img/figuras/goomba.png", ventana);
    r_pres->figuras[F9] = imagen_cargar("img/figuras/yoshi.png", ventana);
    r_pres->tex_vida = imagen_cargar("img/vida.png", ventana); /// AGUSSS------------------------------------
    r_pres->tex_vidaVacia = imagen_cargar("img/vidaVacia.png", ventana); /// AGUSSS------------------------------------

    ///set 2
    r_pres->figuras[E0] = imagen_cargar("img/figuras2/Z.png", ventana);
    r_pres->figuras[E1] = imagen_cargar("img/figuras2/I.png", ventana);
    r_pres->figuras[E2] = imagen_cargar("img/figuras2/J.png", ventana);
    r_pres->figuras[E3] = imagen_cargar("img/figuras2/L.png", ventana);
    r_pres->figuras[E4] = imagen_cargar("img/figuras2/O.png", ventana);
    r_pres->figuras[E5] = imagen_cargar("img/figuras2/S.png", ventana);
    r_pres->figuras[E6] = imagen_cargar("img/figuras2/T.png", ventana);
    r_pres->figuras[E7] = imagen_cargar("img/figuras2/Extra1.png", ventana);
    r_pres->figuras[E8] = imagen_cargar("img/figuras2/Extra2.png", ventana);
    r_pres->figuras[E9] = imagen_cargar("img/figuras2/Extra3.png", ventana);

    r_pres->tex_dorso = imagen_cargar("img/figuras/dorso.png", ventana);
    r_pres->tex_fondo_modojuego[TETRIS] = imagen_cargar("img/fondoSetMario.png", ventana);
    r_pres->tex_fondo_modojuego[MARIO] = imagen_cargar("img/FondoSetTetris.png", ventana);
    r_pres->tex_logo[TETRIS] = imagen_cargar("img/logo_set_tetris.png", ventana);///AGUSSS
    r_pres->tex_logo[MARIO] = imagen_cargar("img/logo_set_mario.png", ventana);///AGUSSS
    r_pres->tex_pointer = imagen_cargar("img/pointer.png", ventana);
    printf("\nImagenes cargadas!");


    // 3. Inicializar el HUD para el "A jugar"
    // Usamos el centro de la ventana y el puntero a 'ventana' como 'extra'

    r_pres->jugar = hud_inicializar(
        ventana->renderer,
        ventana->anchoVentana-120, ventana->altoVentana - 80,
        "JUGAR", sizeof("JUGAR"),
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->jugar, "JUGAR");

    r_pres->config = hud_inicializar(
        ventana->renderer,
        ventana->anchoVentana / 2, 310,
        "CONFIGURACION", sizeof("CONFIGURACION"),
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->config, "CONFIGURACION");

    r_pres->estadisticas = hud_inicializar(
        ventana->renderer,
        ventana->anchoVentana / 2, 430,
        "ESTADISTICAS", sizeof("ESTADISTICAS"),
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->estadisticas, "ESTADISTICAS");

    // ===============================
    // MENU CONFIGURACION
    // ===============================
    r_pres->nivel = hud_inicializar(
        ventana->renderer,
        ventana->anchoVentana / 2, 300,
        "TABLERO: 3x4", 50,
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->nivel, "TABLERO: 3x4");

    r_pres->setFiguras = hud_inicializar(
        ventana->renderer,
        ventana->anchoVentana / 2,400 ,
        "SET: 1", sizeof("SET: 1"),
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->setFiguras, "SET: 1");

    r_pres->cantJugadores = hud_inicializar(
        ventana->renderer,
        ventana->anchoVentana / 2,500,
        "JUGADORES: 1", sizeof("JUGADORES: 1"),
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->cantJugadores, "JUGADORES: 1");
    // ===============================
    // VOLVER
    // ===============================
    r_pres->volver = hud_inicializar(
        ventana->renderer,
        120, ventana->altoVentana - 80,
        "VOLVER", sizeof("VOLVER"),
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->volver, "VOLVER");

    r_pres->salir = hud_inicializar(
        ventana->renderer,
//        ventana->anchoVentana - 120, 50,
        ventana->anchoVentana - 50, 50,
        "X", sizeof("X"),
        ventana,
        actualizar_texto,
        NULL
    );
    hud_actualizar_dato(r_pres->salir, "X");

    /// PUNTAJE EN MODO JUEGO (inicial, dsp se actualiza en el match)
    /*
    r_pres->puntaje = hud_inicializar(
    ventana->renderer,
    150, 50,
    "PUNTAJE: 0", 20,   //texto inicial y tam max buffer
    ventana,
    actualizar_texto,
    NULL
    );
    */
    r_pres->racha = hud_inicializar(
    ventana->renderer,
    ventana->anchoVentana / 2 , 130,
    "ESTAS EN RACHA! + 0", sizeof("ESTAS EN RACHA! + 0"),
    ventana,
    actualizar_texto,
    NULL
    );

    /// mensaje victoria
    r_pres->victoria = hud_inicializar(
        ventana->renderer,
        ventana->anchoVentana /2 , 50,
        "victoria", 50,
        ventana,
        actualizar_texto,
        NULL
    );


        /// PUNTAJE EN MODO JUEGO (inicial, dsp se actualiza en el match)
    // Puntaje J1 izquierda
    r_pres->puntaje = hud_inicializar(  ventana->renderer, 120, 40, "J1: 0", 30, ventana, actualizar_texto, NULL );

    // Puntaje J2 derecha
    r_pres->puntaje2 = hud_inicializar( ventana->renderer, ventana->anchoVentana - 200, 40,  "J2: 0", 30, ventana, actualizar_texto,  NULL  );

    // Turno centro
    r_pres->turno = hud_inicializar( ventana->renderer,  ventana->anchoVentana/2, 40, "TURNO: J1", 30, ventana, actualizar_texto, NULL  );


    return TODO_OK;
}
void renderizar_tablero(SDL_Renderer* renderer, juego* v, recursos_graficos* rec)
{

    //recorro todo el vector hasta la ultima carta (v->tam)
    for(int i = 0; i < v->tam; i++){
        carta cartaActual = v->vec[i];
        SDL_Rect posaDibujar = cartaActual.posicion;

        if(cartaActual.estado == CARTA_TAPADA)
        {
            //si esta tapada dibujamos el dors
            SDL_RenderCopy(renderer, rec->tex_dorso, NULL, &posaDibujar);

            if(cartaActual.hover == ACTIVO)
                renderizar_hover(renderer, &posaDibujar);
        }
        else{
            //no esta tapada
            int idFig = cartaActual.idFigura;
            //buscamos imagen de la figura
            SDL_Texture* img = rec->figuras[idFig];
            SDL_RenderCopy(renderer, img, NULL, &posaDibujar);
        }
    }
}

void renderizar_hover(SDL_Renderer* renderer, SDL_Rect* rect)
{
    //soporte para transparencia
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);


    SDL_RenderFillRect(renderer, rect);


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    SDL_RenderDrawRect(renderer, rect);
}

void manejarEventosJuego(SDL_Event* evento, juego* tableroJuego, recursos_graficos* rec_graficos, EstadoJuego* estadoActual)
{
 if(evento->type == SDL_MOUSEMOTION)
    {
        int mx = evento->motion.x;
        int my = evento->motion.y;

        for(int i = 0; i<tableroJuego->tam; i++)
        {
            SDL_Rect rect = tableroJuego->vec[i].posicion; ///guardo en r la posicion de las cartas

            if(mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
            {
                tableroJuego->vec[i].hover = ACTIVO;
            }
            else
            {
                tableroJuego->vec[i].hover = DESACTIVO;
            }
        }
    }

    if(evento->type == SDL_MOUSEBUTTONDOWN){
        int mx = evento->button.x;
        int my = evento->button.y;
        SDL_Rect rect;

        // Usamos rec_graficos que es el nombre del par�metro de esta funci�n
        hud_obtener_rectangulo(rec_graficos->volver, &rect);

        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h) {
            // Ahora s�, usamos el puntero para cambiar el estado en el main
            *estadoActual = ESTADO_PRESENTACION;
            return;
        }
        manejarClickTablero(mx,my,tableroJuego);

    }
}
void manejarClickTablero(int mx, int my, juego* tableroJuego)
{
    int i = 0;
    int encontrada = -1;

    while(i < tableroJuego->tam && encontrada == -1){
        SDL_Rect rect = tableroJuego->vec[i].posicion; //posicion carta

        if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
        {
            if(tableroJuego->vec[i].estado == CARTA_TAPADA){
                tableroJuego->vec[i].estado = CARTA_VOLTEADA;
                reproducir_click();
                printf("\nCarta encontrada: %d", tableroJuego->vec[i].idFigura);

                if (tableroJuego->clicks == 0){
                    tableroJuego->clicks = 1;
                    tableroJuego->primerclick = i;
                }
                else if(tableroJuego->clicks == 1){
                    tableroJuego->clicks = 2;
                    tableroJuego->segclick = i;

                }
            }
            encontrada = 0;

        }

        i++;//posicion donde la encontro
    }//fin loop while

}

int verificarMatch(juego* tableroJuego, Jugador* jugador, recursos_graficos* rec)
{
    int posC1, posC2;

    posC1 = tableroJuego->primerclick;
    posC2 = tableroJuego->segclick;

    if(tableroJuego->vec[posC1].idFigura == tableroJuego->vec[posC2].idFigura){
        // id figuras iguales, match
        tableroJuego->vec[posC1].estado = CARTA_ENCONTRADA;
        tableroJuego->vec[posC2].estado = CARTA_ENCONTRADA;
        printf("\nPAR ENCONTRADO");

        reproducir_acierto();

        //CUANTO PARES ENCONTRADOS
        tableroJuego->pares_encontrados++;
        // SUMO PUNTOS
        jugador->PuntajeAcum += tableroJuego->vec[posC1].puntos ;

        //RACHA
        tableroJuego->racha++; //si acerto sumo racha

        if(tableroJuego->racha > 1){
            tableroJuego->bonus = (tableroJuego->racha - 1) * puntosxracha;
            jugador->PuntajeAcum += tableroJuego->bonus;
            printf("\nBONUS RACHA: %d", tableroJuego->bonus);
            actualizar_racha_juego(rec, tableroJuego);
        }

        actualizar_visual_puntaje(rec, jugador);
        printf("\n pares: %d; puntos jug: %d", tableroJuego->pares_encontrados, jugador->PuntajeAcum);

        tableroJuego->clicks = 0;
        tableroJuego->primerclick = -1;
        tableroJuego->segclick = -1;

        return 1;//match
    }else{
        //no match
        //SDL_Delay(200);
        reproducir_error();


        tableroJuego->vec[posC1].estado = CARTA_TAPADA;
        tableroJuego->vec[posC2].estado = CARTA_TAPADA;
        printf("\nNO COINCIDEN");

        //se corta la racha
        tableroJuego->racha = 0;
        tableroJuego->bonus = 0;
        actualizar_racha_juego(rec, tableroJuego);

        // Reset clicks
        tableroJuego->clicks = 0;
        tableroJuego->primerclick = -1;
        tableroJuego->segclick = -1;

        return 0;//no match
    }

}
void actualizar_visual_puntaje(recursos_graficos* rec, Jugador* jugador)
{
    char text_nuevo[20];

    sprintf(text_nuevo, "PUNTAJE: %d", jugador->PuntajeAcum);
    hud_actualizar_dato(rec->puntaje, text_nuevo);
}

void actualizar_visual_2puntajes(recursos_graficos* rec, Jugador* j1, Jugador* j2)
{
    char texto1[TAM_NOMBRE+30];
    char texto2[TAM_NOMBRE+30];

    snprintf(texto1, sizeof(texto1), "J1 (%s): %d", j1->Nombre, j1->PuntajeAcum);
    snprintf(texto2, sizeof(texto2), "J2 (%s): %d", j2->Nombre, j2->PuntajeAcum);

    hud_actualizar_dato(rec->puntaje, texto1);
    hud_actualizar_dato(rec->puntaje2, texto2);
}
void actualizar_visual_turno(recursos_graficos* rec, Jugador* jugadorActual)
{
    char texto[80];
    snprintf(texto, sizeof(texto), "TURNO: %s", jugadorActual->Nombre);
    hud_actualizar_dato(rec->turno, texto);
}


void actualizar_racha_juego(recursos_graficos* rec, juego* tablero)
{
    char text_nuevo[30];

    sprintf(text_nuevo, "ESTAS EN RACHA + %d", tablero->bonus);
    hud_actualizar_dato(rec->racha, text_nuevo);
}

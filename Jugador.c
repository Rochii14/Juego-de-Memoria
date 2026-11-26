#include "Jugador.h"
///TIENE LAS FUNCIONES DE PEDIR NOMBRE

void iniciarIngresoNombre(Jugador *j)
{
    j->Nombre[0] = '\0';
    j->posNombre = 0;
    SDL_StartTextInput();//acá abro la memoria que me permite ingresar texto
}

void manejarEventosPedirNombre(SDL_Event* evento,
                               EstadoJuego* estadoActual,
                               recursos_graficos *r,
                               Jugador *jugador,
                               int *jugadorActual,
                               int cantidadJugadores)
{
    SDL_Rect rect;

    // =========================
    // 1) TEXTO INGRESADO
    // =========================
    if (evento->type == SDL_TEXTINPUT )
    {
        if (jugador->posNombre < TAM_NOMBRE - 1)
        {
            strcat(jugador->Nombre, evento->text.text);
            jugador->posNombre++;
        }
    }

    // =========================
    // 2) TECLAS ESPECIALES
    // =========================
    if (evento->type == SDL_KEYDOWN)
    {
        // BORRAR
        if (evento->key.keysym.sym == SDLK_BACKSPACE && jugador->posNombre > 0)
        {
            jugador->posNombre--;
            jugador->Nombre[jugador->posNombre] = '\0';

        }

        // ENTER
        if (evento->key.keysym.sym == SDLK_RETURN || evento->key.keysym.sym == SDLK_KP_ENTER)
        {
            if(jugador->Nombre[0] == '\0')
            {
             strcpy(jugador->Nombre, "Anonymous");
             jugador->posNombre = strlen("Anonymous");
            }
            printf("Nombre ingresado: %s\n", jugador->Nombre);

            if (cantidadJugadores == 2 && *jugadorActual == 0)
            {
                // Pasamos al segundo jugador
                (*jugadorActual) = 1;
            }
            else
            {
                // Ya terminaron de cargar nombres
                *estadoActual = ESTADO_JUEGO;
                SDL_StopTextInput();
                printf("Cambiando a ESTADO_JUEGO\n");
            }
        }
    }

    // =========================
    // 3) EVENTOS DE MOUSE
    // =========================
    if (evento->type == SDL_MOUSEBUTTONDOWN)
    {
        int mx = evento->button.x;
        int my = evento->button.y;

        // -------- BOTÓN VOLVER --------
        hud_obtener_rectangulo(r->volver, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w &&
            my >= rect.y && my <= rect.y + rect.h)
        {
            *estadoActual = ESTADO_PRESENTACION;
            SDL_StopTextInput();
            printf("Volviendo a presentación\n");
            return;
        }

        // -------- BOTÓN JUGAR --------
        hud_obtener_rectangulo(r->jugar, &rect);
        if (mx >= rect.x && mx <= rect.x + rect.w &&
            my >= rect.y && my <= rect.y + rect.h)
        {
            if(jugador->Nombre[0] == '\0')
            {
             strcpy(jugador->Nombre, "Anonymous");
             jugador->posNombre = strlen("Anonymous");
            }
            *estadoActual = ESTADO_JUEGO;
            SDL_StopTextInput();
            printf("Click en JUGAR -> ESTADO_JUEGO\n");
            return;
        }
    }
}


void renderizarIngresoNombre(VentanaGrafica *ventana, recursos_graficos *r, Jugador *jugador)
{
    SDL_Color colorTexto = {255, 255, 255, 255};
    SDL_Color colorCaja = {0, 0, 0, 200};
    SDL_Color colorBorde = {255, 255, 255, 255};

    SDL_Rect cajaTexto; //donde visualmente se escribe el nombre
        cajaTexto.w = 600;
        cajaTexto.h = 80;
        cajaTexto.x = ventana->anchoVentana / 2 - cajaTexto.w / 2;
        cajaTexto.y = ventana->altoVentana / 2 - cajaTexto.h / 2;

    // Dibujar fondo oscuro semitransparente
    SDL_SetRenderDrawColor(ventana->renderer, 0, 0, 0, 180);
    SDL_Rect fondo = {0, 0, ventana->anchoVentana, ventana->altoVentana};
    SDL_RenderFillRect(ventana->renderer, &fondo);

    // Dibujar caja de texto
    SDL_SetRenderDrawColor(ventana->renderer,colorCaja.r,colorCaja.g,colorCaja.b,colorCaja.a);
    SDL_RenderFillRect(ventana->renderer, &cajaTexto);

    // Dibujar borde
    SDL_SetRenderDrawColor(ventana->renderer,colorBorde.r,colorBorde.g,colorBorde.b,colorBorde.a);
    SDL_RenderDrawRect(ventana->renderer, &cajaTexto);

    // Cursor parpadeante
    char buffer[TAM_NOMBRE + 2];
    strcpy(buffer, jugador->Nombre);

    Uint32 tiempo = SDL_GetTicks();
    if ((tiempo / 500) % 2 == 0) // parpadeo cada 500ms
    {
        strcat(buffer, "|");
    }

    if (buffer[0] == '\0')
        strcpy(buffer, "|");

    // Crear textura del texto
    SDL_Texture *texTexto = texto_crear_textura(ventana, buffer, colorTexto);

    if (texTexto)
    {
        int w, h;
        SDL_QueryTexture(texTexto, NULL, NULL, &w, &h);

        SDL_Rect destino;
        destino.x = cajaTexto.x + 20;
        destino.y = cajaTexto.y + (cajaTexto.h / 2 - h / 2);
        destino.w = w;
        destino.h = h;

        SDL_RenderCopy(ventana->renderer, texTexto, NULL, &destino);
        SDL_DestroyTexture(texTexto);
    }
    //Texto de ingrese
    SDL_Texture *texTitulo = texto_crear_textura(  ventana, "Ingrese su nombre y presione ENTER", colorTexto);

    if (texTitulo)
    {
        int w, h;
        SDL_QueryTexture(texTitulo, NULL, NULL, &w, &h);

        SDL_Rect destinoTitulo;
        destinoTitulo.x = ventana->anchoVentana / 2 - w / 2;
        destinoTitulo.y = cajaTexto.y - 100;
        destinoTitulo.w = w;
        destinoTitulo.h = h;

        SDL_RenderCopy(ventana->renderer, texTitulo, NULL, &destinoTitulo);
        SDL_DestroyTexture(texTitulo);
    }
}

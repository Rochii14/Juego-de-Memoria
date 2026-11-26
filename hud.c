#include "hud.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sHUD {
    SDL_Texture *textura;
    SDL_Renderer *renderer;
    tActualizarHUD actualizar;
    tDestruirHUD destruir;
    int32_t posX;
    int32_t posY;
    double angulo;
    void *dato;
    size_t tamDato;
    void *extra;
};

tHUD* hud_inicializar(SDL_Renderer *renderer, int32_t posX, int32_t posY, void *dato, size_t tamDato, void *extra, tActualizarHUD actualizar, tDestruirHUD destruir) {
    tHUD *hud = malloc(sizeof(tHUD));
    if (!hud) return NULL;

    hud->tamDato = tamDato;
    if (tamDato > 0) {
        hud->dato = malloc(tamDato);
        if (!hud->dato) {
            free(hud);
            return NULL;
        }
        memcpy(hud->dato, dato, tamDato);
    } else {
        hud->dato = NULL;
    }

    hud->extra = extra;
    hud->posX = posX;
    hud->posY = posY;
    hud->angulo = 0;
    hud->actualizar = actualizar;
    hud->destruir = destruir;
    hud->textura = NULL;
    hud->renderer = renderer;

    return hud;
}

void hud_dibujar(const tHUD *hud) {
    if (!hud || !hud->textura) return;

    int32_t ancho, alto;
    SDL_QueryTexture(hud->textura, NULL, NULL, &ancho, &alto);

    SDL_Rect destino = { hud->posX - (ancho / 2), hud->posY - (alto / 2), ancho, alto };
    SDL_Point centro = { ancho / 2, alto / 2 };

    SDL_RenderCopyEx(hud->renderer, hud->textura, NULL, &destino, hud->angulo, &centro, SDL_FLIP_NONE);
}
//para obtener las medidas de la textura creada y su posicion. Lo sincronizamos con hud_dibujar
void hud_obtener_rectangulo(const tHUD *hud, SDL_Rect *rect) {
    if (!hud || !hud->textura) return;
    int32_t w,h; //ancho, alto;
    SDL_QueryTexture(hud->textura, NULL, NULL, &w, &h);

    // Calculamos el rectangulo
    rect->x = hud->posX - (w / 2);
    rect->y = hud->posY - (h / 2);
    rect->w = w;
    rect->h = h;
}

Error hud_actualizar_dato(tHUD *hud, void *datoNuevo) {
    if (!hud->actualizar) return ERR_HUD_ACTUALIZAR;

    SDL_Texture *nuevaTextura = hud->actualizar(hud->renderer, hud->dato, datoNuevo, hud->extra);
    if (!nuevaTextura) return ERR_TEXTURA;

    if (hud->textura) SDL_DestroyTexture(hud->textura);
    hud->textura = nuevaTextura;


    if (hud->dato && datoNuevo) memcpy(hud->dato, datoNuevo, hud->tamDato);

    return TODO_OK;
}

void hud_destruir(tHUD *hud) {
    if (!hud) return;
    if (hud->destruir) hud->destruir(hud->extra);
    if (hud->textura) SDL_DestroyTexture(hud->textura);
    if (hud->dato) free(hud->dato);
    free(hud);
}

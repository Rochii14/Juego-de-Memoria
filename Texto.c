#include <stdlib.h>
#include <stdio.h>
#include "Texto.h"

Error texto_inicializar()
{
    if (TTF_Init() != 0) {
        fprintf(stderr, "No se pudo inicializar SDL_ttf: %s\n", TTF_GetError());
        return ERR_SDL_TTF;
    }

    return TODO_OK;

}
TTF_Font* texto_cargar_fuente(const char *ruta, uint32_t tamLetra)
{
    TTF_Font *fuente = TTF_OpenFont(ruta, tamLetra);
    if (!fuente) {
        fprintf(stderr, "No se pudo cargar la fuente \%s\n", TTF_GetError());
    }

    return fuente;

}
SDL_Texture* texto_crear_textura(VentanaGrafica *ventana, const char* texto, SDL_Color color)
{
    SDL_Surface * superficie = TTF_RenderUTF8_Blended(ventana->fuenteTTF, texto, color); // Permite utilizar caracteres UTF8
    if (!superficie) {
        fprintf(stderr, "%s\n", TTF_GetError());
        return NULL;
    }

    SDL_Texture *textura = SDL_CreateTextureFromSurface(ventana->renderer, superficie);

    SDL_FreeSurface(superficie); // Una vez creada la textura, la superficie ya no es necesaria

    if (!textura) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);

    return textura;
}
void texto_destruir_fuente(TTF_Font *fuente)
{
    TTF_CloseFont(fuente);
}
void texto_finalizar()
{
    TTF_Quit();
}

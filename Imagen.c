#include <stdio.h>
#include "Imagen.h"
#include "Errores.h"


Error imagen_inicializar()//inicializar imagen
{
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);

    if ((initted & flags) != flags) {
        printf("IMG_Init error: %s\n", IMG_GetError());
        return ERR_SDL_IMAGE;
    }

    return TODO_OK;
}
SDL_Texture * imagen_cargar (const char *ruta, VentanaGrafica * ventana) // Carga una imagen y la transforma en textura
{
    SDL_Surface *image= IMG_Load(ruta);
    if (!image)
    {
        printf("IMG_Load error (%s): %s\n", ruta, IMG_GetError());
        return NULL;
    }
    SDL_Texture *image_texture=SDL_CreateTextureFromSurface(ventana->renderer,image);
    if (!image_texture) {
        printf("SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        return NULL;
    }
    return image_texture;
}
void imagen_destruir( SDL_Texture * imagen_texture)
{
    SDL_DestroyTexture(imagen_texture);
}

void imagen_finalizar()
{
    IMG_Quit();
}
void liberar_imagenes(recursos_graficos* r_pres)
{
    imagen_destruir(r_pres->tex_fondo);
    ///limpieza set 1
    imagen_destruir(r_pres->figuras[F0]);
    imagen_destruir(r_pres->figuras[F1]);
    imagen_destruir(r_pres->figuras[F2]);
    imagen_destruir(r_pres->figuras[F3]);
    imagen_destruir(r_pres->figuras[F4]);
    imagen_destruir(r_pres->figuras[F5]);
    imagen_destruir(r_pres->figuras[F6]);
    imagen_destruir(r_pres->figuras[F7]);
    imagen_destruir(r_pres->figuras[F8]);
    imagen_destruir(r_pres->figuras[F9]);
    imagen_destruir(r_pres->tex_vida);
    imagen_destruir(r_pres->tex_vidaVacia);
    ///limpieza set 2
    imagen_destruir(r_pres->figuras[E0]);
    imagen_destruir(r_pres->figuras[E1]);
    imagen_destruir(r_pres->figuras[E2]);
    imagen_destruir(r_pres->figuras[E3]);
    imagen_destruir(r_pres->figuras[E4]);
    imagen_destruir(r_pres->figuras[E5]);
    imagen_destruir(r_pres->figuras[E6]);
    imagen_destruir(r_pres->figuras[E7]);
    imagen_destruir(r_pres->figuras[E8]);
    imagen_destruir(r_pres->figuras[E9]);

    imagen_destruir(r_pres->tex_dorso);
    imagen_destruir(r_pres->tex_fondo_modojuego[TETRIS]);
    imagen_destruir(r_pres->tex_fondo_modojuego[MARIO]);
    imagen_destruir(r_pres->tex_logo[TETRIS]);
    imagen_destruir(r_pres->tex_logo[MARIO]);
    imagen_destruir(r_pres->tex_pointer);

}

#ifndef ERRORES_H_INCLUDED
#define ERRORES_H_INCLUDED

typedef enum {

    // Generico
    TODO_OK = 0, //igual por defecto es 0 por ser el primero
    ERR_MEMORIA,

    // SDL
    ERR_SDL,
    ERR_SDL_MIXER,
    ERR_SDL_TTF,
    ERR_SDL_IMAGE,
    ERR_TEXTURA,

    // Audio
    ERR_AUDIO_DRIVER,
    ERR_AUDIO_ASSET,

    // Imagen
    ERR_IMAGEN,

    //hud - textos
    ERR_HUD_ACTUALIZAR,

    //archivos
    ERR_ARCHIVO
}Error;

const char* InformarError(Error err);


#endif // ERRORES_H_INCLUDED

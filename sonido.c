#include "sonido.h"
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

static Mix_Chunk* sonidoAcierto = NULL;
static Mix_Chunk* sonidoError   = NULL;
static Mix_Music* musicaFondo   = NULL;
static Mix_Chunk* sonidoPremio =  NULL;
static Mix_Chunk* sonidoClick = NULL;


void sonidos_inicializar()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Error iniciando audio: %s\n", Mix_GetError());
        return;
    }

    int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
    if ((Mix_Init(flags) & flags) != flags)
    {
        printf("Error inicializando formatos: %s\n", Mix_GetError());
    }
}

void sonidos_cargar()
{
    sonidoAcierto = Mix_LoadWAV("sonidos/acierto.wav");
    if (!sonidoAcierto)
        printf("\nError cargando acierto\n");

    sonidoError = Mix_LoadWAV("sonidos/error.wav");
    if (!sonidoError)
        printf("\nError cargando error\n");

    musicaFondo = Mix_LoadMUS("sonidos/fondo.mp3");
    if (!musicaFondo)
        printf("\nError cargando musica\n");

    sonidoClick= Mix_LoadWAV("sonidos/click.mp3");
    if (!sonidoClick)
        printf("\nError cargando click\n");
}

void reproducir_acierto()
{
    Mix_PlayChannel(-1, sonidoAcierto, 0);
}

void reproducir_error()
{
    Mix_PlayChannel(-1, sonidoError, 0);
}

void reproducir_click()
{
    Mix_PlayChannel(-1,sonidoClick,0);
}
void reproducir_musica()
{
    Mix_PlayMusic(musicaFondo, -1);
}


void apagar_musica()
{
    Mix_PauseMusic();
}

void reproducir_win()
{
    Mix_PlayChannel(-1,sonidoPremio,0);
}
void sonidos_liberar()
{
    Mix_FreeChunk(sonidoAcierto);
    Mix_FreeChunk(sonidoError);
    Mix_FreeMusic(musicaFondo);
    Mix_CloseAudio();
}

#ifndef SONIDO_H_INCLUDED
#define SONIDO_H_INCLUDED
#define FREC_MUESTREO 44100
#define AMPLITUD_TONO 32766
#define DURACION_SEG 1

#include <math.h>
#include "sdl.h"


void sonidos_cargar();
void sonidos_inicializar();
void reproducir_acierto();
void reproducir_error();
void reproducir_musica();
void reproducir_click();
void reproducir_win();
void apagar_musica();
void sonidos_liberar();

#endif // SONIDO_H_INCLUDED

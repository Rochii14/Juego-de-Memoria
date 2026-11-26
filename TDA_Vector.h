#ifndef TDA_VECTOR_H_INCLUDED
#define TDA_VECTOR_H_INCLUDED

#include "Errores.h"
#define TAM_MAX_VEC_J 10
/// TAM_MAX_VEC_J -> Maximo tam vector jugadores para usarse en estadisticas
#define INCREMENTO_VECTOR 1.5

typedef int (*cmp) (const void*, const void*); //puntero a funcion de comparacion

typedef struct
{
    void* vec; //variable de puntero del tipo void donde guardo la direccion que devuelve el malloc
    size_t ce; //cantidad de elementos guardados
    size_t TAMV;//TAM Max del vector
    size_t tamElem;
}t_Vector;

//funciones para las estadisticas (leer archivos de jugadores, guardarlos en vectores dinamicos)
void* vectorCrear(t_Vector* v,size_t TamElementoVec, size_t tamMaxCant);
void vectorDestruir(t_Vector* v);
Error vectorRedimensionar(t_Vector *v);
void vectorJugadoresCrear(t_Vector *v);
void vectorJugadoresDestruir(t_Vector *v);

int cmpJugador(const void* a, const void* b);
Error vectorJugadoresInsertarOrdenado(t_Vector* v, const void* jugador, size_t tamElem,int (*cmp) (const void*, const void*));
Error cargarVectorDeArchivoTxT(t_Vector *v);
Error rankingGuardar(t_Vector* v);

#endif // TDA_VECTOR_H_INCLUDED

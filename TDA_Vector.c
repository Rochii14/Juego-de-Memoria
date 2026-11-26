#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA_Vector.h"
#include "Jugador.h"

/////////generico
void* vectorCrear(t_Vector* v,size_t TamElementoVec, size_t tamMaxCant) //la idea es usar esto para crear el vector donde se guardan los jugadores con su
{
    v->vec=malloc(tamMaxCant* TamElementoVec);
    if(!v->vec)
    {
        perror("Error al abrir el archivo:");
        return NULL;
    }

    v->ce=0;
    v->TAMV=tamMaxCant;
    v->tamElem=TamElementoVec;
    return v->vec;
}

void vectorDestruir(t_Vector* v)
{
    free(v->vec);
    v->ce=0;
    v->TAMV=0;
    v->tamElem=0;
}
Error vectorRedimensionar(t_Vector *v)
{
    void* nuevoVec= realloc(v->vec , ((v->TAMV) * INCREMENTO_VECTOR* (v->tamElem))); //capacidadMax * incremento * tamElemento estructura
    if(!nuevoVec)
    {
        puts("No es posible redimensionar el vector.\n");
        return ERR_MEMORIA;
    }
    v->vec=nuevoVec;
    v->TAMV *= INCREMENTO_VECTOR;
    return TODO_OK;
}

//////// jugador
//funcion que crea el vector de jugador (caso 1 jugador)
void vectorJugadoresCrear(t_Vector *v)
{
    vectorCrear(v,sizeof(Jugador),TAM_MAX_VEC_J);
}

void vectorJugadoresDestruir(t_Vector *v)
{
    vectorDestruir(v);
}

int cmpJugador(const void* a, const void* b)
{
    const Jugador* j1 = a;
    const Jugador* j2 = b;

    return j2->PuntajeAcum - j1->PuntajeAcum;
}

Error vectorJugadoresInsertarOrdenado(t_Vector* v, const void* jugador, size_t tamElem,int (*cmp) (const void*, const void*))
{
    if(v->ce==v->TAMV)///evaluo si la cant elementos es menor a la capacidad
    {///redimensiono capacidad si es necesario
        if(vectorRedimensionar(v)==TODO_OK)
        {
            puts("Vector redimensionado.\n");
        }else{
            puts ("Error de Memoria.\n");
            return ERR_MEMORIA;
        }
    }
    char *inicioVec=(char*)(v->vec);
    char *finVec= (char*)(v->vec+(v->ce)*(v->tamElem)); //el final es la cantidad de bytes

    ///busco la posicion en donde deberia insertar ordenadamente
    while(inicioVec<finVec && (cmp(inicioVec, jugador) < 0))
    {
        inicioVec+=tamElem;
    }
    ///muevo el bloque que queda a la derecha
    memmove(inicioVec + v->tamElem, inicioVec,finVec - inicioVec);
    ///inserto el valor donde le corresponde
    memcpy(inicioVec, jugador, v->tamElem);
    ///modifico la cantidad de elementos
    v->ce++;
    return TODO_OK;
}

////////ARCHIVOS
Error cargarVectorDeArchivoTxT(t_Vector *v) //para hacer el top de estadisticas-- 1 paso
{
    FILE* f = fopen("Jugadores.txt", "r");
    // Si no existe, lo creo vacio-- NO USO W+ PORQUE SEPARO EN DISTINTAS FUNCIONES EL CODIGO
    if(!f)
    {
        f = fopen("Jugadores.txt", "w");
        if(!f)
            return ERR_ARCHIVO;

        fclose(f);
        return TODO_OK; // no hay registros para cargar
    }

    Jugador j;
    while(fscanf(f, "%d %49s", &j.PuntajeAcum, j.Nombre) == 2) //igualo a dos porque espero leer dos campos
    {
        j.posNombre = 0; // lo inicializo porque en el archivo no lo uso

        if(vectorJugadoresInsertarOrdenado(v, &j, sizeof(Jugador),cmpJugador) != TODO_OK) // a medida que leo el registro en la variable, voy insertando en el vector
        {
            fclose(f);
            return ERR_MEMORIA;
        }
    }

    fclose(f);
    return TODO_OK;
}

//2 paso insercion ordenada en vector
//3 paso guardar vector en archivo.
Error rankingGuardar(t_Vector* v)
{
    FILE* f = fopen("Jugadores.txt", "w");
    if(!f)
        return ERR_ARCHIVO;

    char* base = (char*)v->vec;

    for(size_t i = 0; i < v->ce; i++)
    {
        Jugador* j = (Jugador*)(base + i * v->tamElem);
        fprintf(f, "%d %s\n", j->PuntajeAcum, j->Nombre);
    }

    fclose(f);
    return TODO_OK;
}

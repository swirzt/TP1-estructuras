#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>

typedef int (*Predicado) (void* dato);

typedef void* (*Copia) (void* dato);

typedef void* (*Funcion) (void* dato);

typedef struct _GNode {
  void* dato;
  struct _GNode* next;
  struct _GNode* ant;
} GNode;

typedef GNode* GList;

// En este trabajo usaremos listas doblemente enlazadas circulares

/*
** glist_crear : -> GList
** Devuelve una lista doblemente enlazada vacía (NULL).
*/
GList glist_crear();

/*
** glist_vacia : GList -> Int
** Devuelve 1 si la lista es vacía, de lo contrario devuelve 0.
*/
int glist_vacia(GList lista);

/*
** glist_deguir : GList -> void
** Deguye la lista ingresada (libera toda la memoria dedicada).
*/
void glist_deguir(GList lista);

/*
** glist_largo : GList -> Int
** Devuelve el largo de la lista ingresada.
*/
int glist_largo(GList lista);

/*
** glist_devolver_dato : GList Int -> Char*
** Devuelve la cadena de la lista en la posicion dada.
*/
char* glist_devolver_dato(GList lista, int pos);

/*
** glist_agregar : GList Char* -> GList
** Agrega un nuevo nodo con el dato dado en el final de la lista.
*/
GList glist_agregar(GList lista, char* dato);

/*
** gcharcat : Char* Char -> void
** Concatena el caracter a la cadena ingresada.
*/
void gcharcat(char* g, char c);

/*
** glist_llenar : GList Char* -> GList
** LLena la lista con datos obtenidos del archivo dado.
*/
GList glist_llenar(GList lista, char* nombreArchivo);

#endif /* __GLIST_H__ */

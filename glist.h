#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>

typedef int (*Predicado)(void* dato);

typedef void* (*Copia)(void* dato);

typedef void* (*Funcion)(void* dato);

typedef void (*Destruir)(void* dato);

// Utilizamos listas doblemente enlazadas circulares

typedef struct _GNode {
  void* dato;
  struct _GNode* next;
  struct _GNode* ant;
} GNode;

typedef GNode* GList;

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
** glist_destruir : GList Destruir -> void
** Deguye la lista ingresada (libera toda la memoria dedicada).
*/
void glist_destruir(GList lista, Destruir d);

/*
** glist_largo : GList -> Int
** Devuelve el largo de la lista ingresada.
*/
int glist_largo(GList lista);

/*
** glist_devolver_dato : GList Int -> void*
** Devuelve la cadena de la lista en la posicion dada.
*/
void* glist_devolver_dato(GList lista, int pos, int largolista);

/*
** glist_agregar : GList void* -> GList
** Agrega un nuevo nodo con el dato dado en el final de la lista.
*/
GList glist_agregar(GList lista, void* dato);

/*
** glist_map : GList Funcion Copia -> GList
** Aplica una funcion f a cada elemento de la lista
*/
GList glist_map(GList lista, Funcion f, Copia c);

/*
** glist_filter : GList Predicado Copia -> GList
** Devuelve una GList con los elementos de lista que cumplan con un predicado p
*/
GList glist_filter(GList lista, Predicado p, Copia c);

#endif /* __GLIST_H__ */

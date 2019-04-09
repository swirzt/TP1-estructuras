#ifndef __STRLIST_H__
#define __STRLIST_H__

#include <stddef.h>

typedef struct _StrNode {
  char* dato;
  struct _StrNode* next;
  struct _StrNode* ant;
} StrNode;

typedef StrNode* StrList;

// En este trabajo usaremos listas doblemente enlazadas circulares

/*
** strlist_crear : -> StrList
** Devuelve una lista doblemente enlazada vacía (NULL).
*/
StrList strlist_crear();

/*
** strlist_vacia : StrList -> Int
** Devuelve 1 si la lista es vacía, de lo contrario devuelve 0.
*/
int strlist_vacia(StrList lista);

/*
** strlist_destruir : StrList -> void
** Destruye la lista ingresada (libera toda la memoria dedicada).
*/
void strlist_destruir(StrList lista);

/*
** strlist_largo : StrList -> Int
** Devuelve el largo de la lista ingresada.
*/
int strlist_largo(StrList lista);

/*
** strlist_devolver_dato : StrList Int Int -> Char*
** Devuelve la cadena de la lista en la posicion dada.
*/
char* strlist_devolver_dato(StrList lista, int pos, int largolista);

/*
** strlist_agregar : StrList Char* -> StrList
** Agrega un nuevo nodo con el dato dado en el final de la lista.
*/
StrList strlist_agregar(StrList lista, char* dato);

/*
** strlist_llenar : StrList Char* -> StrList
** LLena la lista con datos obtenidos del archivo dado.
*/
StrList strlist_llenar(StrList lista, char* nombreArchivo);

#endif /* __STRLIST_H__ */

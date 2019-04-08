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

typedef struct {
  char* nombre;
  char* pais;
  int edad;
} Persona;

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
** glist_destruir : GList -> void
** Deguye la lista ingresada (libera toda la memoria dedicada).
*/
void glist_destruir(GList lista);

/*
** glist_largo : GList -> Int
** Devuelve el largo de la lista ingresada.
*/
int glist_largo(GList lista);

/*
** glist_devolver_dato : GList Int -> Char*
** Devuelve la cadena de la lista en la posicion dada.
*/
void* glist_devolver_dato(GList lista, int pos);

/*
** glist_agregar : GList Char* -> GList
** Agrega un nuevo nodo con el dato dado en el final de la lista.
*/
GList glist_agregar(GList lista, void* dato);

/*
** persona_crear : char* char* int -> Persona*
** Crea un nuevo elemento de la estructura Persona  
*/
Persona* persona_crear(char* nombre, int edad, char* pais);

/*
** llenar_lista_personas : GList char* -> Glist
** Llena una GList vacia con nodos de elemento personas
*/
GList llenar_lista_personas(GList lista,char* archivopersonas);

/*
** glist_map : GList Funcion Copia -> GList
** Aplica una funcion f a cada elemento de la lista
*/
GList glist_map(GList lista, Funcion f, Copia c);

/*
** glist_filter : GList Predicado Copia
** Devuelve una GList con los elementos de lista que cumplan con un predicado p
*/
GList glist_filter(GList lista, Predicado p, Copia c);

#endif /* __GLIST_H__ */

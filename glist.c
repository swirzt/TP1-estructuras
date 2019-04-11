#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

// Utilizamos listas doblemente enlazadas circulares

/*
** glist_crear : -> GList
** Devuelve una lista doblemente enlazada vacía (NULL).
*/
GList glist_crear() { return NULL; }

/*
** glist_vacia : GList -> Int
** Devuelve 1 si la lista es vacía, de lo contrario devuelve 0.
*/
int glist_vacia(GList lista) { return lista == NULL; }

/*
** glist_destruir : GList Destruir -> void
** Deguye la lista ingresada (libera toda la memoria dedicada).
*/
void glist_destruir(GList lista, Destruir d) {
  if (!glist_vacia(lista)) {
    GList i = lista;
    do {
      GList sigtmp = i->next;
      d(i->dato);
      free(i);
      i = sigtmp;
    } while (i->next != lista);
  }
}

/*
** glist_largo : GList -> Int
** Devuelve el largo de la lista ingresada.
*/
int glist_largo(GList lista) {
  if (glist_vacia(lista)) return 0;
  GList inicio = lista;
  int i = 0;
  for (; lista->next != inicio; lista = lista->next) i++;
  return ++i;
}

/*
** glist_devolver_dato : GList Int Int -> void*
** Devuelve la cadena de la lista en la posicion dada.
*/
void* glist_devolver_dato(GList lista, int pos, int largolista) {
  if (glist_vacia(lista)) return NULL;
  if (largolista / 2 > pos)  // Recorro hacia adelante
    for (int i = 0; i < pos; i++) lista = lista->next;
  else {  // Recorro hacia atras
    int max = largolista - pos + 1;
    for (int i = 0; i <= max; i++) lista = lista->ant;
  }
  return lista->dato;
}

/*
** glist_agregar : GList void* -> GList
** Agrega un nuevo nodo con el dato dado en el final de la lista.
*/
GList glist_agregar(GList lista, void* dato) {
  GList nuevoNodo = malloc(sizeof(GNode));
  nuevoNodo->dato = dato;
  if (glist_vacia(lista)) {
    nuevoNodo->ant = nuevoNodo;
    nuevoNodo->next = nuevoNodo;
    return nuevoNodo;
  } else {
    nuevoNodo->next = lista;
    nuevoNodo->ant = lista->ant;
    lista->ant->next = nuevoNodo;
    lista->ant = nuevoNodo;
    return lista;
  }
}

/*
** glist_map : GList Funcion Copia -> GList
** Aplica una funcion f a cada elemento de la lista
*/
GList glist_map(GList lista, Funcion f, Copia c) {
  GList inicio = lista;
  GList listaMapeada = glist_crear();
  do {
    listaMapeada = glist_agregar(listaMapeada, f(c(lista->dato)));
    lista = lista->next;
  } while (lista->next != inicio);
  return listaMapeada;
}

/*
** glist_filter : GList Predicado Copia -> GList
** Devuelve una GList con los elementos de lista que cumplan con un predicado p
*/
GList glist_filter(GList lista, Predicado p, Copia c) {
  GList inicio = lista;
  GList listaFiltrada = glist_crear();
  do {
    if (p(lista->dato))
      listaFiltrada = glist_agregar(listaFiltrada, c(lista->dato));
    lista = lista->next;
  } while (lista->next != inicio);
  return listaFiltrada;
}

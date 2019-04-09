#include "strlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// En este trabajo usaremos listas doblemente enlazadas circulares

/*
** strlist_crear : -> StrList
** Devuelve una lista doblemente enlazada vacía (NULL).
*/
StrList strlist_crear() { return NULL; }

/*
** strlist_vacia : StrList -> Int
** Devuelve 1 si la lista es vacía, de lo contrario devuelve 0.
*/
int strlist_vacia(StrList lista) { return lista == NULL; }

/*
** strlist_destruir : StrList -> void
** Destruye la lista ingresada (libera toda la memoria dedicada).
*/
void strlist_destruir(StrList lista) {
  if (!strlist_vacia(lista)) {
    StrList i = lista;
    for (; i->next != lista;) {
      StrList sigtmp = i->next;
      free(i->dato);
      free(i);
      i = sigtmp;
    }
    free(i->dato);
    free(i);
  }
}

/*
** strlist_largo : StrList -> Int
** Devuelve el largo de la lista ingresada.
*/
int strlist_largo(StrList lista) {
  StrList inicio = lista;
  int i = 0;
  for (; lista->next != inicio; lista = lista->next) i++;
  return ++i;
}

/*
** strlist_devolver_dato : StrList Int -> Char*
** Devuelve la cadena de la lista en la posicion dada.
*/
char* strlist_devolver_dato(StrList lista, int pos, int largolista) {
  if (strlist_vacia(lista)) return NULL;
  if (largolista / 2 > pos)  // Recorro hacia adelante
    for (int i = 0; i < pos; i++) lista = lista->next;
  else {  // Recorro hacia atras
    int max = largolista - pos + 1;
    for (int i = 0; i <= max; i++) lista = lista->ant;
  }
  return lista->dato;
}

/*
** strlist_agregar : StrList Char* -> StrList
** Agrega un nuevo nodo con el dato dado en el final de la lista.
*/
StrList strlist_agregar(StrList lista, char* dato) {
  StrList nuevoNodo = malloc(sizeof(StrNode));
  nuevoNodo->dato = malloc(sizeof(char) * 45);
  strcpy(nuevoNodo->dato, dato);
  if (strlist_vacia(lista)) {
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
** strcharcat : Char* Char -> void
** Concatena el caracter a la cadena ingresada.
*/
void strcharcat(char* str, char c, int i) {
  // size_t len = strlen(str);
  *(str + i) = c;
  *(str + i + 1) = '\0';
}

/*
** strlist_llenar : StrList Char* -> StrList
** LLena la lista con datos obtenidos del archivo dado.
*/
StrList strlist_llenar(StrList lista, char* nombreArchivo) {
  FILE* archivo;
  archivo = fopen(nombreArchivo, "r");
  char *buffer = malloc(sizeof(char) * 45), bufferc;
  bufferc = fgetc(archivo);
  while (bufferc != EOF) {
    int i = 0;
    while (bufferc != '\n' && bufferc != '\r' && bufferc != EOF) {
      if (bufferc != '*') {
        strcharcat(buffer, bufferc, i);
        i++;
      }
      bufferc = fgetc(archivo);
    }
    lista = strlist_agregar(lista, buffer);
    while (bufferc != EOF && (bufferc == '\n' || bufferc == '\r'))
      bufferc = fgetc(archivo);
  }
  free(buffer);
  fclose(archivo);
  return lista;
}

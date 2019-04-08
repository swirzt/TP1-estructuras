#include "glist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GList glist_crear() { return NULL; }

int glist_vacia(GList lista) { return lista == NULL; }

void glist_destruir(GList lista) {
  if (!glist_vacia(lista)) {
    GList i = lista;
    for (; i->next != lista;) {
      GList sigtmp = i->next;
      free(i->dato);
      free(i);
      i = sigtmp;
    }
    free(i->dato);
    free(i);
  }
}

int glist_largo(GList lista) {
  GList inicio = lista;
  int i = 0;
  for (; lista->next != inicio; lista = lista->next) i++;
  return ++i;
}

void* glist_devolver_dato(GList lista, int pos) {
  if (glist_vacia(lista)) return NULL;
  int largolista = glist_largo(lista);
  if (largolista / 2 > pos)  // Recorro hacia adelante
    for (int i = 0; i < pos; i++) lista = lista->next;
  else {  // Recorro hacia atras
    int max = largolista - pos + 1;
    for (int i = 0; i <= max; i++) lista = lista->ant;
  }
  return lista->dato;
}

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

Persona* persona_crear(char* nombre, int edad, char* pais) {
  Persona* nuevaPersona = malloc(sizeof(Persona));
  char* nombrecpy = malloc(sizeof(char) * 14);
  strcpy(nombrecpy, nombre);
  char* paiscpy = malloc(sizeof(char) * 44);
  strcpy(paiscpy, pais);
  nuevaPersona->nombre = nombrecpy;
  nuevaPersona->pais = paiscpy;
  nuevaPersona->edad = edad;
  return nuevaPersona;
}

void archivoleer(FILE* archivo, char* buffer, char* bufferc) {
  int i = 0;
  for (; *bufferc != ',' || *bufferc != '\n'; i++) {
    *(buffer + i) = *bufferc;
    *bufferc = fgetc(archivo);
  }
  *(buffer + i) = '\0';
  *bufferc = fgetc(archivo);
}

GList llenar_lista_personas(GList lista, char* archivoPersonas) {
  FILE* archivo = fopen(archivoPersonas, "r");
  char* buffer1 = malloc(sizeof(char) * 45);
  char* buffer2 = malloc(sizeof(char) * 4);
  char* buffer3 = malloc(sizeof(char) * 45);
  char* bufferc = malloc(sizeof(char));
  *bufferc = fgetc(archivo);
  while (*bufferc != EOF) {
    // int i;
    // for (i = 0; bufferc != ','; i++) {
    //   *(buffer1 + i) = bufferc;
    //   bufferc = fgetc(archivo);
    // }
    // *(buffer1 + i) = '\0';
    // bufferc = fgetc(archivo);
    archivoleer(archivo, buffer1, bufferc);
    // for (i = 0; bufferc != ','; i++) {
    //   *(buffer2 + i) = bufferc;
    //   bufferc = fgetc(archivo);
    // }
    // *(buffer2 + i) = '\0';
    // bufferc = fgetc(archivo);
    archivoleer(archivo, buffer2, bufferc);
    // for (i = 0; bufferc != '\n'; i++) {
    //   *(buffer3 + i) = bufferc;
    //   bufferc = fgetc(archivo);
    // }
    // *(buffer3 + i) = '\0';
    // bufferc = fgetc(archivo);
    archivoleer(archivo, buffer3, bufferc);
    Persona* personaTmp = persona_crear(buffer1, atoi(buffer2), buffer3);
    lista = glist_agregar(lista, personaTmp);
  }
  free(buffer1);
  free(buffer2);
  free(buffer3);
  free(bufferc);
  fclose(archivo);
  return lista;
}

// GList glist_map(GList lista, Funcion f, Copia c){
//   GList inicio = lista;
//   GList listaMapeada =
//   for (;)
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "glist.h"

typedef struct {
  char* nombre;
  char* pais;
  int edad;
} Persona;

#define MAX_NOMBRES 15
#define MAX_PAISES 44

int existe_archivo() {
  if (access("nombres.txt", F_OK)) {
    printf("El archivo nombres.txt no existe\n");
    return 0;
  }
  return 1;
}

Persona* persona_crear(char* nombre, int edad, char* pais) {
  Persona* nuevaPersona = malloc(sizeof(Persona));
  char* nombrecpy = malloc(sizeof(char) * MAX_NOMBRES);
  strcpy(nombrecpy, nombre);
  char* paiscpy = malloc(sizeof(char) * MAX_PAISES);
  strcpy(paiscpy, pais);
  nuevaPersona->nombre = nombrecpy;
  nuevaPersona->pais = paiscpy;
  nuevaPersona->edad = edad;
  return nuevaPersona;
}

GList llenar_lista_personas(GList lista, char* archivoPersonas) {
  FILE* archivo = fopen(archivoPersonas, "r");
  char* buffer1 = malloc(sizeof(char) * MAX_NOMBRES);
  char* buffer2 = malloc(sizeof(char) * 4);
  char* buffer3 = malloc(sizeof(char) * MAX_PAISES);
  char bufferc = fgetc(archivo);
  while (!feof(archivo)) {
    int i;

    for (i = 0; bufferc != ','; i++) {
      *(buffer1 + i) = bufferc;
      bufferc = fgetc(archivo);
    }
    *(buffer1 + i) = '\0';
    bufferc = fgetc(archivo);

    for (i = 0; bufferc != ','; i++) {
      *(buffer2 + i) = bufferc;
      bufferc = fgetc(archivo);
    }
    *(buffer2 + i) = '\0';
    bufferc = fgetc(archivo);

    for (i = 0; bufferc != '\n'; i++) {
      *(buffer3 + i) = bufferc;
      bufferc = fgetc(archivo);
    }
    *(buffer3 + i) = '\0';
    bufferc = fgetc(archivo);

    Persona* personaTmp = persona_crear(buffer1, atoi(buffer2), buffer3);
    lista = glist_agregar(lista, personaTmp);
  }
  free(buffer1);
  free(buffer2);
  free(buffer3);
  fclose(archivo);
  return lista;
}

void* copiar_persona(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  Persona* copia = malloc(sizeof(Persona));
  copia->nombre = malloc(sizeof(char) * MAX_NOMBRES);
  strcpy(copia->nombre, datoPersona->nombre);
  copia->edad = datoPersona->edad;
  copia->pais = malloc(sizeof(char) * MAX_PAISES);
  strcpy(copia->pais, datoPersona->pais);
  return copia;
}

void destruye_personas(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  free(datoPersona->nombre);
  free(datoPersona->pais);
  free(datoPersona);
}

void* map1(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  int nombreLen = strlen(datoPersona->nombre);
  int paisLen = strlen(datoPersona->pais);
  for (int i = 0; i < nombreLen; i++)
    *(datoPersona->nombre + i) = *(datoPersona->nombre + i) + 1;
  for (int i = 0; i < paisLen; i++)
    *(datoPersona->pais + i) = *(datoPersona->pais + i) + 1;
  datoPersona->edad = datoPersona->edad + 1;
  return datoPersona;
}

void* map2(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  int nombreLen = strlen(datoPersona->nombre);
  int paisLen = strlen(datoPersona->pais);
  *(datoPersona->nombre + (rand() % nombreLen)) = '\0';
  *(datoPersona->pais + (rand() % paisLen)) = '\0';
  datoPersona->edad = datoPersona->edad / 2 * ((rand() % 100) + 1);
  return datoPersona;
}

int filter1(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  if (datoPersona->edad > 50) return 0;
  return 1;
}

int existe_e(char* palabra, int largo) {
  int hay = 0;
  for (int i = 0; i < largo && !hay; i++)
    if (*(palabra + i) == 'e') hay++;
  return hay;
}

int filter2(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  int largoNom = strlen(datoPersona->nombre);
  return existe_e(datoPersona->nombre, largoNom);
}

void glist_imprimir_persona(GList lista, char* nombreArchivo) {
  FILE* archivo = fopen(nombreArchivo, "w");
  int largolista = glist_largo(lista);
  for (int i = 0; i < largolista; i++) {
    Persona* tmp = lista->dato;
    fprintf(archivo, "%s,%d,%s\n", tmp->nombre, tmp->edad, tmp->pais);
    lista = lista->next;
  }
  fclose(archivo);
}

int main() {
  if (!existe_archivo()) return 0;
  GList personas = glist_crear();
  personas = llenar_lista_personas(personas, "personas.txt");

  GList map;
  map = glist_map(personas, map1, copiar_persona);
  glist_imprimir_persona(map, "personasmap1.txt");
  printf("Se completo el primer map\n");
  glist_destruir(map, destruye_personas);
  map = glist_map(personas, map2, copiar_persona);
  glist_imprimir_persona(map, "personasmap2.txt");
  printf("Se completo el segundo map\n");
  glist_destruir(map, destruye_personas);

  GList filter;
  filter = glist_filter(personas, filter1, copiar_persona);
  glist_imprimir_persona(filter, "personafilter1.txt");
  printf("Se completo el primer filter\n");
  glist_destruir(filter, destruye_personas);
  filter = glist_filter(personas, filter2, copiar_persona);
  glist_imprimir_persona(filter, "personafilter2.txt");
  printf("Se completo el segundo filter\n");
  glist_destruir(filter, destruye_personas);

  glist_destruir(personas, destruye_personas);
  return 1;
}
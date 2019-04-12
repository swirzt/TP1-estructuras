#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "glist.h"

/*
El programa toma los datos del archivo "personas.txt"
-"personas.txt" debe ser de la forma: nombre,edad,lugarDeNacimiento

Una vez leidos los datos procede de la siguiente forma:
1)Aplica la funcion datos_mas_uno() a la lista original por medio de un map
  Almacena los datos de la lista modificada en el archivo "personasmap1.txt"

2)Aplica la funcion datos_random() a la lista original por medio de un map
  Almacena los datos de la lista modificada en el archivo "personasmap2.txt"

3)Aplica la funcion crisis_edad() a la lista original por medio de un filter
  Almacena los datos de la lista filtrada en el archivo "personasfilter1.txt"

4)Aplica la funcion hay_e() a la lista original por medio de un filter
  Almacena los datos de la lista filtrada en el archivo "personasfilter2.txt"

Todos los archivos de salida son de la forma: nombre,edad,lugarDeNacimiento
*/

typedef struct {
  char* nombre;
  int edad;
  char* pais;
} Persona;

#define MAX_NOMBRES 17
#define MAX_PAISES 47

/*
** existe_archivo : -> Int
** Devuelve 1 si el archivo existe, de lo contrario notifica y devuelve 0.
*/
int existe_archivo() {
  if (access("nombres.txt", F_OK)) {
    printf("El archivo nombres.txt no existe\n");
    return 0;
  }
  return 1;
}

/*
** persona_crear : Char* Int Char* -> Persona*
** Recibe un nombre, una edad y un pais.
** Devuelve un puntero a Persona con los datos dados.
*/
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

/*
** llenar_lista_personas : GList Char* -> GList
** Recibe una lista y el nombre de un archivo que almacena Personas.
** Devuelve una lista con las Personas del archivo dentro.
*/
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

/*
** copiar_persona : void* -> void*
** Recibe un puntero Persona.
** Crea una copia en memoria y devuelve la copia.
*/
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

/*
** destruye_personas : void* -> void
** Recibe un puntero a Persona, libera toda la memoria que esta ocupa.
*/
void destruye_personas(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  free(datoPersona->nombre);
  free(datoPersona->pais);
  free(datoPersona);
}

/*
** datos_mas_uno : void* -> void*
** Recibe un puntero a Persona.
** Modifica todos sus datos +1 y la devuelve.
*/
void* datos_mas_uno(void* voidPersona) {
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

/*
** datos_random : void* -> void*
** Recibe un puntero a Persona, modifica sus valores de forma random.
*/
void* datos_random(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  int nombreLen = strlen(datoPersona->nombre);
  int paisLen = strlen(datoPersona->pais);
  *(datoPersona->nombre + (rand() % nombreLen)) = '\0';
  *(datoPersona->pais + (rand() % paisLen)) = '\0';
  datoPersona->edad = datoPersona->edad / 2 * ((rand() % 100) + 1);
  return datoPersona;
}

/*
** crisis_edad : void* -> Int
** Recibe un puntero a Persona, devuelve 1 si su edad es menor a 50.
** De lo contrario devuelve 0.
*/
int crisis_edad(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  if (datoPersona->edad > 50) return 0;
  return 1;
}

/*
** hay_e : void* -> Int
** Recibe un puntero a Persona.
** Devuelve 1 si en el nombre de la Persona existe una 'e'.
*/
int hay_e(void* voidPersona) {
  Persona* datoPersona = voidPersona;
  int largoNom = strlen(datoPersona->nombre);
  char* nombre = datoPersona->nombre;
  int hay = 0;
  for (int i = 0; i < largoNom && !hay; i++)
    if (*(nombre + i) == 'e') hay++;
  return hay;
}

/*
** glist_imprimir_persona : GList Char* -> void
** Recibe una lista de Personas y un nombre de archivo.
** Almacena los datos de la lista en el archivo dado.
*/
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

  GList listamod;

  listamod = glist_map(personas, datos_mas_uno, copiar_persona);  // map1
  glist_imprimir_persona(listamod, "personasmap1.txt");
  printf("Se completo el primer map\n");
  glist_destruir(listamod, destruye_personas);

  listamod = glist_map(personas, datos_random, copiar_persona);  // map2
  glist_imprimir_persona(listamod, "personasmap2.txt");
  printf("Se completo el segundo map\n");
  glist_destruir(listamod, destruye_personas);

  listamod = glist_filter(personas, crisis_edad, copiar_persona);  // filter1
  glist_imprimir_persona(listamod, "personafilter1.txt");
  printf("Se completo el primer filter\n");
  glist_destruir(listamod, destruye_personas);

  listamod = glist_filter(personas, hay_e, copiar_persona);  // filter2
  glist_imprimir_persona(listamod, "personafilter2.txt");
  printf("Se completo el segundo filter\n");
  glist_destruir(listamod, destruye_personas);

  glist_destruir(personas, destruye_personas);
  return 1;
}
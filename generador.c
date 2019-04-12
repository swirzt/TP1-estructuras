#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "glist.h"

/*
El programa toma los datos de los archivos "nombres.txt" y "paises.txt".
-"nombres.txt" debe contener un nombre por línea.
-"paises.txt" debe contener un pais/ciudad por línea.

Al ser ejecutado pide al usuario el ingreso de la cantidad de personas a crear
Imprime todas las personas en el archivo "personas.txt"
-Cada linea es de la forma: nombre,edad,lugarDeNacimiento
*/

#define MAX_NOMBRES 17
#define MAX_PAISES 47

#define CADENA_MAYOR MAX_NOMBRES > MAX_PAISES ? MAX_NOMBRES : MAX_PAISES

/*
** falta_archivo : -> Int
** Si los 2 archivos existen devuelve 0, de lo contrario imprime lo que falta y
** devuelve 1.
*/
int falta_archivo() {
  int i = 0;
  if (access("nombres.txt", F_OK)) {
    printf("El archivo nombres.txt no existe\n");
    i = 1;
  }
  if (access("paises.txt", F_OK)) {
    printf("El archivo paises.txt no existe\n");
    i = 1;
  }
  return i;
}

/*
** Inicializa el generador de random a partir de la hora actual del sistema.
*/
void seedrand() {
  time_t t;
  srand(time(&t));
}

/*
** ingreso_cantidad : -> Int
** Pide el ingreso de la cantidad de personas a generar y lo devuelve.
*/
int ingreso_cantidad() {
  int i;
  printf("Ingrese la cantidad de personas a generar:\n>");
  scanf("%d", &i);
  return i;
}

/*
** es_no_letra : Char -> Int
** Recibe un caracter, devuelve 1 si no es una letra, de lo contrario 0.
** Comparaciones hechas en los valores del rango ASCII
*/
int es_no_letra(char c) {
  int tipo = 0;
  if (c > 0 && c < 32)
    tipo++;
  else if (c > 32 && c < 65)
    tipo++;
  else if (c > 90 && c < 97)
    tipo++;
  else if (c > 122 && c < 128)
    tipo++;
  else if (c > 154 && c < 160)
    tipo++;
  else if (c > 165 && c < 181)
    tipo++;
  else if (c > 183 && c < 198)
    tipo++;
  else if (c > 199 && c < 210)
    tipo++;
  else if (c > 212 && c < 224)
    tipo++;
  else if (c > 237 && c < 256)
    tipo++;
  return tipo;
}

/*
** glist_llenar : StrList Char* -> StrList
** LLena la lista con datos obtenidos del archivo dado.
*/
GList glist_llenar(GList lista, char* nombreArchivo) {
  FILE* archivo;
  archivo = fopen(nombreArchivo, "r");
  char *buffer = malloc(sizeof(char) * CADENA_MAYOR), bufferc;
  bufferc = fgetc(archivo);
  while (bufferc != EOF) {
    int i = 0;
    while (bufferc != '\n' && bufferc != '\r' && bufferc != EOF) {
      if (!es_no_letra(bufferc)) {
        *(buffer + i) = bufferc;
        i++;
      }
      *(buffer + i + 1) = '\0';
      bufferc = fgetc(archivo);
    }
    char* newbuffer = malloc(sizeof(char) * 45);
    strcpy(newbuffer, buffer);
    lista = glist_agregar(lista, newbuffer);
    while (bufferc != EOF && (bufferc == '\n' || bufferc == '\r'))
      bufferc = fgetc(archivo);
  }
  free(buffer);
  fclose(archivo);
  return lista;
}

/*
 ** genera_personas : Int GList GList -> void
 ** Recibe la cantidad a generar y 2 listas, escribe los datos generados
 ** aleatoriamente en el archivo "personas.txt".
 */
void genera_personas(int cantDatos, GList nombres, GList paises) {
  int rndNombres, rndPaises, rndEdad;
  int largoNombres = glist_largo(nombres);
  int largoPaises = glist_largo(paises);
  FILE* archivo;
  archivo = fopen("personas.txt", "w+");
  for (int i = 0; i < cantDatos; i++) {
    rndNombres = rand() % largoNombres;
    rndPaises = rand() % largoPaises;
    rndEdad = (rand() % 100) + 1;
    char* nombre = glist_devolver_dato(nombres, rndNombres, largoNombres);
    fprintf(archivo, "%s,", nombre);
    fprintf(archivo, "%d,", rndEdad);
    char* pais = glist_devolver_dato(paises, rndPaises, largoPaises);
    fprintf(archivo, "%s\n", pais);
  }
  fclose(archivo);
}

int main() {
  if (falta_archivo()) return 0;
  seedrand();  // Si se quiere tener resultados iguales en cada ejecucion se
               // debe comentar esta linea
  int cantDatos = ingreso_cantidad();
  GList nombres, paises;
  nombres = glist_llenar(glist_crear(), "nombres.txt");
  paises = glist_llenar(glist_crear(), "paises.txt");
  genera_personas(cantDatos, nombres, paises);
  glist_destruir(nombres, free);
  glist_destruir(paises, free);
  printf("Se generaron %d personas aleatorias.\n", cantDatos);
  return 0;
}

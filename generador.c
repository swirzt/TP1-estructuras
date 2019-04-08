#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "strlist.h"

/*
** revisa_archivos : -> Int
** Si los 2 archivos existen devuelve 0, de lo contrario imprime lo que falta y
** devuelve 1.
*/
int revisa_archivos() {
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
 ** genera_personas : Int StrList Strlist -> void
 ** Recibe la cantidad a generar y las 2 listas y escribe los datos generados
 ** aleatoriamente en el archivo "personas.txt".
 */
void genera_personas(int cantDatos, StrList nombres, StrList paises) {
  int rndNombres, rndPaises, rndEdad;
  int largoNombres = strlist_largo(nombres);
  int largoPaises = strlist_largo(paises);
  FILE* archivo;
  archivo = fopen("personas.txt", "w+");
  for (int i = 0; i < cantDatos; i++) {
    rndNombres = rand() % largoNombres;
    rndPaises = rand() % largoPaises;
    rndEdad = (rand() % 100) + 1;
    fprintf(archivo, "%s,", strlist_devolver_dato(nombres, rndNombres));
    fprintf(archivo, "%s,", strlist_devolver_dato(paises, rndPaises));
    fprintf(archivo, "%d\n", rndEdad);
  }
  fclose(archivo);
}

int main() {
  if (revisa_archivos()) return 0;
  seedrand();  // Si se quiere tener resultados iguales en cada ejecucion se
               // debe comentar esta linea
  int cantDatos = ingreso_cantidad();
  StrList nombres, paises;
  nombres = strlist_llenar(strlist_crear(), "nombres.txt");
  paises = strlist_llenar(strlist_crear(), "paises.txt");
  genera_personas(cantDatos, nombres, paises);
  strlist_destruir(nombres);
  strlist_destruir(paises);
  printf("Se generaron %d personas aleatorias.\n", cantDatos);
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE* archivo = fopen("paises.txt", "r");
  size_t max = 0;
  char* tmp = malloc(sizeof(char) * 50);
  // char tmpp = fgetc(archivo);
  // while (tmpp != EOF) {
  //   int i = 0;
  //   while (tmpp != '\n') {
  //     *(tmp + i) = tmpp;
  //     tmpp = fgetc(archivo);
  //   }
  //   *(tmp + i) = '\0';
  //   printf("%s\n", tmp);
  //   if (strlen(tmp) > max) max = strlen(tmp);
  //   tmpp = fgetc(archivo);
  // }
  for (int i = 0; i < 2800; i++) {
    fscanf(archivo, "%s", tmp);
    if (strlen(tmp) > max) max = strlen(tmp);
  }
  printf("%ld", max);
  return 0;
}
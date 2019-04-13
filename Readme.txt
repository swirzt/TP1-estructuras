Trabajo práctico N°1: Listas enlazadas

Para compilar los programas de forma automatica se debe abrir la consola en
la carpeta que contiene los archivos.
Una vez alli se debe usar el comando $make que se encargara de compilar
todos los archivos necesarios.

El programa "generador" al ejecutarse genera una lista de personas con los siguientes datos:
*Nombre
*Edad
*País
Dicho programa requiere que se hayan escrito los nombres en el archivo "nombres.txt"
y los paises en "paises.txt".
La lista de personas generada se escribirá en "personas.txt".

El programa "mapfilter" deberá ejecutarse para aplicar funciones sobre
las personas en el archivo "personas.txt".
Los resultados de aplicar dichos map o filter serán escritos en sus respectivos archivos:
-"personafilter1.txt"
-"personafilter2.txt"
-"personasmap1.txt"
-"personasmap2.txt"

Si se desea eliminar el archivo generado en el primer programa use el comando:
$make limpiapersonas
Si se desea eliminar los archivos generados en el segundo programa use el comando:
$make limpiamapfilter
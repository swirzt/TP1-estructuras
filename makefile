CC=gcc
FLAGS=-std=c99 -pedantic -Wall

all: glist.o generador mapfilter

glist.o: glist.c glist.h
	$(CC) -c glist.c $(FLAGS)

generador: generador.c glist.o
	$(CC) -o generador generador.c glist.o $(FLAGS)

mapfilter: mapfilter.c glist.o
	$(CC) -o mapfilter mapfilter.c glist.o $(FLAGS)

limpiapersonas:
	rm personas.txt

limpiamapfilter:
	rm personasmap1.txt
	rm personasmap2.txt
	rm personafilter1.txt
	rm personafilter2.txt

#ifndef __GIM_H__
#define __GIM_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lista.h"
#include "heap.h"

#define OK 0
#define ERROR -1



typedef struct pokemon{
	
	char nombre[100];
	int velocidad;
	int defensa;
	int ataque;
	int cantidad_bonificador;
 
} pokemon_t;

typedef struct {

	char nombre[100];
	lista_t* pokemones;
	int cantidad_pokemones;

} entrenador_t;

typedef struct gimnasio{

	char nombre[100];
	int dificultad;
	int id_puntero_funcion;
	lista_t* entrenador;
	int cantidad_entrenadores;

} gimnasio_t;

typedef struct{

	char nombre[100];
	lista_t* pokemones_obtenidos;
	lista_t* pokemones_para_combatir;
	int cantidad_pokemones;

}personaje_t;

/*Carga toda la informacion del archivo de gimnasios a un heap y lo devuelve*/

heap_t* cargar_gimnasios(const char* ruta_archivo);

/*Carga toda la informacion del archivo del personaje a un personaje y lo devuelve*/

personaje_t* cargar_personaje(const char* ruta_archivo);

/*Destruye el personaje liberando toda la memoria reservada*/

void destruir_personaje(personaje_t* personaje);


#endif /*__GIM_H__*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cargas.h"

#define OK 0
#define ERROR -1
#define FORMATO_LECTURA_POKEMON "%99[^;];%i;%i;%i\n"
#define FORMATO_LECTURA_ENTRENADOR "%99[^\n]\n"
#define FORMATO_LECTURA_GIMNASIO "%99[^;];%i;%i\n"
#define FORMATO_LECTURA_LETRA "%c\n"

void destruir_e_y_p(gimnasio_t* gimnasio){
	if(!gimnasio->entrenador) return;
	entrenador_t* entrenador;
	pokemon_t* pokemon;
	for(int i = 0;i<gimnasio->cantidad_entrenadores;i++){
		entrenador = lista_elemento_en_posicion(gimnasio->entrenador, i);
		if(entrenador->pokemones != NULL){
			for(int j = 0;j<entrenador->cantidad_pokemones;j++){
				pokemon = lista_elemento_en_posicion(entrenador->pokemones,j);
				free(pokemon);
			}
			lista_destruir(entrenador->pokemones);
		}
		free(entrenador);
	}
	lista_destruir(gimnasio->entrenador);
}

void destruir_cosa(gimnasio_t* c){
	if(!c) return;
	destruir_e_y_p(c);
    free(c);
}


int comparar_cosas(void* gimnasio1, void* gimnasio2){
	if(!gimnasio1 || !gimnasio2){
		return 0;
	}
	if(((gimnasio_t*)gimnasio1)->dificultad > ((gimnasio_t*)gimnasio2)->dificultad){
		return 1;
	}
	if(((gimnasio_t*)gimnasio2)->dificultad > ((gimnasio_t*)gimnasio1)->dificultad){
		return -1;
	}
	return 0;
}


void destructor_de_cosas(void* elemento){
    if(!elemento)
        return;
    destruir_cosa((gimnasio_t*)elemento);
}

int leer_pokemones(FILE* archivo_gimnasio,pokemon_t* pokemon){

	/*char cadena[1000];		
  	char* linea=fgets(cadena,1000,archivo_gimnasio);
	if(!linea){
		return ERROR;
	}*/
    return fscanf(archivo_gimnasio,FORMATO_LECTURA_POKEMON, pokemon->nombre, &(pokemon->velocidad), &(pokemon->defensa), &(pokemon->ataque));
}

 
int leer_entrenador(FILE* archivo_gimnasio,entrenador_t* entrenador){

    return fscanf(archivo_gimnasio,FORMATO_LECTURA_ENTRENADOR, entrenador->nombre);
}

int leer_gimnasio(FILE* archivo_gimnasio, gimnasio_t* gym){
	
    return fscanf(archivo_gimnasio,FORMATO_LECTURA_GIMNASIO, gym->nombre, &(gym->dificultad), &(gym->id_puntero_funcion));
}

int leer_letra(FILE* archivo_gimnasio,char* letra){

	char cadena[1000];
  	char* linea=fgets(cadena,1000,archivo_gimnasio);
	if(!linea){
		return ERROR;
	}
    return sscanf(linea,FORMATO_LECTURA_LETRA, letra);
}

pokemon_t* crear_pokemon(){

	pokemon_t* pokemon=calloc(1,sizeof(pokemon_t));
	if(!pokemon) return NULL;
	return pokemon;
}

entrenador_t* crear_entrenador(){

	
	entrenador_t* entrenador=calloc(1,sizeof(entrenador_t));
	if(!entrenador) return NULL;
	entrenador->pokemones=lista_crear();
	return entrenador;
}

gimnasio_t* crear_gym(){

	
	gimnasio_t* gimnasio=calloc(1,sizeof(gimnasio_t));
	if(!gimnasio) return NULL;
	gimnasio->entrenador=lista_crear();
	return gimnasio;
}

int asignar_pokemones(pokemon_t* pokemon, pokemon_t pokemon_aux){

	strcpy(pokemon->nombre,pokemon_aux.nombre);
	pokemon->velocidad=pokemon_aux.velocidad;
	pokemon->defensa=pokemon_aux.defensa;
	pokemon->ataque=pokemon_aux.ataque;
}

int asignar_gimnasio(gimnasio_t* gimnasio, gimnasio_t gimnasio_aux){

	strcpy(gimnasio->nombre,gimnasio_aux.nombre);
	gimnasio->dificultad=gimnasio_aux.dificultad;
	gimnasio->id_puntero_funcion=gimnasio_aux.id_puntero_funcion;
}

heap_t* cargar_gimnasios(const char* ruta_archivo){

	FILE* archivo_gimnasio;
	archivo_gimnasio=fopen(ruta_archivo,"r");
	if(archivo_gimnasio==NULL){
		return NULL;
	}
	gimnasio_t gimnasio_aux;
	entrenador_t entrenador_aux;
	pokemon_t pokemon_aux;
	char letra,letra_E,letra_P;
	int leidos_letra=leer_letra(archivo_gimnasio,&letra);
	int leidos=leer_gimnasio(archivo_gimnasio,&gimnasio_aux);
	heap_t* heap=heap_crear(comparar_cosas,destructor_de_cosas);
	if(!heap) return NULL;
	while(leidos!=EOF && leidos==3 && letra=='G'){
		gimnasio_t* gimnasio=crear_gym();
		if(!gimnasio) return NULL;
		leidos_letra=leer_letra(archivo_gimnasio,&letra_E);
		if(letra_E=='E'){
			int leidos_entrenador=leer_entrenador(archivo_gimnasio,&entrenador_aux);
			while(leidos!=EOF && leidos==3 && leidos_entrenador==1 && letra=='G' && letra_E=='E'){
				entrenador_t* entrenador=crear_entrenador();
				if(!entrenador){
					free(gimnasio);
					fclose(archivo_gimnasio);
					return NULL;
				}
				strcpy(entrenador->nombre,entrenador_aux.nombre);
				gimnasio->cantidad_entrenadores=gimnasio->cantidad_entrenadores+1;
				leidos_letra=leer_letra(archivo_gimnasio,&letra_P);
				if(letra_P=='P'){
					int leidos_pokemon=leer_pokemones(archivo_gimnasio,&pokemon_aux);
					while(leidos!=EOF && leidos==3 && leidos_entrenador==1 && leidos_pokemon==4 && letra=='G' && letra_E=='E' && letra_P=='P'){
						pokemon_t* pokemon=crear_pokemon();
						if(!pokemon){
							free(gimnasio);
							free(entrenador);
							fclose(archivo_gimnasio);
							return NULL;
						}
						asignar_pokemones(pokemon,pokemon_aux);
						lista_insertar(entrenador->pokemones,pokemon);
						entrenador->cantidad_pokemones=entrenador->cantidad_pokemones+1;
						leidos_letra=leer_letra(archivo_gimnasio,&letra_P);
						if(letra_P=='P'){
							leidos_pokemon=leer_pokemones(archivo_gimnasio,&pokemon_aux);
						}
					}
				}
				lista_apilar(gimnasio->entrenador,entrenador);
				if(letra_P=='E'){
					letra_E='E';
					leidos_entrenador=leer_entrenador(archivo_gimnasio,&entrenador_aux);
				}
				else letra_E='G';
			}
		}
		asignar_gimnasio(gimnasio,gimnasio_aux);
		heap_insertar(heap,gimnasio);
		leidos=leer_gimnasio(archivo_gimnasio,&gimnasio_aux);
		
	}
	fclose(archivo_gimnasio);
	return heap;
}



//------------------PERSONAJE-------------------




int leer_pokemones_personaje(FILE* archivo_personaje,pokemon_t* pokemon){

    return fscanf(archivo_personaje,FORMATO_LECTURA_POKEMON, pokemon->nombre, &(pokemon->velocidad), &(pokemon->defensa), &(pokemon->ataque));
}

 
int leer_personaje(FILE* archivo_personaje,personaje_t* personaje){

    return fscanf(archivo_personaje,FORMATO_LECTURA_ENTRENADOR, personaje->nombre);
}

personaje_t* crear_personaje(){

	
	personaje_t* personaje=calloc(1,sizeof(personaje_t));
	if(!personaje) return NULL;
	personaje->pokemones_para_combatir=lista_crear();
	personaje->pokemones_obtenidos=lista_crear();
	return personaje;
}

int asignar_personaje(personaje_t* personaje, personaje_t personaje_aux){

	strcpy(personaje->nombre,personaje_aux.nombre);
}

personaje_t* cargar_personaje(const char* ruta_archivo){

	FILE* archivo_personaje;
	archivo_personaje=fopen(ruta_archivo,"r");
	if(archivo_personaje==NULL){
		return NULL;
	}
	personaje_t personaje_aux;
	pokemon_t pokemon_aux;
	int contador=0;
	char letra,letra_P;
	int leidos_letra=leer_letra(archivo_personaje,&letra);
	int leidos=leer_personaje(archivo_personaje,&personaje_aux);
	if(leidos!=EOF && leidos==1 && letra=='E'){
		personaje_t* personaje=crear_personaje();
		if(!personaje) return NULL;
		leidos_letra=leer_letra(archivo_personaje,&letra_P);
		if(letra_P=='P'){
			int leidos_pokemon=leer_pokemones(archivo_personaje,&pokemon_aux);
			while(leidos_pokemon!=EOF && leidos_pokemon==4 && letra_P=='P'){
				pokemon_t* pokemon=crear_pokemon();
				if(!pokemon){
					lista_destruir(personaje->pokemones_obtenidos);
					lista_destruir(personaje->pokemones_para_combatir);
					free(personaje);
					fclose(archivo_personaje);
					return NULL;
				}
				asignar_pokemones(pokemon,pokemon_aux);
				personaje->cantidad_pokemones=personaje->cantidad_pokemones+1;
				if(personaje->cantidad_pokemones>6) lista_insertar(personaje->pokemones_obtenidos,pokemon);
				else lista_insertar(personaje->pokemones_para_combatir,pokemon);
				leidos_letra=leer_letra(archivo_personaje,&letra_P);
				leidos_pokemon=leer_pokemones(archivo_personaje,&pokemon_aux);
			}
		}
		asignar_personaje(personaje,personaje_aux);
		fclose(archivo_personaje);
		return personaje;
	}
	fclose(archivo_personaje);
	return NULL;
}

void destruir_personaje(personaje_t* personaje){
	if(!personaje) return;
	if(!personaje->pokemones_obtenidos && !personaje->pokemones_para_combatir) return free(personaje);
	pokemon_t* pokemon;
	for(int i=0;i<personaje->cantidad_pokemones; i++ ){
		if(i>=6) pokemon=lista_elemento_en_posicion(personaje->pokemones_obtenidos,i-6);
		else pokemon=lista_elemento_en_posicion(personaje->pokemones_para_combatir,i);
		free(pokemon);
	}
	lista_destruir(personaje->pokemones_obtenidos);
	lista_destruir(personaje->pokemones_para_combatir);
	free(personaje);
}
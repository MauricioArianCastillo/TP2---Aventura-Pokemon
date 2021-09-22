#include<stdio.h>
#include<stdbool.h>
#include "batallas.h"

int funcion_batalla_1(void* pkm_1, void* pkm_2){

	if(((pokemon_t*)pkm_1)->velocidad>((pokemon_t*)pkm_2)->velocidad){
		return GANO_PRIMERO;
	}
	else return GANO_SEGUNDO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){

	if(((pokemon_t*)pkm_1)->ataque>((pokemon_t*)pkm_2)->ataque){
		return GANO_PRIMERO;
	}
	else return GANO_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){

	if(((pokemon_t*)pkm_1)->defensa>((pokemon_t*)pkm_2)->defensa){
		return GANO_PRIMERO;
	}
	else return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){

	if(strcmp(((pokemon_t*)pkm_1)->nombre,((pokemon_t*)pkm_2)->nombre) == 1 ){
		return GANO_PRIMERO;
	}
	else return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){

	if(strlen(((pokemon_t*)pkm_1)->nombre)>strlen(((pokemon_t*)pkm_2)->nombre)){
		return GANO_PRIMERO;
	}
	else return GANO_SEGUNDO;
}


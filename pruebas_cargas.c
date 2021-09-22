#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"
#include "cargas.h"
#include "heap.h"
#include "lista.h"



void pruebas_cargar_gimnasios(){

	heap_t* heap=cargar_gimnasios("Gimnasios.txt");
	pa2m_afirmar(heap!=NULL,"El heap no es NULL");
	pa2m_afirmar(heap->tope==3,"El heap tiene la cantidad correcta de gimnasios");
	gimnasio_t* gimnasio;
	entrenador_t* entrenador;
	pokemon_t* pokemon;
	int tope=heap->tope;
	printf("tope:%d\n",tope);
	for(int i=0;i<tope;i++){
		printf("GIMNASIO:\n\n");
		gimnasio=heap->vector[0];
		printf("nombre:%s\ndificultad:%d\npunt:%d\ncantidad_entr:%d\n\n",gimnasio->nombre,gimnasio->dificultad,gimnasio->id_puntero_funcion,gimnasio->cantidad_entrenadores);
		
		for(size_t e=0;e<gimnasio->cantidad_entrenadores;e++){
			printf("ENTRENADOR:\n");
			entrenador=lista_elemento_en_posicion(gimnasio->entrenador,e);
			printf("nombre entrenador:%s\ncantidad pokemones:%d\n\n",entrenador->nombre,entrenador->cantidad_pokemones);
			printf("POKEMONES:\n");
			for(size_t o=0;o<entrenador->cantidad_pokemones;o++){
				
				pokemon=lista_elemento_en_posicion(entrenador->pokemones,o);
				printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);
				printf("\n");
			}
			printf("\n");
		}
		printf("\n\n");
		if(heap->tope>1)heap_extraer_raiz(heap);
	}
	heap_destruir(heap);

}
void pruebas_cargar_personaje(){

	personaje_t* personaje=cargar_personaje("Personaje_pierde.txt");
	pokemon_t* pokemon=NULL;
	pa2m_afirmar(personaje!=NULL,"El personaje no es NULL");
	pa2m_afirmar(personaje->cantidad_pokemones==18,"El personaje tiene la cantidad correcta de pokemones");
	printf("\nPERSONAJE:\n\n");
	printf("Nombre:%s\nnPokemones totales:%d\n\n",personaje->nombre,personaje->cantidad_pokemones);
	for(size_t i=0;i<personaje->cantidad_pokemones;i++){
		if(i>=6) pokemon=lista_elemento_en_posicion(personaje->pokemones_obtenidos,i-6);
		else pokemon=lista_elemento_en_posicion(personaje->pokemones_para_combatir,i);
		printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);
		printf("\n");
	}
	destruir_personaje(personaje);
}

void main(){
	pa2m_nuevo_grupo("PRUEBAS DE CARGA");
	pruebas_cargar_gimnasios();
	pruebas_cargar_personaje();
	pa2m_mostrar_reporte();
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "heap.h"
#include "cargas.h"
#include "batallas.h"

#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

/*---------------------FUNCIONES DE INFORMAR---------------------*/

void mostrar_gimnasio(gimnasio_t* gimnasio){
	
	printf("GIMNASIO:\n\n");
	printf("nombre:%s\ndificultad:%d\nid_puntero_funcion:%d\ncantidad_entrenadores:%d\n\n",gimnasio->nombre,gimnasio->dificultad,gimnasio->id_puntero_funcion,gimnasio->cantidad_entrenadores);

	for(size_t e=0;e<gimnasio->cantidad_entrenadores;e++){
		printf("ENTRENADOR:\n");
		entrenador_t* entrenador=lista_elemento_en_posicion(gimnasio->entrenador,e);
		printf("nombre entrenador:%s\ncantidad pokemones:%d\n\n",entrenador->nombre,entrenador->cantidad_pokemones);
		printf("POKEMONES:\n");
		for(size_t o=0;o<entrenador->cantidad_pokemones;o++){
			
			pokemon_t* pokemon=lista_elemento_en_posicion(entrenador->pokemones,o);
			printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);
			printf("\n");
		}
		printf("\n");
	}
	printf("\n\n");
	
}

void mostrar_personaje(personaje_t* personaje){

	printf("\nPERSONAJE:\n\n");
	printf("Nombre:%s\nnPokemones totales:%d\n\n",personaje->nombre,personaje->cantidad_pokemones);
	printf("\nPOKEMONES:\n\n");
	pokemon_t* pokemon;
	printf("POKEMONES PARA COMBATIR:\n\n");
	for(size_t i=0;i<personaje->cantidad_pokemones;i++){
		if(i==6) printf("POKEMONES OBTENIDOS:\n\n");
		if(i>=6) pokemon=lista_elemento_en_posicion(personaje->pokemones_obtenidos,i-6);
		else pokemon=lista_elemento_en_posicion(personaje->pokemones_para_combatir,i);
		printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);
		printf("\n");
	}
}

void mostrar_pokemones(personaje_t* personaje){

	printf("\nPOKEMONES:\n\n");
	printf("POKEMONES PARA COMBATIR:\n\n");
	pokemon_t* pokemon;
	for(size_t i=0;i<personaje->cantidad_pokemones;i++){
		if(i==6) printf("POKEMONES OBTENIDOS:\n\n");
		if(i>=6){
			printf("POKEMON NRO: %ld\n",i+1);
			pokemon=lista_elemento_en_posicion(personaje->pokemones_obtenidos,i-6);
			printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);
		} 
		else {
			printf("POKEMON NRO: %ld\n",i+1);
			pokemon=lista_elemento_en_posicion(personaje->pokemones_para_combatir,i);
			printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);	
		}
		
		printf("\n");
	}

}

int mostrar_pokemones_lider(entrenador_t* entrenador){
	if(!entrenador) return ERROR;
	printf("\nPOKEMONES:\n\n");
	for(size_t i=0;i<entrenador->cantidad_pokemones;i++){
		
		printf("POKEMON NRO: %ld\n",i+1);
		pokemon_t* pokemon=lista_elemento_en_posicion(entrenador->pokemones,i);
		printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);	
		printf("\n");
	}

}

/*---------------------FUNCIONES DE CAMBIAR POKEMON---------------------*/

void swap_pokemon(pokemon_t* pokemon1, pokemon_t* pokemon2){
	pokemon_t pokemon_aux=*pokemon1;
	*pokemon1=*pokemon2;
	*pokemon2=pokemon_aux;
}

void escanear_numeros(size_t* n_1, size_t* n_2,personaje_t* personaje){

	size_t n1,n2;
	mostrar_pokemones(personaje);
	printf("Para intercambiar seleccionar ingresando primero el numero del pokemon para combatir, y luego ingresar el numero del pokemon de los pokemones obtenidos.\n");
	printf("Pokemon para combatir:");
	scanf("%zu",&n1);
	while(n1>6 || n1<1){
		printf("ERROR. Ingresar un numero valido:");
		scanf("%zu",&n1);
	}
	fflush(stdin);
	printf("Pokemon de los obtenidos:");
	scanf("%zu",&n2);
	while(n2<7 || n2>6+personaje->pokemones_obtenidos->cantidad){
		printf("ERROR. Ingresar un numero valido:");
		scanf("%zu",&n2);
	}
	fflush(stdin);
	*n_1=n1;
	*n_2=n2;
}

void cambiar_pokemones(personaje_t* personaje){

	size_t n1,n2;
	escanear_numeros(&n1,&n2,personaje);
	pokemon_t* pokemon1=lista_elemento_en_posicion(personaje->pokemones_para_combatir,n1-1);
	pokemon_t* pokemon2=lista_elemento_en_posicion(personaje->pokemones_obtenidos,n2-7);
	swap_pokemon(pokemon1,pokemon2);
	printf("Se ha intercambiado exitosamente!");
	char y_n;
	printf("Desea continuar? Y/N");
	scanf(" %c",&y_n);
	while(y_n=='Y'){
		system("clear");
		escanear_numeros(&n1,&n2,personaje);
		pokemon_t* pokemon1=lista_elemento_en_posicion(personaje->pokemones_para_combatir,n1-1);
		pokemon_t* pokemon2=lista_elemento_en_posicion(personaje->pokemones_obtenidos,n2-7);
		swap_pokemon(pokemon1,pokemon2);
		printf("Se ha intercambiado exitosamente!");
		printf("Desea continuar? Y/N");
		scanf(" %c",&y_n);
	}
}

/*----------------------MENU DE VICTORIA Y DE DERROTA---------------------*/


char opcion_victoria(char opcion,bool t){

	char c;
	printf("MENU DE VICTORIA:\n\n");
	if(t==false) printf("T:Obtener un pokemon del lider (solo 1 intento)\nC:Cambiar los pokemones de batalla\nN:Poximo gimnasio\n");
	else printf("C:Cambiar los pokemones de batalla\nN:Poximo gimnasio\n");
	printf("Ingrese la opcion que desee:\n");
	scanf(" %c",&opcion);
	while(opcion!='T' && opcion!='C' && opcion!='N'){
		printf("Ingresar una opcion valida:");
		scanf(" %c",&opcion);
		if(t==true && opcion=='T') opcion='A';
	}
	system("clear");
	return opcion;
}

int case_T(entrenador_t* entrenador,personaje_t* personaje){

	int verificar=0;
	if(mostrar_pokemones_lider(entrenador)==ERROR) verificar=ERROR;
	printf("Seleccionar ingresando  el numero del pokemon del lider que desee.\n");
	printf("Pokemon para combatir:");
	size_t n1;
	scanf("%zu",&n1);
	pokemon_t* pokemon_obtenido=lista_elemento_en_posicion(entrenador->pokemones,n1-1),pokemon_aux;
	pokemon_aux=*pokemon_obtenido;
	lista_borrar_de_posicion(entrenador->pokemones,n1-1);
	entrenador->cantidad_pokemones=entrenador->cantidad_pokemones-1;
	*pokemon_obtenido=pokemon_aux;
	lista_insertar(personaje->pokemones_obtenidos,pokemon_obtenido);
	personaje->cantidad_pokemones=personaje->cantidad_pokemones+1;
	printf("Se ha obtenido exitosamente!\n");
	system("clear");
	if(verificar==ERROR) return ERROR;
	return OK;
}

int menu_victoria(heap_t* heap,entrenador_t* entrenador, personaje_t* personaje, bool* siguiente,bool*termina,int* tope){

	bool t=false;
	char opcion='A',c;
	int verificar=0;
	*tope=*tope-1;
	if(*tope!=0){																						
		printf("Felicidades ganaste el gimnasio!!\n\n");
		while(opcion!='F' && heap->tope!=0){
			opcion=opcion_victoria(opcion,t);
			switch(opcion){
				case 'T':
					if(case_T(entrenador,personaje)==ERROR) verificar=ERROR;
					t=true;
					break;
				case 'C':
					cambiar_pokemones(personaje);
					system("clear");
					break;
				case 'N':
					*siguiente=true;
					opcion='F';
					break;
			}
		}
	}
	if(*tope==0){
		*termina=true;
		printf("Felicidades!!! Te converstiste en maestro pokemon!!!! :D\n");
		scanf(" %c",&c);
	}
	if(verificar==ERROR) return ERROR;
	else return OK;
	
}

char opcion_derrota(char opcion){

	char c;
	printf("C:Cambiar los pokemones de batalla\nR:Reintenta la batalla\nF:Finaliza la partida\n");
	printf("Ingrese la opcion que desee:\n");
	scanf(" %c",&opcion);
	while(opcion!='C' && opcion!='R' && opcion!='F'){
		printf("Ingresar una opcion valida:");
		scanf(" %c",&opcion);
	}
	return opcion;
}

void menu_derrota(bool* reintentar,personaje_t* personaje){
	
	bool verdadero=true;
	char opcion='A',c;
	if (*reintentar==false) printf("Que lastima perdiste :c\n");
	else printf("Has perdido nuevamente! :c\n");
	*reintentar=false;
	while(opcion!='F'){
		opcion=opcion_derrota(opcion);
		switch(opcion){

			case 'C':
				cambiar_pokemones(personaje);
				system("clear");
				break;
			case 'R':
				*reintentar=true;
				system("clear");
				break;
		}
		if(opcion=='R') opcion='F';
	}
}

/*---------------FUNCIONES DE SIMULACION-------------*/


void sumar_estadisticas(pokemon_t* pokemon){
	
	if(pokemon->cantidad_bonificador==63) return;
	pokemon->cantidad_bonificador=pokemon->cantidad_bonificador+1;
	pokemon->velocidad=pokemon->velocidad+1;
	pokemon->ataque=pokemon->ataque+1;
	pokemon->defensa=pokemon->defensa+1;
}

int while_batalla_simulacion(lista_iterador_t* iterador,lista_iterador_t* iterador2,pokemon_t* pokemon1,pokemon_t* pokemon2,int funcion_batalla(void*,void*),int verificar){

	bool e=true;
	int contador=0;
	char c;
	while(contador<5 && lista_iterador_tiene_siguiente(iterador)){
		if(verificar==GANO_PRIMERO && contador<5){
			sumar_estadisticas(pokemon1);
			contador++;
			lista_iterador_avanzar(iterador2);
		} 
		else if(verificar==GANO_SEGUNDO && lista_iterador_tiene_siguiente(iterador)){
			sumar_estadisticas(pokemon2);
			e=lista_iterador_avanzar(iterador);
		}
		if(e==true){
			pokemon1=lista_iterador_elemento_actual(iterador),
			pokemon2=lista_iterador_elemento_actual(iterador2);
			verificar=funcion_batalla(pokemon1,pokemon2);
		}
		//cuando la condicion de alguno de los dos ya no se cumpla salir del while y devolver el resultado
	}
	return verificar;
}

int batalla_simulacion(personaje_t* personaje, entrenador_t* entrenador,int funcion_batalla(void*,void*)){

	lista_iterador_t* iterador=lista_iterador_crear(personaje->pokemones_para_combatir);
	if(!iterador) return ERROR;
	lista_iterador_t* iterador2=lista_iterador_crear(entrenador->pokemones);
	if(!iterador2) return ERROR;
	pokemon_t* pokemon1=lista_iterador_elemento_actual(iterador),*pokemon2=lista_iterador_elemento_actual(iterador2);
	int verificar=funcion_batalla(pokemon1,pokemon2);	
	verificar=while_batalla_simulacion(iterador,iterador2,pokemon1,pokemon2,funcion_batalla,verificar);
	lista_iterador_destruir(iterador);
	lista_iterador_destruir(iterador2);
	return verificar;

}

bool switch_simulacion(gimnasio_t* gimnasio,personaje_t* personaje, entrenador_t* entrenador){

	int verificar=0;
	bool perdio=false;
	switch(gimnasio->id_puntero_funcion){
		case 1:
			verificar=batalla_simulacion(personaje,entrenador,funcion_batalla_1);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 2:

			verificar=batalla_simulacion(personaje,entrenador,funcion_batalla_2);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 3:

			verificar=batalla_simulacion(personaje,entrenador,funcion_batalla_3);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 4:

			verificar=batalla_simulacion(personaje,entrenador,funcion_batalla_4);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 5:
			
			verificar=batalla_simulacion(personaje,entrenador,funcion_batalla_5);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;
	}
	if (perdio==true) return true;
	return false;
}

int simulacion(heap_t* heap,gimnasio_t* gimnasio,entrenador_t* entrenador, personaje_t* personaje, int nro_entrenador,bool* reintentar,bool* terminar,int* tope){

	char c;
	bool lider=false,perdio=false;
	if(nro_entrenador==0) lider=true;
	pokemon_t* pokemon1,pokemon2;
	entrenador_t* entrenador_aux;
	perdio=switch_simulacion(gimnasio,personaje,entrenador);
	if(perdio==false && lider==true) {
		system("clear");
		if(menu_victoria(heap,entrenador,personaje,reintentar,terminar,tope)==ERROR) return ERROR;
		return OK;
	}
	if(perdio) {
		system("clear");
		menu_derrota(reintentar,personaje);
		if (*reintentar==true) simulacion(heap,gimnasio,entrenador,personaje,nro_entrenador,reintentar,terminar,tope);
		else *terminar=true;
		return OK;
	}
	else{
		if(nro_entrenador!=0) nro_entrenador--;
		entrenador_aux=lista_elemento_en_posicion(gimnasio->entrenador,nro_entrenador);
		simulacion(heap,gimnasio,entrenador_aux,personaje,nro_entrenador,reintentar,terminar,tope);
	}
	return OK;
}

/*----------------------FUNCIONES DE BATALLA----------------------*/


void informar_pokemones(pokemon_t* pokemon,pokemon_t* pokemon2){

	printf("POKEMON DEL RIVAL:\n\n");
	printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon->nombre,pokemon->velocidad,pokemon->defensa,pokemon->ataque);
	printf("\nPOKEMON DEL PERSONAJE:\n\n");
	printf("nombre pokemon:%s\nvelocidad:%d\ndefensa:%d\nataque:%d\n",pokemon2->nombre,pokemon2->velocidad,pokemon2->defensa,pokemon2->ataque);

}
void gano_pokemon(){

	char c;
	printf("\nGano mi pokemon :D\nPresione cualquier letra para avanzar");
	scanf(" %c",&c);
	system("clear");
}

void perdio_pokemon(){

	char c;
	printf("\nPerdio mi pokemon :c\nPresione cualquier letra para avanzar");
	scanf(" %c",&c);
	system("clear");
}

int while_batalla(lista_iterador_t* iterador,lista_iterador_t* iterador2,pokemon_t* pokemon1,pokemon_t* pokemon2,int funcion_batalla(void*,void*),int verificar){

	bool e=true;
	char c;
	int contador=0;
	while(contador<5 && lista_iterador_tiene_siguiente(iterador)){
		if(verificar==GANO_PRIMERO && contador<5){
			gano_pokemon();
			sumar_estadisticas(pokemon1);
			contador++;
			lista_iterador_avanzar(iterador2);
		} 
		else if(verificar==GANO_SEGUNDO && lista_iterador_tiene_siguiente(iterador)){
			perdio_pokemon();
			sumar_estadisticas(pokemon2);
			e=lista_iterador_avanzar(iterador);
		} 
		if(e==true){
			pokemon1=lista_iterador_elemento_actual(iterador),
			pokemon2=lista_iterador_elemento_actual(iterador2);
			informar_pokemones(pokemon1,pokemon2);
			verificar=funcion_batalla(pokemon1,pokemon2);
		}
	}
	return verificar;
}

int batalla(personaje_t* personaje, entrenador_t* entrenador,int funcion_batalla(void*,void*)){

	char c;
	lista_iterador_t* iterador=lista_iterador_crear(personaje->pokemones_para_combatir);
	if(!iterador) return ERROR;
	lista_iterador_t* iterador2=lista_iterador_crear(entrenador->pokemones);
	if(!iterador2) {
		lista_iterador_destruir(iterador);
		return ERROR;	
	}
	pokemon_t* pokemon1=lista_iterador_elemento_actual(iterador),*pokemon2=lista_iterador_elemento_actual(iterador2);
	informar_pokemones(pokemon1,pokemon2);
	int verificar=funcion_batalla(pokemon1,pokemon2);	
	verificar=while_batalla(iterador,iterador2,pokemon1,pokemon2,funcion_batalla,verificar);
	
	if(verificar==GANO_PRIMERO) gano_pokemon();
	else if(verificar==GANO_SEGUNDO) perdio_pokemon();

	lista_iterador_destruir(iterador);
	lista_iterador_destruir(iterador2);
	return verificar;

}

bool switch_batalla(gimnasio_t* gimnasio,personaje_t* personaje, entrenador_t* entrenador){

	int verificar=0;
	bool perdio=false;
	switch(gimnasio->id_puntero_funcion){
		case 1:
			verificar=batalla(personaje,entrenador,funcion_batalla_1);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 2:

			verificar=batalla(personaje,entrenador,funcion_batalla_2);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 3:

			verificar=batalla(personaje,entrenador,funcion_batalla_3);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 4:

			verificar=batalla(personaje,entrenador,funcion_batalla_4);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;

		case 5:
			
			verificar=batalla(personaje,entrenador,funcion_batalla_5);
			if(verificar==GANO_SEGUNDO) perdio=true;
			break;
	}
	if (perdio==true) return true;
	return false;
}

int menu_batalla(heap_t* heap,gimnasio_t* gimnasio,entrenador_t* entrenador, personaje_t* personaje, int nro_entrenador,bool* reintentar,bool* terminar,int* tope){

	char c;
	bool lider=false,perdio=false;
	if(nro_entrenador==0) lider=true;
	int verificar=0;
	entrenador_t* entrenador_aux;
	perdio=switch_batalla(gimnasio,personaje,entrenador);
	if(perdio==false && lider==true) {
		system("clear");
		if(menu_victoria(heap,entrenador,personaje,reintentar,terminar,tope)==ERROR) return ERROR;
		return OK;
	}
	if(perdio) {
		system("clear");
		menu_derrota(reintentar,personaje);
		if (*reintentar==true) menu_batalla(heap,gimnasio,entrenador,personaje,nro_entrenador,reintentar,terminar,tope);
		else *terminar=true;
		return OK;
	}
	else{
		printf("\nFelicidades ganaste la batalla. Apreta cualquier letra para avanzar al siguiente combate.");
		scanf(" %c",&c);
		system("clear");
		if(nro_entrenador!=0) nro_entrenador--;
		entrenador_aux=lista_elemento_en_posicion(gimnasio->entrenador,nro_entrenador);
		menu_batalla(heap,gimnasio,entrenador_aux,personaje,nro_entrenador,reintentar,terminar,tope);
	}
}


/*-------------MENU DE GIMNASIO------------*/

char validar_opcion_gimnasio(char opcion){

	char c;
	while(opcion!='E' && opcion!='G' && opcion!='C' && opcion!='B' && opcion!='Z'){
		system("clear");
		printf("MENU DE GIMNASIO:\n\n");
		printf("E:Mostrar al personaje principal con sus pokemones.\nG:Mostrar la informacion del gimnasio actual.\nC:Cambiar los pokemones de batalla.\nB:Jugar la siguiente batalla.\nZ:Salir\n\n");
		printf("Ingresar una opcion valida:");
		scanf(" %c",&opcion);
		fflush(stdin);
		system("clear");
	}
	return opcion;
}

char mostrar_instrucciones_gimnasio_e_ingresar(char opcion){

	printf("MENU DE GIMNASIO:\n\n");
	printf("E:Mostrar al personaje principal con sus pokemones.\nG:Mostrar la informacion del gimnasio actual.\nC:Cambiar los pokemones de batalla.\nB:Jugar la siguiente batalla.\nZ:Salir\n\n");
	printf("Ingrese la letra de la opcion que desee:\n\n");
	scanf(" %c",&opcion);
	fflush(stdin);
	system("clear");
	opcion=validar_opcion_gimnasio(opcion);
	return opcion;
}

void case_E_gym(personaje_t* personaje){

	char c;
	mostrar_personaje(personaje);
	printf("Presione cualquier letra para continuar:");
	scanf(" %c",&c);
	system("clear");
}

void case_G(gimnasio_t* gimnasio){

	char c;
	mostrar_gimnasio(gimnasio);
	printf("Presione cualquier letra para continuar:");
	scanf(" %c",&c);
	system("clear");
}

int case_B(heap_t* heap,personaje_t* personaje,gimnasio_t* gimnasio,bool* terminar){

	system("clear");
	bool reintentar=false;
	int tope=heap->tope;
	gimnasio=heap->vector[0];
	entrenador_t* entrenador;
	entrenador=lista_tope(gimnasio->entrenador);
	*terminar=false;
	if(menu_batalla(heap,gimnasio,entrenador,personaje,gimnasio->cantidad_entrenadores-1,&reintentar,terminar,&tope)==ERROR)return ERROR;
	if(*terminar==true) tope=0;
	if(tope>0) heap_extraer_raiz(heap);	//cambia de gimnasio y elimina el anterior
	system("clear");
	return OK;

}

int menu_gimnasio(heap_t* heap, personaje_t* personaje,bool*terminar){
	
	if(!heap || !personaje) return ERROR;
	gimnasio_t* gimnasio=heap->vector[0];
	int verificar=0;
	char opcion='E',c;
	while(opcion!='Z'){
		if(*terminar==false) opcion=mostrar_instrucciones_gimnasio_e_ingresar(opcion);
		switch(opcion){
			case 'E':
				case_E_gym(personaje);
				break;
			case 'G':
				case_G(gimnasio);
				break;
			case 'C':
				cambiar_pokemones(personaje);
				system("clear");
				break;

			case 'B':
				verificar=case_B(heap,personaje,gimnasio,terminar);
				if(verificar==ERROR) *terminar=true;
				int tope=heap->tope;
				if(tope!=0) gimnasio=heap->vector[0];
				break;
		}
		if(*terminar==true) opcion='Z';
	}
	if(verificar==ERROR) return ERROR;
	return OK;
}

/*------------- MENU DE INICIO ------------*/

char validar_opcion_inicio(char opcion){

	char c;
	while(opcion!='A' && opcion!='E' && opcion!='I' && opcion!='S' && opcion!='Z'){
		system("clear");
		printf("MENU DE INICIO:\n\n");
		printf("E:Ingresar el archivo del personaje principal.\nA:Ingresar el archivo de gimnasios.\nI:Comenzar la partida.\nS:Simular la partida.\nZ:Salir\n\n");
		printf("Ingresar una opcion valida:");
		scanf(" %c",&opcion);
		fflush(stdin);
	}
	return opcion;
}

bool validar_cargas(heap_t* heap,personaje_t* personaje){

	char c;
	if(!heap || !personaje){
		printf("No se puede jugar porque no se cargaron los archivos. Toque cualquier letra para continuar..");
		scanf(" %c",&c);
		system("clear");
		return false;
	}
	else return true;
}

personaje_t* case_E(personaje_t* personaje){

	if(personaje!=NULL) destruir_personaje(personaje);
	char ruta_archivo[50];
	printf("Ingrese la ruta del archivo o Z para cancelar:");
	scanf("%s",ruta_archivo);
	fflush(stdin);
	personaje=cargar_personaje(ruta_archivo);
	while(!personaje && *ruta_archivo!='Z'){
		printf("ERROR. Por favor ingrese una ruta valida o Z para cancelar:");
		scanf("%s",ruta_archivo);
		fflush(stdin);
		personaje=cargar_personaje(ruta_archivo);
	}
	system("clear");
	return personaje;
}

heap_t* case_A(heap_t* heap){

	if(heap!=NULL) heap_destruir(heap);
	char ruta_archivo[50];
	printf("Ingrese la ruta del archivo o Z para cancelar:");
	scanf("%s",ruta_archivo);
	heap=cargar_gimnasios(ruta_archivo);
	while(!heap && *ruta_archivo!='Z'){
		printf("ERROR. Por favor ingrese una ruta valida o Z para cancelar:");
		scanf("%s",ruta_archivo);
		fflush(stdin);
		heap=cargar_gimnasios(ruta_archivo);
	}
	system("clear");
	return heap;
}

int case_I(heap_t* heap, personaje_t* personaje,bool* terminar){

	*terminar=false;
	int verificar=menu_gimnasio(heap,personaje,terminar);
	system("clear");
	if(verificar==ERROR) return ERROR;
}

int case_S(heap_t* heap,personaje_t* personaje,bool* terminar, bool* siguiente){
	
	gimnasio_t* gimnasio=NULL;
	entrenador_t* entrenador=NULL;
	gimnasio=heap->vector[0];
	entrenador=lista_tope(gimnasio->entrenador);
	*siguiente=false;
	*terminar=false;
	int tope=heap->tope;
	int verificar=simulacion(heap,gimnasio,entrenador,personaje,gimnasio->cantidad_entrenadores-1,siguiente,terminar,&tope);
	if(verificar==ERROR) return ERROR;
	if(*terminar==true) tope=0;
	if(tope>0) heap_extraer_raiz(heap);
	if(tope!=0) gimnasio=heap->vector[0];
	system("clear");
	return OK;

}
char mostrar_instrucciones_inicio_e_ingresar(char opcion){

	printf("MENU DE INICIO:\n\n");
	printf("E:Ingresar el archivo del personaje principal.\nA:Ingresar el archivo de gimnasios.\nI:Comenzar la partida.\nS:Simular la partida.\nZ:Salir\n\n");
	printf("Ingrese la letra de la opcion que desee:\n\n");
	scanf(" %c",&opcion);
	fflush(stdin);
	opcion=validar_opcion_inicio(opcion);
	return opcion;
}

int menu_inicio(heap_t* heap,personaje_t* personaje){

	bool siguiente=false,terminar=false;
	int tope=0,verificar=0;
	char ruta_archivo[50],c,opcion='A';
	while(opcion!='Z'){
		if(siguiente==false) opcion=mostrar_instrucciones_inicio_e_ingresar(opcion);
		switch(opcion){
			case 'E':
				personaje=case_E(personaje);
				break;
			case 'A':
				heap=case_A(heap);
				break;
			case 'I':
				if(validar_cargas(heap,personaje)==true){
					system("clear");
					verificar=case_I(heap,personaje,&terminar);
					if(verificar==ERROR) opcion='Z';
				}
				break;
			case 'S':
				if(validar_cargas(heap,personaje)==true){
					system("clear");												
					verificar=case_S(heap,personaje,&terminar,&siguiente);
					if(verificar==ERROR) opcion='Z';
				}
				break;
		}

		if(terminar==true) opcion='Z';
		if(siguiente==true) opcion='S';
	}
	heap_destruir(heap);
	destruir_personaje(personaje);
	if(verificar==ERROR) return ERROR;
	return OK;
}

void main(){

	heap_t* heap=NULL;
	personaje_t* personaje=NULL;
	int verificar=menu_inicio(heap,personaje);
	if(verificar==ERROR) printf("ERROR\n");

}
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#define ERROR -1
#define OK 0

lista_t* lista_crear(){

	lista_t* lista;
	lista=malloc(sizeof(lista_t));
	if(!lista) return NULL;
	lista->nodo_inicio=NULL;
	lista->nodo_fin=NULL;
	lista->cantidad=0;
	return lista;

}

int lista_insertar(lista_t* lista,void* elemento){
	if(!lista) return ERROR;
	nodo_t* nodo_nuevo=malloc(sizeof(nodo_t));
	if(!nodo_nuevo) return -1;
	nodo_nuevo->elemento=elemento;
	if(lista->cantidad==0){

		lista->nodo_inicio=nodo_nuevo;				//le asigno a nodo inicio la direcc. de memoria del nodo nuevo.
		lista->nodo_inicio->siguiente=NULL;
		lista->nodo_fin=nodo_nuevo;					//le asigno a nodo fin la direcc. de memoria del nodo nuevo.
		lista->nodo_fin->siguiente=NULL;
		lista->cantidad++;
		return OK;
	}
	else {
		if(lista->cantidad==1){
			lista->nodo_inicio->siguiente=nodo_nuevo;		//le asigno al siguiente de nodo inicio la direcc. de memoria del nodo nuevo.
			lista->nodo_fin=nodo_nuevo;						//le asigno a nodo fin la direcc. de memoria del nodo nuevo.
			lista->nodo_fin->siguiente=NULL;
			lista->cantidad++;
			return OK;
		}
	}
	lista->nodo_fin->siguiente=nodo_nuevo;				//le asigno al siguiente del final actual el nodo nuevo
	lista->nodo_fin=nodo_nuevo;							//el nodo final ahora apunta al nodo nuevo
	lista->nodo_fin->siguiente=NULL;					//y el nodo final apunta a NULL
	lista->cantidad++;
	return OK;
}
/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(!lista || lista->cantidad==0) return 0;
	nodo_t* nodo_aux=lista->nodo_inicio;
	size_t contador=1;
	while(nodo_aux->siguiente!=NULL){
		contador++;
		nodo_aux=nodo_aux->siguiente;
	}
	return contador;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!lista) return ERROR;
	size_t i=0;
	nodo_t* nodo_nuevo=malloc(sizeof(nodo_t)),*nodo_aux=NULL,*nodo_aux_anterior=NULL;		//creo el nodo nuevo que quiero insertar y un nodo auxiliar para recorrer la lista
	if(!nodo_nuevo) return ERROR;
	nodo_aux=lista->nodo_inicio;								//igualo el nodo aux al inicio de la lista para recorrerla hasta la posicion pedida
	nodo_nuevo->elemento=elemento;
	if(posicion==0){
		nodo_nuevo->siguiente=lista->nodo_inicio;
		lista->nodo_inicio=nodo_nuevo;
		lista->cantidad++;
		return OK;
	}
	else{
		if(posicion>=lista->cantidad){								//si el nodo nuevo en la posicion pedida es mayor a la lista cantidad o es igual al final,
			free(nodo_nuevo);										//libero el nodo nuevo		
			if(lista_insertar(lista,elemento)==OK) return OK;		// y que inserte el elemento en la posicion final
		}								
	}
	while(i<posicion && nodo_aux->siguiente!=NULL){
		nodo_aux_anterior=nodo_aux;
		nodo_aux=nodo_aux->siguiente;
		i++;
	}
	nodo_nuevo->siguiente=nodo_aux;								//sino que lo inserte en la posicion pedida.
	nodo_aux_anterior->siguiente=nodo_nuevo;
	lista->cantidad++;
	return OK;
}

int lista_borrar(lista_t* lista){ 
	if(!lista || lista->cantidad==0) return ERROR;
	nodo_t* nodo_actual=lista->nodo_inicio,*nodo_anterior=NULL;
	if(lista->cantidad==1){
		free(nodo_actual);
		lista->cantidad--;
		return OK;
	}
	while(nodo_actual->siguiente!=NULL){
		nodo_anterior=nodo_actual;
		nodo_actual=nodo_actual->siguiente;
	}
	free(nodo_actual);
	nodo_anterior->siguiente=NULL;
	lista->cantidad--;
	lista->nodo_fin=nodo_anterior;
	return OK;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

	if(!lista || lista->cantidad==0) return ERROR;
	nodo_t* nodo_aux=lista->nodo_inicio, *nodo_anterior=NULL;
	size_t i=0;
	if(posicion>=lista->cantidad){						//si la posicion es mayor o igual a la cantidad que borre el ultimo.
		if(lista_borrar(lista)==OK) return OK;
	}
	else{
		if(posicion==0){
			nodo_aux=lista->nodo_inicio->siguiente;		//guardo la dir de memoria del siguiente del nodo_inicio
			free(lista->nodo_inicio);					//elimino el nodo inicio
			lista->nodo_inicio=nodo_aux;				//reasigno como nodo_inicio el nodo previamente guardado.
			lista->cantidad--;
			return OK;
		}
		else{
			while(i<posicion && nodo_aux->siguiente!=NULL){		//recorro la lista para obtener el nodo que quiero eliminar
				nodo_anterior=nodo_aux;
				nodo_aux=nodo_aux->siguiente;
				i++;
			}
			nodo_anterior->siguiente=nodo_aux->siguiente;		//que el nodo anterior->siguiente apunte al siguiente del nodo que quiero eliminar.
			free(nodo_aux);										//elimino el nodo que quiero eliminar.
			lista->cantidad--;
			return OK;
		}
	}
	return ERROR;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(!lista || posicion>lista->cantidad) return NULL;		//Devuelve NULL si la lista se encuentra vacia o si la posicion no existe
	nodo_t* nodo_devolver=lista->nodo_inicio;
	size_t i=0;
	if(posicion==lista->cantidad) return lista->nodo_fin->elemento;					//Si la posicion es la final devuelve el ultimo nodo.
	while(i<posicion && nodo_devolver->siguiente!=NULL){				
		nodo_devolver=nodo_devolver->siguiente;
		i++;
	}
	return nodo_devolver->elemento;													//Devuelvo el nodo pedido.
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	if(!lista || lista->cantidad==0) return NULL;
	return lista->nodo_fin->elemento;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	if(!lista ||lista->cantidad==0) return true;
	return false;
}
/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int lista_apilar(lista_t* lista, void* elemento){
	if(!lista) return ERROR;
	else{
		if(lista_insertar(lista,elemento)!=OK) return ERROR;
	}
	return OK;
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int lista_desapilar(lista_t* lista){
	if(!lista || lista->cantidad==0) return ERROR;
	else{
		if(lista_borrar(lista)!=OK) return ERROR;
	}
	return OK;
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* lista_tope(lista_t* lista){
	if(!lista || lista->cantidad==0) return NULL;
	return lista->nodo_fin->elemento;
}
/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t* lista, void* elemento){
	if(!lista) return ERROR;
	lista_insertar(lista,elemento);
	return OK;
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t* lista){
	if(!lista || lista->cantidad==0) return ERROR;
	lista_borrar_de_posicion(lista,0);
	return OK;
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* lista_primero(lista_t* lista){
	if(!lista || lista->cantidad==0) return NULL;
	return lista->nodo_inicio->elemento;
}

/*
 * Libera la memoria reservada por la lista.
 */
void destruir_nodo(nodo_t* nodo){
	if(nodo!=NULL) destruir_nodo(nodo->siguiente);
	free(nodo);
}

void lista_destruir(lista_t* lista){
	if(!lista || lista->cantidad==0) free(lista);
	else{ 
		destruir_nodo(lista->nodo_inicio);
		free(lista);
	}
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(!lista) return NULL;
	lista_iterador_t* iterador=malloc(sizeof(lista_iterador_t));
	if(!iterador) return NULL;
	iterador->corriente=lista->nodo_inicio;
	iterador->lista=lista;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	return iterador->corriente!=NULL;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(iterador->corriente){ 
		iterador->corriente=iterador->corriente->siguiente;
		if(!iterador->corriente) return false;
		return true;
	}
	return false;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente || !iterador->corriente->elemento) return NULL;
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
	if(!lista || lista->cantidad==0 || !(funcion)) return 0;
	size_t cantidad_elementos=1;
	nodo_t* nodo_aux=lista->nodo_inicio;
	while((funcion)(nodo_aux->elemento,contexto) && nodo_aux->siguiente!=NULL){				
		nodo_aux=nodo_aux->siguiente;
		cantidad_elementos++;
	}
	return cantidad_elementos;
}



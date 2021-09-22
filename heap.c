#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define OK 0
#define ERROR -1

#include "heap.h"

heap_t* heap_crear(heap_comparador comparador,heap_liberar_elemento destructor){
	heap_t* heap=calloc(1,sizeof(heap_t));
	heap->comparador=comparador;
	heap->destructor=destructor;
	return heap;
}

int posicion_padre(int n){
	return (n-1)/2;
}

int posicion_hijo_derecho(int n){
	return 2*n+2;
}

int posicion_hijo_izquierdo(int n){
	return 2*n+1;
}
void swap(void** vector, int i, int j){
	void* aux=vector[i];
	vector[i]=vector[j];
	vector[j]=aux;
}
	
void sift_up(heap_t* heap,int n){

	if(n==0) return;

	int padre=posicion_padre(n);

	if(heap->comparador(heap->vector[n],heap->vector[padre])==-1){
		swap(heap->vector,n,padre);
		sift_up(heap,padre);
	}
}

int heap_insertar(heap_t* heap,void* elemento){
	if(!heap && !heap->vector && !elemento) return ERROR;
	void** aux= realloc(heap->vector, sizeof(elemento)*(heap->tope+1));
	if(!aux) return ERROR;
	heap->tope++;
	heap->vector=aux;

	heap->vector[heap->tope-1]=elemento;

	sift_up(heap,heap->tope-1);

	return OK;
}


void sift_down(heap_t* heap, int n){

	int pos_der = posicion_hijo_derecho(n);
	int pos_izq = posicion_hijo_izquierdo(n);
	int pos_menor = pos_izq;

	if(pos_izq >= heap->tope) return;

	if(pos_der < heap->tope){
		if(heap->comparador(heap->vector[pos_der],heap->vector[pos_izq])==-1)
			pos_menor = pos_der;
	}

	if(heap->comparador(heap->vector[n],heap->vector[pos_menor])==1){
		swap(heap->vector,n,pos_menor);
		sift_down(heap,pos_menor);
	}
}

int heap_extraer_raiz(heap_t* heap){

	if(heap->tope==0) return ERROR;

	void* elemento=heap->vector[0];
	heap->destructor(elemento);

	heap->vector[0] = heap->vector[heap->tope-1];
	heap->tope--;

	if(heap->tope !=0) sift_down(heap,0);

	return OK;
}

void heap_destruir(heap_t* heap){

	if(!heap) return;
	if(heap->tope==0) return free(heap);
	if(heap && heap->vector && heap->destructor){
		for(int i=heap->tope-1;i>=0;i--){
			heap->destructor(heap->vector[i]);
		}
		free(heap->vector);
	}
	free(heap);
}























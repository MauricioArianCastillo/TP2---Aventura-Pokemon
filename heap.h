#ifndef __HEAP_H__
#define __HEAP_H__

#include<stdio.h>


#define OK 0
#define ERROR -1

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * (heap_extraer_raiz) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct{
	void** vector;
	int tope;
	heap_comparador comparador;
	heap_liberar_elemento destructor;

}heap_t;


heap_t* heap_crear();

int posicion_padre(int n);

int posicion_hijo_derecho(int n);

int posicion_hijo_izquierdo(int n);

void swap(void** vector, int i, int j);

void sift_up(heap_t* heap,int i);

int heap_insertar(heap_t* heap,void* elemento);

void* heap_devolver_raiz(heap_t* heap);

int heap_extraer_raiz(heap_t* heap);

void sift_down(heap_t* heap, int n);

void heap_destruir(heap_t* heap);

#endif /*__HEAP_H__*/
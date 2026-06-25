#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo
struct Nodo {
	int dato;
	struct Nodo *izq;
	struct Nodo *der;
};

// Crear un nuevo nodo
struct Nodo* crearNodo(int valor) {
	struct Nodo* nuevo = (struct Nodo*) malloc(sizeof(struct Nodo));
	
	nuevo->dato = valor;
	nuevo->izq = NULL;
	nuevo->der = NULL;
	
	return nuevo;
}

// Inserci�n recursiva en �rbol binario de b�squeda
struct Nodo* insertar(struct Nodo* raiz, int valor) {
	
	// Caso base
	if (raiz == NULL)
		return crearNodo(valor);
	
	// Caso recursivo
	if (valor < raiz->dato)
		raiz->izq = insertar(raiz->izq, valor);
	else
		raiz->der = insertar(raiz->der, valor);
	
	return raiz;
}

// Recorrido InOrden
void inorden(struct Nodo* raiz) {
	
	if (raiz != NULL) {
		
		inorden(raiz->izq);
		
		printf("%d ", raiz->dato);
		
		inorden(raiz->der);
	}
}

// Mostrar �rbol de costado
void mostrarArbol(struct Nodo* raiz, int nivel) {
	
	if (raiz == NULL)
		return;
	
	mostrarArbol(raiz->der, nivel + 1);
	
	for(int i = 0; i < nivel; i++)
		printf("     ");
	
	printf("%d\n", raiz->dato);
	
	mostrarArbol(raiz->izq, nivel + 1);
}

int main() {
	
	struct Nodo* raiz = NULL;
	
	int valor;
	int cantidad;
	
	printf("Cantidad de nodos: ");
	scanf("%d", &cantidad);
	
	for(int i = 0; i < cantidad; i++) {
		
		printf("Ingrese un valor: ");
		scanf("%d", &valor);
		
		raiz = insertar(raiz, valor);
	}
	
	printf("\n\nARBOL BINARIO\n\n");
	mostrarArbol(raiz, 0);
	
	printf("\nRecorrido InOrden: ");
	inorden(raiz);
	
	printf("\n");
	
	return 0;
}
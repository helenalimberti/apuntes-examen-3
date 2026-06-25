#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un nodo
struct Nodo {
	int dato;
	struct Nodo* siguiente;
};


// Funci�n para crear un nuevo nodo
struct Nodo* crearNodo(int valor) ;

// Funci�n para agregar un nodo al final
void agregarAlFinal(struct Nodo** cabeza, int valor);

// Funci�n para imprimir la lista
void imprimirLista(struct Nodo* cabeza);
// Liberar memoria
void liberarLista(struct Nodo* cabeza) ;

int main() {
	struct Nodo* lista = NULL;
	int opcion, valor;
	
	do {
		printf("\n--- MENU ---\n");
		printf("1. Agregar nodo\n");
		printf("2. Mostrar lista\n");
		printf("3. Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
		case 1:
			printf("Ingrese un valor entero: ");
			scanf("%d", &valor);
			agregarAlFinal(&lista, valor);
			break;
		case 2:
			imprimirLista(lista);
			break;
		case 3:
			liberarLista(lista);
			printf("Memoria liberada. Adios.\n");
			break;
		default:
			printf("Opcion invalida.\n");
		}
	} while (opcion != 3);
	
	return 0;
}


// Funci�n para crear un nuevo nodo
struct Nodo* crearNodo(int valor) {
	struct Nodo* nuevo = (struct Nodo*) malloc(sizeof(struct Nodo));
	if (nuevo == NULL) {
		printf("Error: no se pudo asignar memoria.\n");
		exit(1);
	}
	nuevo->dato = valor;
	nuevo->siguiente = NULL;
	return nuevo;
}

// Funci�n para agregar un nodo al final
void agregarAlFinal(struct Nodo** cabeza, int valor) {
	struct Nodo* nuevo = crearNodo(valor);
	
	if (*cabeza == NULL) {
		*cabeza = nuevo;
	} else {
		struct Nodo* actual = *cabeza;
		while (actual->siguiente != NULL) {
			actual = actual->siguiente;
		}
		actual->siguiente = nuevo;
	}
}

// Funci�n para imprimir la lista
void imprimirLista(struct Nodo* cabeza) {
	printf("Lista: ");
	while (cabeza != NULL) {
		printf("%d -> ", cabeza->dato);
		cabeza = cabeza->siguiente;
	}
	printf("NULL\n");
}

// Liberar memoria
void liberarLista(struct Nodo* cabeza) {
	struct Nodo* temp;
	while (cabeza != NULL) {
		temp = cabeza;
		cabeza = cabeza->siguiente;
		free(temp);
	}
}
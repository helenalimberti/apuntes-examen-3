#include <stdio.h>
#include <stdlib.h>
#define cant 5

struct Nodo {
    int dato;
    struct Nodo* siguiente;
};

int main() {
    int j = 0, valor;
    struct Nodo* nuevo  = NULL;
    struct Nodo* cabeza = NULL;
    struct Nodo* ultimo = NULL;  // guarda el ultimo nodo agregado

    while (j < cant) {
        nuevo = (struct Nodo*) malloc(sizeof(struct Nodo));
        if (nuevo == NULL) {
            printf("Error al asignar memoria.\n");
            break;
        }

        printf("Ingrese un valor: ");
        scanf("%d", &valor);
        nuevo->dato = valor;
        nuevo->siguiente = NULL;

        if (cabeza == NULL) {
            // Es el primer nodo: se convierte en la cabeza
            cabeza = nuevo;
        } else {
            // No es el primero: se engancha al ultimo nodo
            ultimo->siguiente = nuevo;
        }

        ultimo = nuevo;  // el nuevo nodo pasa a ser el ultimo
        j++;
    }

    // Mostrar la lista
    printf("\nLista cargada:\n");
    struct Nodo* recorredor = cabeza;
    while (recorredor != NULL) {
        printf("[%d]", recorredor->dato);
        if (recorredor->siguiente != NULL) printf(" -> ");
        recorredor = recorredor->siguiente;
    }
    printf(" -> NULL\n");

    // Liberar memoria
    while (cabeza != NULL) {
        struct Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }

    return 0;
}
			
		
		
		
		
		
		
		
		
		
	
	
	
	
		

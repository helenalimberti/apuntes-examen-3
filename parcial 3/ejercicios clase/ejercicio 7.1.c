#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo
struct Nodo {
    char letra;
    struct Nodo* siguiente;
};

// Crea un nuevo nodo con la letra dada
struct Nodo* crearNodo(char letra) {
    struct Nodo* nodoNuevo = (struct Nodo*) malloc(sizeof(struct Nodo));
    if (nodoNuevo == NULL) { printf("Error de memoria.\n"); exit(1); }
    nodoNuevo->letra = letra;
    nodoNuevo->siguiente = NULL;
    return nodoNuevo;
}

// Agrega una letra al final de la lista
// "primerNodo" es un doble puntero porque necesitamos modificar
// la variable "lista" que esta en el main
void agregarAlFinal(struct Nodo** primerNodo, char letra) {
    struct Nodo* nodoNuevo = crearNodo(letra);

    // Si la lista esta vacia, el nuevo nodo es el primero
    if (*primerNodo == NULL) {
        *primerNodo = nodoNuevo;
        return;
    }

    // Si ya hay nodos, recorremos hasta el ultimo y enganchamos ahi
    struct Nodo* nodoActual = *primerNodo;
    while (nodoActual->siguiente != NULL)
        nodoActual = nodoActual->siguiente;
    nodoActual->siguiente = nodoNuevo;
}

// Imprime todos los nodos de la lista
void imprimirLista(struct Nodo* primerNodo) {
    while (primerNodo != NULL) {
        printf("[%c]", primerNodo->letra);
        if (primerNodo->siguiente != NULL) printf(" -> ");
        primerNodo = primerNodo->siguiente;
    }
    printf(" -> NULL\n");
}

// Elimina los nodos en posiciones multiplo de 3 (3, 6, 9, ...)
void eliminarMultiplosDe3(struct Nodo** primerNodo) {
    struct Nodo* nodoActual  = *primerNodo; // el nodo que estamos mirando ahora
    struct Nodo* nodoAnterior = NULL;        // el nodo que esta justo antes
    int posicion = 1;

    while (nodoActual != NULL) {
        if (posicion % 3 == 0) {
            // Guardamos el nodo a borrar para liberar su memoria despues
            struct Nodo* nodoABorrar = nodoActual;

            if (nodoAnterior == NULL) {
                // El nodo a borrar es el primero de la lista
                *primerNodo = nodoActual->siguiente;
            } else {
                // El nodo anterior "saltea" al nodo actual
                // y apunta directo al que sigue
                nodoAnterior->siguiente = nodoActual->siguiente;
            }

            nodoActual = nodoActual->siguiente; // avanzamos antes de borrar
            free(nodoABorrar);                  // liberamos la memoria
        } else {
            // Este nodo se queda, simplemente avanzamos
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
        }
        posicion++;
    }
}

// Libera toda la memoria de la lista
void liberarLista(struct Nodo* primerNodo) {
    struct Nodo* nodoABorrar;
    while (primerNodo != NULL) {
        nodoABorrar = primerNodo;               // guardamos el nodo actual
        primerNodo = primerNodo->siguiente;     // avanzamos al siguiente
        free(nodoABorrar);                      // borramos el guardado
    }
}

int main() {
    struct Nodo* lista = NULL;

    // Cargar el abecedario en la lista
    for (char c = 'A'; c <= 'Z'; c++)
        agregarAlFinal(&lista, c);

    printf("Lista original:\n");
    imprimirLista(lista);

    // Eliminar letras en posiciones multiplo de 3 (C, F, I, L, O, R, U, X)
    eliminarMultiplosDe3(&lista);

    printf("\nLista sin posiciones multiplo de 3:\n");
    imprimirLista(lista);

    liberarLista(lista);
    return 0;
}
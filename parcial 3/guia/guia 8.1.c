#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo
typedef struct Nodo {
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

// Crear nodo
Nodo* crearNodo(int dato) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));

    if (nuevo == NULL) {
        printf("Error de memoria.\n");
        exit(1);
    }

    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

// Recorrido Preorden (Raíz-Izq-Der)
void preorden(Nodo *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preorden(raiz->izq);
        preorden(raiz->der);
    }
}

// Recorrido Inorden (Izq-Raíz-Der)
void inorden(Nodo *raiz) {
    if (raiz != NULL) {
        inorden(raiz->izq);
        printf("%d ", raiz->dato);
        inorden(raiz->der);
    }
}

// Recorrido Postorden (Izq-Der-Raíz)
void postorden(Nodo *raiz) {
    if (raiz != NULL) {
        postorden(raiz->izq);
        postorden(raiz->der);
        printf("%d ", raiz->dato);
    }
}

int main() {

    // Construcción manual del árbol

    Nodo *raiz = crearNodo(2);

    raiz->izq = crearNodo(7);
    raiz->der = crearNodo(5);

    raiz->izq->izq = crearNodo(2);
    raiz->izq->der = crearNodo(6);

    raiz->izq->der->izq = crearNodo(5);
    raiz->izq->der->der = crearNodo(11);

    raiz->der->der = crearNodo(9);
    raiz->der->der->izq = crearNodo(4);

    printf("Recorrido Preorden: ");
    preorden(raiz);

    printf("\nRecorrido Inorden: ");
    inorden(raiz);

    printf("\nRecorrido Postorden: ");
    postorden(raiz);

    printf("\n");

    return 0;
}
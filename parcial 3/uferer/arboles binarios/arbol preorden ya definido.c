#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

Nodo* crearNodo(int valor) {
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

Nodo* insertar(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        return crearNodo(valor);
    }
    if (valor < raiz->dato) {
        raiz->izq = insertar(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        raiz->der = insertar(raiz->der, valor);
    }
    return raiz;
}

void preOrden(Nodo *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preOrden(raiz->izq);
        preOrden(raiz->der);
    }
}

void inOrden(Nodo *raiz) {
    if (raiz != NULL) {
        inOrden(raiz->izq);
        printf("%d ", raiz->dato);
        inOrden(raiz->der);
    }
}

void postOrden(Nodo *raiz) {
    if (raiz != NULL) {
        postOrden(raiz->izq);
        postOrden(raiz->der);
        printf("%d ", raiz->dato);
    }
}

void liberarArbol(Nodo *raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izq);
        liberarArbol(raiz->der);
        free(raiz);
    }
}

int main() {
    Nodo *raiz = NULL;

    // Numeros predefinidos
    int numeros[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 90};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    for (int i = 0; i < n; i++) {
        raiz = insertar(raiz, numeros[i]);
    }

    printf("PreOrden:  ");
    preOrden(raiz);

    printf("\nInOrden:   ");
    inOrden(raiz);

    printf("\nPostOrden: ");
    postOrden(raiz);

    printf("\n");

    liberarArbol(raiz);
    return 0;
}
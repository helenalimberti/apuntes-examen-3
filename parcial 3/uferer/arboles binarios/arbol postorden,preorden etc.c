#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

// Crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// Insertar en el árbol (BST)
Nodo* insertar(Nodo *raiz, int valor) {
    if (raiz == NULL) {
        return crearNodo(valor);
    }
    if (valor < raiz->dato) {
        raiz->izq = insertar(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        raiz->der = insertar(raiz->der, valor);
    }
    // si es igual, no se inserta (no duplicados)
    return raiz;
}

// Recorrido PreOrden: Raiz -> Izq -> Der
void preOrden(Nodo *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preOrden(raiz->izq);
        preOrden(raiz->der);
    }
}

// Recorrido InOrden: Izq -> Raiz -> Der
void inOrden(Nodo *raiz) {
    if (raiz != NULL) {
        inOrden(raiz->izq);
        printf("%d ", raiz->dato);
        inOrden(raiz->der);
    }
}

// Recorrido PostOrden: Izq -> Der -> Raiz
void postOrden(Nodo *raiz) {
    if (raiz != NULL) {
        postOrden(raiz->izq);
        postOrden(raiz->der);
        printf("%d ", raiz->dato);
    }
}

// Liberar memoria
void liberarArbol(Nodo *raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izq);
        liberarArbol(raiz->der);
        free(raiz);
    }
}

int main() {
    Nodo *raiz = NULL;
    int n, valor;

    printf("¿Cuántos numeros desea ingresar? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Ingrese el numero %d: ", i + 1);
        scanf("%d", &valor);
        raiz = insertar(raiz, valor);
    }

    printf("\nPreOrden:  ");
    preOrden(raiz);

    printf("\nInOrden:   ");
    inOrden(raiz);

    printf("\nPostOrden: ");
    postOrden(raiz);

    printf("\n");

    liberarArbol(raiz);
    return 0;
}
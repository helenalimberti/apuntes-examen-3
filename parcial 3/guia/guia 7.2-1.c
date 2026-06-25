/*
 * Ejercicio 7.2.1 - Pilas
 * Panaderia: lista mezclada de facturas tipo A y B.
 * Se separan en dos pilas para que la ultima emitida
 * sea la primera en atenderse (LIFO).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50

/* ══════════════════════════════════════
   ESTRUCTURAS
   ══════════════════════════════════════ */

struct Factura {
    int  nro;
    char tipo;
    char cliente[MAX_NOMBRE];
};

struct NodoLista {
    struct Factura    datos;
    struct NodoLista *siguiente;
};

struct NodoPila {
    struct Factura   datos;
    struct NodoPila *siguiente;
};

/* ══════════════════════════════════════
   LISTA ORIGINAL (mezclada)
   ══════════════════════════════════════ */

struct NodoLista *agregarFactura(struct NodoLista *cabeza, struct Factura f) {
    struct NodoLista *nuevo = malloc(sizeof(struct NodoLista));
    nuevo->datos     = f;
    nuevo->siguiente = NULL;

    if (cabeza == NULL) return nuevo;

    struct NodoLista *actual = cabeza;
    while (actual->siguiente != NULL)
        actual = actual->siguiente;
    actual->siguiente = nuevo;
    return cabeza;
}

void mostrarLista(struct NodoLista *cabeza) {
    int pos = 1;
    while (cabeza != NULL) {
        printf("  %d. Factura #%04d | Tipo %c | %s\n",
               pos++, cabeza->datos.nro,
               cabeza->datos.tipo, cabeza->datos.cliente);
        cabeza = cabeza->siguiente;
    }
}

/* ══════════════════════════════════════
   PILA (LIFO)
   ══════════════════════════════════════ */

/* PUSH: apila encima del tope */
struct NodoPila *push(struct NodoPila *tope, struct Factura f) {
    struct NodoPila *nuevo = malloc(sizeof(struct NodoPila));
    nuevo->datos     = f;
    nuevo->siguiente = tope;
    return nuevo;
}

/* POP: desapila el tope */
struct NodoPila *pop(struct NodoPila *tope, struct Factura *f) {
    if (tope == NULL) return NULL;
    *f = tope->datos;
    struct NodoPila *siguiente = tope->siguiente;
    free(tope);
    return siguiente;
}

void mostrarPila(struct NodoPila *tope) {
    if (tope == NULL) {
        printf("  (vacia)\n");
        return;
    }
    printf("  TOPE (ultima emitida = primera a atender)\n");
    int orden = 1;
    while (tope != NULL) {
        printf("  %d. Factura #%04d | Tipo %c | %s\n",
               orden++, tope->datos.nro,
               tope->datos.tipo, tope->datos.cliente);
        tope = tope->siguiente;
    }
}

/* ══════════════════════════════════════
   SEPARAR LISTA EN DOS PILAS
   Al recorrer en orden e ir apilando,
   la ultima factura queda en el tope → LIFO
   ══════════════════════════════════════ */

void separarEnPilas(struct NodoLista *cabeza,
                    struct NodoPila **pilaA,
                    struct NodoPila **pilaB) {
    while (cabeza != NULL) {
        if (cabeza->datos.tipo == 'A')
            *pilaA = push(*pilaA, cabeza->datos);
        else
            *pilaB = push(*pilaB, cabeza->datos);
        cabeza = cabeza->siguiente;
    }
}

/* ══════════════════════════════════════
   ATENDER: desapilar mostrando el orden
   ══════════════════════════════════════ */

void atenderPila(struct NodoPila **tope, char tipo) {
    struct Factura f;
    int orden = 1;
    printf("  Orden de atencion:\n");
    while (*tope != NULL) {
        *tope = pop(*tope, &f);
        printf("  %d. Factura #%04d | Tipo %c | %s\n",
               orden++, f.nro, tipo, f.cliente);
    }
}

/* ══════════════════════════════════════
   MAIN
   ══════════════════════════════════════ */

int main(void) {

    struct NodoLista *lista = NULL;
    struct NodoPila  *pilaA = NULL;
    struct NodoPila  *pilaB = NULL;

    /* Facturas mezcladas ingresadas en orden de emision */
    struct Factura facturas[] = {
        {1001, 'A', "Maria Gonzalez"},
        {1002, 'B', "Carlos Lopez"},
        {1003, 'A', "Ana Perez"},
        {1004, 'B', "Luis Fernandez"},
        {1005, 'A', "Sofia Martinez"},
        {1006, 'B', "Jorge Diaz"},
        {1007, 'A', "Lucia Romero"},
        {1008, 'B', "Pablo Torres"}
    };

    int n = sizeof(facturas) / sizeof(facturas[0]);
    int i;
    for (i = 0; i < n; i++)
        lista = agregarFactura(lista, facturas[i]);

    /* 1. Lista original */
    printf("Lista original (mezclada):\n");
    mostrarLista(lista);

    /* 2. Separar en pilas */
    separarEnPilas(lista, &pilaA, &pilaB);

    printf("\nPila Tipo A:\n");
    mostrarPila(pilaA);

    printf("\nPila Tipo B:\n");
    mostrarPila(pilaB);

    /* 3. Atender */
    printf("\nAtendiendo Tipo A:\n");
    atenderPila(&pilaA, 'A');

    printf("\nAtendiendo Tipo B:\n");
    atenderPila(&pilaB, 'B');

    return 0;
}
/*
 * Ejercicio 7.2.2
 * Funcion Reemplazar: recibe una pila de enteros,
 * un valor "viejo" y un valor "nuevo".
 * Si "viejo" aparece en la pila, lo reemplaza por "nuevo".
 * La pila queda en el mismo orden al terminar.
 */

#include <stdio.h>
#include <stdlib.h>

/* ══════════════════════════════════════
   ESTRUCTURA
   ══════════════════════════════════════ */

struct Nodo {
    int           valor;
    struct Nodo  *siguiente;
};

/* ══════════════════════════════════════
   OPERACIONES DE PILA
   ══════════════════════════════════════ */

struct Nodo *push(struct Nodo *tope, int valor) {
    struct Nodo *nuevo = malloc(sizeof(struct Nodo));
    nuevo->valor     = valor;
    nuevo->siguiente = tope;
    return nuevo;
}

struct Nodo *pop(struct Nodo *tope, int *valor) {
    if (tope == NULL) return NULL;
    *valor = tope->valor;
    struct Nodo *sig = tope->siguiente;
    free(tope);
    return sig;
}

void mostrarPila(struct Nodo *tope) {
    printf("  TOPE -> ");
    while (tope != NULL) {
        printf("[%d]", tope->valor);
        if (tope->siguiente != NULL) printf(" -> ");
        tope = tope->siguiente;
    }
    printf("\n");
}

/* ══════════════════════════════════════
   REEMPLAZAR
   Estrategia:
     1. Desapilar todo en una pila auxiliar
        (esto invierte el orden).
     2. Volver a apilar en la pila original,
        reemplazando "viejo" por "nuevo"
        (esto restaura el orden original).
   ══════════════════════════════════════ */

struct Nodo *reemplazar(struct Nodo *tope, int viejo, int nuevo) {
    struct Nodo *auxiliar = NULL;
    int valor;

    /* Paso 1: pasar todo a la pila auxiliar */
    while (tope != NULL)
        tope = pop(tope, &valor),
        auxiliar = push(auxiliar, valor);

    /* Paso 2: volver a la pila original reemplazando */
    while (auxiliar != NULL) {
        auxiliar = pop(auxiliar, &valor);
        if (valor == viejo)
            valor = nuevo;
        tope = push(tope, valor);
    }

    return tope;
}

/* ══════════════════════════════════════
   MAIN
   ══════════════════════════════════════ */

int main(void) {

    struct Nodo *pila = NULL;

    /* Cargar pila: tope sera 3 */
    pila = push(pila, 10);
    pila = push(pila, 5);
    pila = push(pila, 8);
    pila = push(pila, 5);
    pila = push(pila, 3);

    printf("Pila original:\n");
    mostrarPila(pila);

    printf("Reemplazar 5 por 99:\n");
    pila = reemplazar(pila, 5, 99);

    printf("Pila resultante:\n");
    mostrarPila(pila);

    return 0;
}
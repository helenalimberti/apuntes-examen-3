/*
 * Ejercicio 7.2.3
 * Funcion que determina si una pila de enteros
 * esta ordenada de manera ascendente.
 *
 * Ascendente: yendo del tope al fondo,
 * cada elemento es MENOR al que le sigue.
 *
 *   Ordenada:    TOPE -> [1] -> [4] -> [7] -> [10]
 *   Desordenada: TOPE -> [1] -> [7] -> [3] -> [10]
 *
 * La pila debe quedar igual al terminar.
 *
 * Orden del algoritmo: O(n)
 * Justificacion: se recorren los n elementos una sola
 * vez para vaciar la pila en la auxiliar (comparando
 * de paso), y luego se recorren otra vez para restaurar.
 * Son dos pasadas lineales → O(n) + O(n) = O(n).
 * No hay bucles anidados.
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
   ESTA ORDENADA ASCENDENTE
   
   Estrategia:
     1. Desapilar en una pila auxiliar,
        comparando cada elemento con el anterior.
        Si en algun momento el elemento actual
        NO es mayor al anterior → desordenada.
     2. Restaurar la pila original desde la auxiliar.
   
   Recibe puntero doble (**tope) para poder
   modificar el puntero original desde el main.
   ══════════════════════════════════════ */

int estaOrdenada(struct Nodo **tope) {
    struct Nodo *auxiliar = NULL;
    int valor;
    int anterior;
    int ordenada = 1;   /* asumimos que si */
    int primero  = 1;   /* para saltar la primera comparacion */

    /* Paso 1: vaciar en auxiliar y comparar */
    while (*tope != NULL) {
        *tope = pop(*tope, &valor);
        auxiliar = push(auxiliar, valor);

        if (!primero && valor <= anterior)
            ordenada = 0;

        anterior = valor;
        primero  = 0;
    }

    /* Paso 2: restaurar la pila original */
    while (auxiliar != NULL) {
        auxiliar = pop(auxiliar, &valor);
        *tope = push(*tope, valor);
    }

    return ordenada;
}

/* ══════════════════════════════════════
   MAIN
   ══════════════════════════════════════ */

int main(void) {

    struct Nodo *pila = NULL;
    int v;

    /* ─── Caso 1: ordenada ascendente ─── */
    printf("Caso 1 (ordenada):\n");
    pila = push(pila, 10);
    pila = push(pila, 7);
    pila = push(pila, 4);
    pila = push(pila, 1);

    mostrarPila(pila);
    printf("  Resultado: %s\n", estaOrdenada(&pila) ? "SI, ordenada" : "NO, desordenada");
    printf("  Pila luego de la funcion:\n");
    mostrarPila(pila);

    while (pila != NULL) pila = pop(pila, &v);

    /* ─── Caso 2: desordenada ─── */
    printf("\nCaso 2 (desordenada):\n");
    pila = push(pila, 10);
    pila = push(pila, 3);
    pila = push(pila, 7);
    pila = push(pila, 1);

    mostrarPila(pila);
    printf("  Resultado: %s\n", estaOrdenada(&pila) ? "SI, ordenada" : "NO, desordenada");
    printf("  Pila luego de la funcion:\n");
    mostrarPila(pila);

    while (pila != NULL) pila = pop(pila, &v);

    /* ─── Caso 3: un solo elemento ─── */
    printf("\nCaso 3 (un solo elemento):\n");
    pila = push(pila, 5);

    mostrarPila(pila);
    printf("  Resultado: %s\n", estaOrdenada(&pila) ? "SI, ordenada" : "NO, desordenada");
    printf("  Pila luego de la funcion:\n");
    mostrarPila(pila);

    while (pila != NULL) pila = pop(pila, &v);

    return 0;
}
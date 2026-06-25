/*
 * Ejercicio 7.1.1
 * - Almacena el abecedario en una lista simplemente encadenada.
 * - Elimina las letras en posiciones multiplo de 3.
 * - Preserva la lista original en una lista doblemente encadenada.
 */

#include <stdio.h>
#include <stdlib.h>

/* ══════════════════════════════════════
   LISTA SIMPLEMENTE ENCADENADA
   ══════════════════════════════════════ */

struct NodoSimple {
    char                letra;
    struct NodoSimple  *siguiente;
};

/* --- Agregar letra al final --- */
struct NodoSimple *agregarSimple(struct NodoSimple *cabeza, char letra) {
    struct NodoSimple *nuevo = malloc(sizeof(struct NodoSimple));
    nuevo->letra     = letra;
    nuevo->siguiente = NULL;

    if (cabeza == NULL) return nuevo;

    struct NodoSimple *actual = cabeza;
    while (actual->siguiente != NULL)
        actual = actual->siguiente;
    actual->siguiente = nuevo;
    return cabeza;
}

/* --- Mostrar lista simple --- */
void mostrarSimple(struct NodoSimple *cabeza) {
    while (cabeza != NULL) {
        printf("[%c]", cabeza->letra);
        if (cabeza->siguiente != NULL) printf(" -> ");
        cabeza = cabeza->siguiente;
    }
    printf("\n");
}

/* --- Eliminar posiciones multiplo de 3 (1, 2, 3, 4...) --- */
struct NodoSimple *eliminarMultiplos3(struct NodoSimple *cabeza) {
    struct NodoSimple *actual   = cabeza;
    struct NodoSimple *anterior = NULL;
    int posicion = 1;

    while (actual != NULL) {
        if (posicion % 3 == 0) {
            printf("  Eliminando posicion %d: '%c'\n", posicion, actual->letra);

            struct NodoSimple *aborra = actual;
            if (anterior == NULL)
                cabeza = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;

            actual = actual->siguiente;
            free(aborra);
        } else {
            anterior = actual;
            actual   = actual->siguiente;
        }
        posicion++;
    }
    return cabeza;
}

/* ══════════════════════════════════════
   LISTA DOBLEMENTE ENCADENADA
   ══════════════════════════════════════ */

struct NodoDoble {
    char               letra;
    struct NodoDoble  *anterior;
    struct NodoDoble  *siguiente;
};

/* --- Agregar letra al final --- */
struct NodoDoble *agregarDoble(struct NodoDoble *cabeza, char letra) {
    struct NodoDoble *nuevo = malloc(sizeof(struct NodoDoble));
    nuevo->letra     = letra;
    nuevo->siguiente = NULL;
    nuevo->anterior  = NULL;

    if (cabeza == NULL) return nuevo;

    struct NodoDoble *actual = cabeza;
    while (actual->siguiente != NULL)
        actual = actual->siguiente;
    actual->siguiente = nuevo;
    nuevo->anterior   = actual;
    return cabeza;
}

/* --- Mostrar lista doble --- */
void mostrarDoble(struct NodoDoble *cabeza) {
    printf("NULL <-> ");
    while (cabeza != NULL) {
        printf("[%c]", cabeza->letra);
        if (cabeza->siguiente != NULL) printf(" <-> ");
        cabeza = cabeza->siguiente;
    }
    printf(" <-> NULL\n");
}

/* ══════════════════════════════════════
   MAIN
   ══════════════════════════════════════ */

int main(void) {

    struct NodoSimple *listaSimple = NULL;
    struct NodoDoble  *listaDoble  = NULL;

    /* 1. Cargar el abecedario en ambas listas */
    char c;
    for (c = 'A'; c <= 'Z'; c++) {
        listaSimple = agregarSimple(listaSimple, c);
        listaDoble  = agregarDoble(listaDoble,  c);
    }

    /* 2. Mostrar lista simple original */
    printf("Lista simple (original):\n");
    mostrarSimple(listaSimple);

    /* 3. Mostrar lista doble (copia preservada) */
    printf("\nLista doble (preservada):\n");
    mostrarDoble(listaDoble);

    /* 4. Eliminar multiplos de 3 de la lista simple */
    printf("\nEliminando posiciones multiplo de 3:\n");
    listaSimple = eliminarMultiplos3(listaSimple);

    /* 5. Mostrar resultado */
    printf("\nLista simple (resultado):\n");
    mostrarSimple(listaSimple);

    /* 6. Confirmar que la lista doble no cambio */
    printf("\nLista doble (sin cambios):\n");
    mostrarDoble(listaDoble);

    return 0;
}
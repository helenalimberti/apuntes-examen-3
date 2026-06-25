/*
 * Ejercicio 7.1.3
 * Lista simplemente encadenada de letras con:
 *  - insertarFinal  : agrega una letra al final
 *  - recuperar      : devuelve la letra en una posicion dada
 *  - cantidadNodos  : devuelve cuantos elementos tiene la lista
 */

#include <stdio.h>
#include <stdlib.h>

/* ══════════════════════════════════════
   ESTRUCTURA
   ══════════════════════════════════════ */

struct Nodo {
    char          letra;
    struct Nodo  *siguiente;
};

/* ══════════════════════════════════════
   INSERTAR AL FINAL
   ══════════════════════════════════════ */

struct Nodo *insertarFinal(struct Nodo *cabeza, char letra) {
    struct Nodo *nuevo = malloc(sizeof(struct Nodo));
    nuevo->letra     = letra;
    nuevo->siguiente = NULL;

    if (cabeza == NULL) return nuevo;

    struct Nodo *actual = cabeza;
    while (actual->siguiente != NULL)
        actual = actual->siguiente;

    actual->siguiente = nuevo;
    return cabeza;
}

/* ══════════════════════════════════════
   RECUPERAR ELEMENTO POR POSICION
   Posiciones desde 1 hasta n.
   Devuelve '\0' si la posicion no existe.
   ══════════════════════════════════════ */

char recuperar(struct Nodo *cabeza, int posicion) {
    struct Nodo *actual = cabeza;
    int i = 1;

    while (actual != NULL) {
        if (i == posicion)
            return actual->letra;
        actual = actual->siguiente;
        i++;
    }

    printf("  ERROR: la posicion %d no existe en la lista.\n", posicion);
    return '\0';
}

/* ══════════════════════════════════════
   CANTIDAD DE NODOS
   ══════════════════════════════════════ */

int cantidadNodos(struct Nodo *cabeza) {
    int cont = 0;
    struct Nodo *actual = cabeza;
    while (actual != NULL) {
        cont++;
        actual = actual->siguiente;
    }
    return cont;
}

/* ══════════════════════════════════════
   MOSTRAR LISTA
   ══════════════════════════════════════ */

void mostrar(struct Nodo *cabeza) {
    struct Nodo *actual = cabeza;
    while (actual != NULL) {
        printf("[%c]", actual->letra);
        if (actual->siguiente != NULL) printf(" -> ");
        actual = actual->siguiente;
    }
    printf("\n");
}

/* ══════════════════════════════════════
   MAIN
   ══════════════════════════════════════ */

int main(void) {

    struct Nodo *lista = NULL;
    char letra;
    int opcion, posicion;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Insertar letra al final\n");
        printf("2. Recuperar letra por posicion\n");
        printf("3. Ver cantidad de elementos\n");
        printf("4. Mostrar lista\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                printf("Letra a insertar: ");
                scanf(" %c", &letra);
                lista = insertarFinal(lista, letra);
                printf("Letra '%c' insertada al final.\n", letra);
                break;

            case 2:
                printf("Posicion a recuperar: ");
                scanf("%d", &posicion);
                letra = recuperar(lista, posicion);
                if (letra != '\0')
                    printf("Letra en posicion %d: '%c'\n", posicion, letra);
                break;

            case 3:
                printf("Cantidad de elementos: %d\n", cantidadNodos(lista));
                break;

            case 4:
                if (lista == NULL)
                    printf("La lista esta vacia.\n");
                else
                    mostrar(lista);
                break;

            case 0:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
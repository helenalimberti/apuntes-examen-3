/*
 * Ejercicio 7.3.2
 * Funcion que dada una cola y un numero k,
 * devuelve los primeros k elementos en el orden
 * en que habrian salido de la cola.
 * Si la cola tiene menos de k elementos, muestra un mensaje.
 *
 * Orden de ejecucion: O(k)
 * Justificacion: el unico trabajo que hace la funcion es
 * recorrer los primeros k nodos de la cola (o todos si hay menos).
 * No hay bucles anidados ni operaciones adicionales sobre n,
 * por lo tanto el tiempo crece de forma lineal con k.
 */

#include <stdio.h>
#include <stdlib.h>

/* ══════════════════════════════════════
   ESTRUCTURAS
   ══════════════════════════════════════ */

struct Nodo {
    int           valor;
    struct Nodo  *siguiente;
};

struct Cola {
    struct Nodo *frente;
    struct Nodo *final;
    int          cantidad;
};

/* ══════════════════════════════════════
   FUNCIONES DE COLA
   ══════════════════════════════════════ */

void iniciar(struct Cola *c) {
    c->frente   = NULL;
    c->final    = NULL;
    c->cantidad = 0;
}

void encolar(struct Cola *c, int v) {
    struct Nodo *n = malloc(sizeof(struct Nodo));
    n->valor     = v;
    n->siguiente = NULL;
    if (c->final == NULL) {
        c->frente = n;
        c->final  = n;
    } else {
        c->final->siguiente = n;
        c->final = n;
    }
    c->cantidad++;
}

void mostrarCola(struct Cola *c) {
    struct Nodo *act = c->frente;
    printf("  FRENTE -> ");
    while (act != NULL) {
        printf("[%d]", act->valor);
        if (act->siguiente != NULL) printf(" -> ");
        act = act->siguiente;
    }
    printf(" <- FINAL  (%d elementos)\n", c->cantidad);
}

/* ══════════════════════════════════════
   FUNCION PRINCIPAL: primeros K elementos
   
   No destruye la cola: recorre con un puntero auxiliar
   sin desencolar nada, preservando la cola original.

   Orden: O(k) — se visita cada nodo una sola vez
   hasta llegar al k-esimo o al final de la cola.
   ══════════════════════════════════════ */

int* primerosk(struct Cola *c, int k, int *tamano) {

    /* Verificar si la cola tiene menos de k elementos */
    if (c->cantidad < k) {
        printf("  ERROR: se pidieron %d elementos pero la cola solo tiene %d.\n",
               k, c->cantidad);
        *tamano = 0;
        return NULL;
    }

    /* Reservar arreglo para k elementos */
    int *resultado = malloc(k * sizeof(int));
    *tamano = k;

    /* Recorrer con puntero auxiliar (no desencola) */
    struct Nodo *actual = c->frente;
    for (int i = 0; i < k; i++) {
        resultado[i] = actual->valor;
        actual = actual->siguiente;
    }

    return resultado;
}

/* ══════════════════════════════════════
   MAIN
   ══════════════════════════════════════ */

int main(void) {

    struct Cola c;
    iniciar(&c);

    encolar(&c, 10);
    encolar(&c, 20);
    encolar(&c, 30);
    encolar(&c, 40);
    encolar(&c, 50);

    printf("Cola original:\n");
    mostrarCola(&c);
    printf("\n");

    /* --- Caso 1: k valido --- */
    int tam, *res;

    printf("Primeros 3 elementos (k=3):\n");
    res = primerosk(&c, 3, &tam);
    if (res != NULL) {
        printf("  Resultado: ");
        for (int i = 0; i < tam; i++)
            printf("%d ", res[i]);
        printf("\n");
        free(res);
    }

    printf("\n");

    /* --- Caso 2: k igual al total --- */
    printf("Primeros 5 elementos (k=5, igual al total):\n");
    res = primerosk(&c, 5, &tam);
    if (res != NULL) {
        printf("  Resultado: ");
        for (int i = 0; i < tam; i++)
            printf("%d ", res[i]);
        printf("\n");
        free(res);
    }

    printf("\n");

    /* --- Caso 3: k mayor que la cola --- */
    printf("Primeros 8 elementos (k=8, mas que la cola):\n");
    res = primerosk(&c, 8, &tam);
    if (res != NULL) {
        free(res);
    }

    printf("\nLa cola original no fue modificada:\n");
    mostrarCola(&c);

    return 0;
}
/*
 * Ejercicio 7.3.3 - MergeColas (sin typedef)
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

int desencolar(struct Cola *c) {
    struct Nodo *tmp = c->frente;
    int v     = tmp->valor;
    c->frente = tmp->siguiente;
    if (c->frente == NULL) c->final = NULL;
    free(tmp);
    c->cantidad--;
    return v;
}

int verFrente(struct Cola *c) {
    return c->frente->valor;
}

int estaVacia(struct Cola *c) {
    return c->frente == NULL;
}

/* ══════════════════════════════════════
   MERGECOLAS
   ══════════════════════════════════════ */

int* MergeColas(struct Cola *A, struct Cola *B, int *tamano) {
    *tamano = A->cantidad + B->cantidad;
    int *resultado = malloc(*tamano * sizeof(int));
    int i = 0;

    while (!estaVacia(A) && !estaVacia(B)) {
        if (verFrente(A) < verFrente(B))
            resultado[i++] = desencolar(A);
        else
            resultado[i++] = desencolar(B);
    }

    while (!estaVacia(A))
        resultado[i++] = desencolar(A);

    while (!estaVacia(B))
        resultado[i++] = desencolar(B);

    return resultado;
}

/* ══════════════════════════════════════
   MAIN
   ══════════════════════════════════════ */

int main(void) {

    struct Cola A, B;
    iniciar(&A);
    iniciar(&B);

    encolar(&A, 2);
    encolar(&A, 5);
    encolar(&A, 8);
    encolar(&A, 11);

    encolar(&B, 1);
    encolar(&B, 3);
    encolar(&B, 6);
    encolar(&B, 9);
    encolar(&B, 14);

    printf("Cola A: 2 5 8 11\n");
    printf("Cola B: 1 3 6 9 14\n\n");

    int tam;
    int *res = MergeColas(&A, &B, &tam);

    printf("Resultado (%d elementos): ", tam);
    for (int i = 0; i < tam; i++)
        printf("%d ", res[i]);
    printf("\n");

    free(res);
    return 0;
}
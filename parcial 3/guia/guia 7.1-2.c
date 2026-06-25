#include <stdio.h>
#include <stdlib.h>

// ============================================
// ESTRUCTURA DEL NODO DOBLE
// ============================================

struct NodoDoble {
    int valor;
    struct NodoDoble* anterior;
    struct NodoDoble* siguiente;
};

// ============================================
// FUNCIONES BÁSICAS
// ============================================

// Crea un nuevo nodo doble
struct NodoDoble* crearNodo(int valor) {
    struct NodoDoble* nuevo = (struct NodoDoble*) malloc(sizeof(struct NodoDoble));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }
    nuevo->valor = valor;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Agrega un nodo al final de la lista doble
void agregarAlFinal(struct NodoDoble** cabeza, int valor) {
    struct NodoDoble* nuevo = crearNodo(valor);
    
    if (*cabeza == NULL) {
        *cabeza = nuevo;
        return;
    }
    
    struct NodoDoble* actual = *cabeza;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
    nuevo->anterior = actual;
}

// Imprime la lista doble (adelante)
void imprimirLista(struct NodoDoble* cabeza) {
    printf("[");
    while (cabeza != NULL) {
        printf("%d", cabeza->valor);
        if (cabeza->siguiente != NULL) printf(" <-> ");
        cabeza = cabeza->siguiente;
    }
    printf("] -> NULL\n");
}

// Libera la memoria de la lista
void liberarLista(struct NodoDoble* cabeza) {
    struct NodoDoble* aBorrar;
    while (cabeza != NULL) {
        aBorrar = cabeza;
        cabeza = cabeza->siguiente;
        free(aBorrar);
    }
}

// ============================================
// FUNCIÓN PRINCIPAL: MERGE DE DOS LISTAS
// ============================================

struct NodoDoble* mergeListas(struct NodoDoble* lista1, struct NodoDoble* lista2) {
    // Creamos una lista vacía para el resultado
    struct NodoDoble* resultado = NULL;
    
    // Mientras ambas listas tengan elementos, comparamos
    while (lista1 != NULL && lista2 != NULL) {
        if (lista1->valor <= lista2->valor) {
            // Si el valor de lista1 es menor o igual, lo agregamos
            agregarAlFinal(&resultado, lista1->valor);
            lista1 = lista1->siguiente;  // Avanzamos en lista1
        } else {
            // Si el valor de lista2 es menor, lo agregamos
            agregarAlFinal(&resultado, lista2->valor);
            lista2 = lista2->siguiente;  // Avanzamos en lista2
        }
    }
    
    // Si quedaron elementos en lista1, los agregamos todos
    while (lista1 != NULL) {
        agregarAlFinal(&resultado, lista1->valor);
        lista1 = lista1->siguiente;
    }
    
    // Si quedaron elementos en lista2, los agregamos todos
    while (lista2 != NULL) {
        agregarAlFinal(&resultado, lista2->valor);
        lista2 = lista2->siguiente;
    }
    
    return resultado;
}

// ============================================
// FUNCIÓN PARA CREAR LISTA DESDE ARREGLO
// ============================================

struct NodoDoble* crearListaDesdeArreglo(int arreglo[], int tamaño) {
    struct NodoDoble* cabeza = NULL;
    for (int i = 0; i < tamaño; i++) {
        agregarAlFinal(&cabeza, arreglo[i]);
    }
    return cabeza;
}

// ============================================
// PROGRAMA PRINCIPAL
// ============================================

int main() {
    // Crear dos listas ordenadas
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10};
    
    struct NodoDoble* lista1 = crearListaDesdeArreglo(arr1, 5);
    struct NodoDoble* lista2 = crearListaDesdeArreglo(arr2, 5);
    
    printf("=== LISTAS ORIGINALES ===\n");
    printf("Lista 1: ");
    imprimirLista(lista1);
    printf("Lista 2: ");
    imprimirLista(lista2);
    
    // Fusionar las listas
    struct NodoDoble* listaFusionada = mergeListas(lista1, lista2);
    
    printf("\n=== LISTA FUSIONADA ===\n");
    printf("Resultado: ");
    imprimirLista(listaFusionada);
    
    // Liberar memoria
    liberarLista(lista1);
    liberarLista(lista2);
    liberarLista(listaFusionada);
    
    return 0;
}
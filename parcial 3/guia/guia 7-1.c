#include <stdio.h>
#include <stdlib.h>

// ============================================
// PARTE 1: LISTA SIMPLEMENTE ENLAZADA
// ============================================

// Nodo para lista simple (solo tiene siguiente)
struct NodoSimple {
    char letra;
    struct NodoSimple* siguiente;
};

// Crea un nodo simple
struct NodoSimple* crearNodoSimple(char letra) {
    struct NodoSimple* nuevo = (struct NodoSimple*) malloc(sizeof(struct NodoSimple));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }
    nuevo->letra = letra;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Agrega al final de la lista simple
void agregarSimple(struct NodoSimple** cabeza, char letra) {
    struct NodoSimple* nuevo = crearNodoSimple(letra);
    
    if (*cabeza == NULL) {
        *cabeza = nuevo;
        return;
    }
    
    struct NodoSimple* actual = *cabeza;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
}

// Imprime lista simple
void imprimirSimple(struct NodoSimple* cabeza) {
    printf("Lista SIMPLE: ");
    while (cabeza != NULL) {
        printf("[%c]", cabeza->letra);
        if (cabeza->siguiente != NULL) printf(" -> ");
        cabeza = cabeza->siguiente;
    }
    printf(" -> NULL\n");
}

// Elimina nodos en posiciones múltiplo de 3 (de la lista simple)
void eliminarMultiplosDe3Simple(struct NodoSimple** cabeza) {
    struct NodoSimple* actual = *cabeza;
    struct NodoSimple* anterior = NULL;
    int posicion = 1;
    
    while (actual != NULL) {
        if (posicion % 3 == 0) {
            struct NodoSimple* aBorrar = actual;
            
            if (anterior == NULL) {
                // Es el primer nodo
                *cabeza = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            
            actual = actual->siguiente;
            free(aBorrar);
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
        posicion++;
    }
}

// ============================================
// PARTE 2: LISTA DOBLEMENTE ENLAZADA (para preservar el original)
// ============================================

// Nodo para lista doble (tiene anterior y siguiente)
struct NodoDoble {
    char letra;
    struct NodoDoble* anterior;
    struct NodoDoble* siguiente;
};

// Crea un nodo doble
struct NodoDoble* crearNodoDoble(char letra) {
    struct NodoDoble* nuevo = (struct NodoDoble*) malloc(sizeof(struct NodoDoble));
    if (nuevo == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }
    nuevo->letra = letra;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Agrega al final de la lista doble
void agregarDoble(struct NodoDoble** cabeza, char letra) {
    struct NodoDoble* nuevo = crearNodoDoble(letra);
    
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

// Imprime lista doble (de adelante hacia atrás)
void imprimirDobleAdelante(struct NodoDoble* cabeza) {
    printf("Lista DOBLE (adelante): ");
    while (cabeza != NULL) {
        printf("[%c]", cabeza->letra);
        if (cabeza->siguiente != NULL) printf(" <-> ");
        cabeza = cabeza->siguiente;
    }
    printf(" <-> NULL\n");
}

// Imprime lista doble (de atrás hacia adelante)
void imprimirDobleAtras(struct NodoDoble* cabeza) {
    // Primero vamos al final
    struct NodoDoble* actual = cabeza;
    while (actual != NULL && actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    
    printf("Lista DOBLE (atrás): ");
    while (actual != NULL) {
        printf("[%c]", actual->letra);
        if (actual->anterior != NULL) printf(" <-> ");
        actual = actual->anterior;
    }
    printf(" <-> NULL\n");
}

// ============================================
// COPIA: Lista simple → Lista doble
// ============================================
struct NodoDoble* copiarSimpleADoble(struct NodoSimple* cabezaSimple) {
    struct NodoDoble* cabezaDoble = NULL;
    
    while (cabezaSimple != NULL) {
        agregarDoble(&cabezaDoble, cabezaSimple->letra);
        cabezaSimple = cabezaSimple->siguiente;
    }
    
    return cabezaDoble;
}

// ============================================
// LIBERAR MEMORIA
// ============================================
void liberarSimple(struct NodoSimple* cabeza) {
    struct NodoSimple* aBorrar;
    while (cabeza != NULL) {
        aBorrar = cabeza;
        cabeza = cabeza->siguiente;
        free(aBorrar);
    }
}

void liberarDoble(struct NodoDoble* cabeza) {
    struct NodoDoble* aBorrar;
    while (cabeza != NULL) {
        aBorrar = cabeza;
        cabeza = cabeza->siguiente;
        free(aBorrar);
    }
}

// ============================================
// PROGRAMA PRINCIPAL
// ============================================
int main() {
    struct NodoSimple* listaSimple = NULL;
    struct NodoDoble* listaDoble = NULL;
    
    // 1. Crear el abecedario en la lista simple
    printf("=== CREANDO ABECEDARIO ===\n");
    for (char c = 'A'; c <= 'Z'; c++) {
        agregarSimple(&listaSimple, c);
    }
    
    imprimirSimple(listaSimple);
    
    // 2. PRESERVAR: Copiar la lista simple a una doble
    printf("\n=== PRESERVANDO ORIGINAL EN LISTA DOBLE ===\n");
    listaDoble = copiarSimpleADoble(listaSimple);
    
    printf("Original preservado:\n");
    imprimirDobleAdelante(listaDoble);
    imprimirDobleAtras(listaDoble);
    
    // 3. Eliminar múltiplos de 3 de la lista SIMPLE
    printf("\n=== ELIMINANDO MÚLTIPLOS DE 3 DE LA LISTA SIMPLE ===\n");
    eliminarMultiplosDe3Simple(&listaSimple);
    
    printf("Lista simple modificada:\n");
    imprimirSimple(listaSimple);
    
    // 4. Mostrar que la lista doble sigue intacta (original preservado)
    printf("\n=== COMPROBANDO QUE EL ORIGINAL SE PRESERVÓ ===\n");
    printf("Lista doble (original) sigue igual:\n");
    imprimirDobleAdelante(listaDoble);
    
    // 5. Liberar memoria
    liberarSimple(listaSimple);
    liberarDoble(listaDoble);
    
    printf("\n¡Programa terminado!\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h> // Necesaria para usar malloc() (gestión de memoria dinámica)

// Definición de la estructura del nodo para una LISTA DOBLEMENTE ENLAZADA
struct Nodo {
    int dato;                   // El valor entero que guarda el nodo
    struct Nodo* siguiente;     // Puntero al próximo nodo (hacia adelante)
    struct Nodo* anterior;      // Puntero al nodo previo (hacia atrás)
};

// Prototipos de funciones (Le avisan al compilador que estas funciones existen más abajo)
void insertarNodo(struct Nodo** inicio);
void mostrarAdelante(struct Nodo* inicio);
void mostrarAtras(struct Nodo* inicio);

int main() {
    struct Nodo* inicio = NULL; // Se inicializa la lista vacía (apunta a NULL)
    int opcion;
    
    // Bucle del menú que se ejecuta al menos una vez
    do {
        printf("\n--- MENU LISTA DOBLE ---");
        printf("\n1. Insertar elemento");
        printf("\n2. Mostrar de adelante hacia atras");
        printf("\n3. Mostrar de atras hacia adelante");
        printf("\n4. Salir");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
        case 1:
            // Pasamos la DIRECCIÓN de 'inicio' (&inicio) porque la función puede modificar el puntero original
            insertarNodo(&inicio); 
            break;
        case 2:
            // Solo pasamos el valor de 'inicio' porque esta función solo lee la lista, no la modifica
            mostrarAdelante(inicio);
            break;
        case 3:
            mostrarAtras(inicio);
            break;
        case 4:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida.\n");
        }
    } while (opcion != 4); // Si el usuario presiona 4, el bucle termina
    
    return 0;
}

// Procedimiento para crear e insertar nodos (al final de la lista)
void insertarNodo(struct Nodo** inicio) {
    // Reserva memoria dinámica para el nuevo nodo en el "Heap"
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    
    // 'auxiliar' copia el contenido de inicio. Si la lista está vacía, auxiliar será NULL.
    // Nos servirá para recorrer la lista sin perder el puntero inicial.
    struct Nodo* auxiliar = *inicio; 
    
    printf("Ingrese el valor numerico: ");
    scanf("%d", &nuevo->dato); // Guarda el número ingresado dentro del nuevo nodo
    nuevo->siguiente = NULL;   // Como se inserta al final, su 'siguiente' siempre será NULL
    
    // CASO A: La lista está vacía
    if (*inicio == NULL) {
        nuevo->anterior = NULL; // Al ser el primer y único nodo, no tiene a nadie atrás
        *inicio = nuevo;        // El puntero 'inicio' de la lista ahora apunta a este nuevo nodo
    } 
    // CASO B: La lista ya tiene elementos
    else {
        // Bucle para mover 'auxiliar' hasta el último nodo actual de la lista
        // Se detiene cuando encuentra el nodo cuyo 'siguiente' es NULL
        while (auxiliar->siguiente != NULL) {
            auxiliar = auxiliar->siguiente; // Avanza al siguiente nodo
        }
        
        // Aquí hacemos el doble enganche:
        auxiliar->siguiente = nuevo; // El que antes era el último, ahora apunta hacia adelante al 'nuevo'
        nuevo->anterior = auxiliar;  // El 'nuevo' apunta hacia atrás al que era el último (auxiliar)
    }
    printf("Elemento insertado correctamente.\n");
}

// Procedimiento para recorrer de adelante hacia atrás (recorrido clásico)
void mostrarAdelante(struct Nodo* inicio) {
    struct Nodo* auxiliar = inicio; // Empezamos desde el primer nodo
    
    // Validación: Si inicio es NULL, la lista no tiene elementos
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return; // Rompe la función aquí mismo y regresa al menú
    }
    
    printf("Lista (Adelante -> Atras): ");
    // Mientras 'auxiliar' no llegue al final (más allá del último nodo, que es NULL)
    while (auxiliar != NULL) {
        printf("[%d] ", auxiliar->dato); // Imprime el dato del nodo actual
        auxiliar = auxiliar->siguiente;  // Avanza al siguiente nodo
    }
    printf("\n");
}

// Procedimiento para recorrer de atrás hacia adelante
void mostrarAtras(struct Nodo* inicio) {
    struct Nodo* auxiliar = inicio; // Empezamos desde el primer nodo
    
    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }
    
    // PASO 1: Viajar hasta el último nodo de la lista
    // (Necesitamos llegar al final para poder empezar a retroceder)
    while (auxiliar->siguiente != NULL) {
        auxiliar = auxiliar->siguiente;
    }
    
    // Al salir del bucle anterior, 'auxiliar' está parado exactamente en el ÚLTIMO nodo
    printf("Lista (Atras -> Adelante): ");
    
    // PASO 2: Caminar hacia atrás usando el puntero 'anterior'
    // Se detendrá cuando pasemos el primer nodo (cuyo 'anterior' es NULL)
    while (auxiliar != NULL) {
        printf("[%d] ", auxiliar->dato); // Imprime el dato
        auxiliar = auxiliar->anterior;   // Retrocede al nodo previo
    }
    printf("\n");
}
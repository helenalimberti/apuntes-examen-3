#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo (Se mantiene igual)
struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
};

// Prototipos de funciones actualizados
// 'insertarNodo' ahora recibe la dirección de ambos punteros externos (inicio y fin)
void insertarNodo(struct Nodo** inicio, struct Nodo** fin);
void mostrarAdelante(struct Nodo* inicio);
void mostrarAtras(struct Nodo* fin);      // Recibe 'fin' para arrancar directamente desde atrás

int main() {
    // Declaración de los DOS punteros externos principales de control:
    struct Nodo* inicio = NULL; // Guarda la dirección del primer nodo
    struct Nodo* fin    = NULL; // NUEVO: Guarda la dirección del último nodo
    int opcion;

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
            // Pasamos las direcciones de ambos punteros de control (&inicio y &fin) 
            // porque la inserción puede modificar a cualquiera de los dos.
            insertarNodo(&inicio, &fin);  
            break;
        case 2:
            // Para mostrar hacia adelante solo pasamos el puntero 'inicio' (Copia de lectura)
            mostrarAdelante(inicio);
            break;
        case 3:
            // NUEVO: Pasamos 'fin' directamente, nos ahorramos viajar desde el inicio
            mostrarAtras(fin);            
            break;
        case 4:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida.\n");
        }
    } while (opcion != 4);

    return 0;
}

// Inserción al final de manera instantánea — Complejidad O(1)
void insertarNodo(struct Nodo** inicio, struct Nodo** fin) {
    // Reservamos memoria para el nuevo nodo
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));

    printf("Ingrese el valor numerico: ");
    scanf("%d", &nuevo->dato);
    nuevo->siguiente = NULL; // Al insertarse al final, nadie va después de él

    // CASO A: La lista está completamente vacía
    if (*inicio == NULL) {
        nuevo->anterior = NULL; // No hay nadie antes que él
        *inicio = nuevo;   // El puntero externo 'inicio' apunta a este primer nodo
        *fin    = nuevo;   // El puntero externo 'fin' también apunta a este único nodo
    }
    // CASO B: La lista ya tiene elementos (¡Aquí se nota la magia de 'fin'!)
    // ¡YA NO EXISTE EL BUCLE 'auxiliar = auxiliar->siguiente'!
    else {
        // 1. El nodo nuevo se conecta hacia atrás con el que actualmente es el último (*fin)
        nuevo->anterior   = *fin;  
        
        // 2. El actual último nodo se conecta hacia adelante con el nuevo nodo
        (*fin)->siguiente = nuevo; 
        
        // 3. Actualizamos el puntero de control: 'fin' ahora apunta al nuevo nodo (el verdadero último)
        *fin = nuevo;              
    }

    printf("Elemento insertado correctamente.\n");
}

// Procedimiento clásico para recorrer desde el inicio hacia adelante
void mostrarAdelante(struct Nodo* inicio) {
    struct Nodo* auxiliar = inicio; // Creamos el inspector temporal desde el 'inicio'

    if (inicio == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    printf("Lista (Adelante -> Atras): ");
    while (auxiliar != NULL) {
        printf("[%d] ", auxiliar->dato);
        auxiliar = auxiliar->siguiente; // Avanza usando punteros internos
    }
    printf("\n");
}

// Muestra la lista al revés en tiempo récord — Complejidad O(1) en el arranque
void mostrarAtras(struct Nodo* fin) {
    // Inicializamos el inspector temporal directamente en el puntero 'fin'.
    // Nos ahorramos el bucle while que antes usábamos para llegar hasta aquí.
    struct Nodo* auxiliar = fin; 

    if (fin == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    // Ya estamos parados en el extremo final, solo nos queda caminar en reversa
    printf("Lista (Atras -> Adelante): ");
    while (auxiliar != NULL) {
        printf("[%d] ", auxiliar->dato);
        auxiliar = auxiliar->anterior; // Retrocede usando los punteros internos anteriores
    }
    printf("\n");
}
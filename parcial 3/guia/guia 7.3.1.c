#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// ESTRUCTURAS
// ============================================

// Información del alumno
struct Alumno {
    int dni;
    char nombre[50];
    char apellido[50];
    char link[200];
};

// Nodo de la cola
struct NodoCola {
    struct Alumno alumno;
    struct NodoCola* siguiente;
};

// Estructura de la cola
struct Cola {
    struct NodoCola* frente;
    struct NodoCola* final;
    int tamaño;
};

// ============================================
// FUNCIONES DE LA COLA
// ============================================

// 1. Crear una cola vacía
struct Cola* crearCola() {
    struct Cola* nueva = (struct Cola*) malloc(sizeof(struct Cola));
    nueva->frente = NULL;
    nueva->final = NULL;
    nueva->tamaño = 0;
    return nueva;
}

// 2. Crear un nodo con los datos del alumno
struct NodoCola* crearNodo(struct Alumno alumno) {
    struct NodoCola* nuevo = (struct NodoCola*) malloc(sizeof(struct NodoCola));
    nuevo->alumno = alumno;
    nuevo->siguiente = NULL;
    return nuevo;
}

// 3. Agregar un alumno al final de la cola (encolar)
void encolar(struct Cola* cola, struct Alumno alumno) {
    struct NodoCola* nuevo = crearNodo(alumno);
    
    if (cola->frente == NULL) {
        // Si la cola está vacía
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        // Agregar al final
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
    
    cola->tamaño++;
    printf("  [OK] %s %s (DNI: %d) agregado a la cola. Posición: %d\n", 
           alumno.nombre, alumno.apellido, alumno.dni, cola->tamaño);
}

// 4. Quitar y devolver el primer alumno de la cola (desencolar)
struct Alumno desencolar(struct Cola* cola) {
    struct Alumno vacio;
    vacio.dni = 0;
    strcpy(vacio.nombre, "");
    strcpy(vacio.apellido, "");
    strcpy(vacio.link, "");
    
    if (cola->frente == NULL) {
        printf("  [ERROR] La cola está vacía\n");
        return vacio;
    }
    
    struct NodoCola* nodoAEliminar = cola->frente;
    struct Alumno alumno = nodoAEliminar->alumno;
    
    cola->frente = cola->frente->siguiente;
    
    if (cola->frente == NULL) {
        cola->final = NULL;
    }
    
    cola->tamaño--;
    free(nodoAEliminar);
    
    printf("  [OK] %s %s (DNI: %d) desencolado para corregir\n", 
           alumno.nombre, alumno.apellido, alumno.dni);
    return alumno;
}

// 5. Ver el primer alumno sin desencolar
struct Alumno verFrente(struct Cola* cola) {
    struct Alumno vacio;
    vacio.dni = 0;
    strcpy(vacio.nombre, "");
    strcpy(vacio.apellido, "");
    strcpy(vacio.link, "");
    
    if (cola->frente == NULL) {
        printf("  [ERROR] La cola está vacía\n");
        return vacio;
    }
    
    return cola->frente->alumno;
}

// 6. Verificar si la cola está vacía
int estaVacia(struct Cola* cola) {
    if (cola->frente == NULL) {
        return 1;  // Verdadero
    }
    return 0;  // Falso
}

// 7. Obtener el tamaño de la cola
int obtenerTamaño(struct Cola* cola) {
    return cola->tamaño;
}

// 8. Imprimir toda la cola
void imprimirCola(struct Cola* cola) {
    if (cola->frente == NULL) {
        printf("  Cola vacía\n");
        return;
    }
    
    struct NodoCola* actual = cola->frente;
    printf("  Cola (tamaño: %d) - Frente → Final:\n", cola->tamaño);
    int pos = 1;
    while (actual != NULL) {
        printf("    %d. DNI: %d | %s, %s | Link: %s\n", 
               pos,
               actual->alumno.dni,
               actual->alumno.apellido,
               actual->alumno.nombre,
               actual->alumno.link);
        actual = actual->siguiente;
        pos++;
    }
}

// 9. Imprimir los datos de un alumno
void imprimirAlumno(struct Alumno alumno) {
    printf("    DNI: %d\n", alumno.dni);
    printf("    Nombre: %s %s\n", alumno.nombre, alumno.apellido);
    printf("    Link del proyecto: %s\n", alumno.link);
}

// 10. Liberar toda la memoria de la cola
void liberarCola(struct Cola* cola) {
    struct NodoCola* actual = cola->frente;
    struct NodoCola* aBorrar;
    
    while (actual != NULL) {
        aBorrar = actual;
        actual = actual->siguiente;
        free(aBorrar);
    }
    
    free(cola);
    printf("  [OK] Memoria liberada\n");
}

// ============================================
// FUNCIÓN PARA CREAR UN ALUMNO (ayuda)
// ============================================

struct Alumno crearAlumno(int dni, char nombre[], char apellido[], char link[]) {
    struct Alumno nuevo;
    nuevo.dni = dni;
    strcpy(nuevo.nombre, nombre);
    strcpy(nuevo.apellido, apellido);
    strcpy(nuevo.link, link);
    return nuevo;
}

// ============================================
// FUNCIÓN PARA CORREGIR PROYECTOS
// ============================================

void corregirProyectos(struct Cola* cola) {
    if (estaVacia(cola)) {
        printf("\n  [ERROR] No hay proyectos para corregir\n");
        return;
    }
    
    printf("\n=== INICIANDO CORRECCIÓN DE PROYECTOS ===\n");
    printf("(Orden FIFO - Primero en entregar, primero en corregir)\n\n");
    
    int numero = 1;
    while (!estaVacia(cola)) {
        printf("Corrección #%d:\n", numero);
        struct Alumno alumno = desencolar(cola);
        imprimirAlumno(alumno);
        printf("  [OK] Proyecto corregido\n\n");
        numero++;
    }
    
    printf("=== CORRECCIÓN FINALIZADA ===\n");
    printf("Total de proyectos corregidos: %d\n", numero - 1);
}

// ============================================
// PROGRAMA PRINCIPAL
// ============================================

int main() {
    printf("=== SISTEMA DE ENTREGA DE PROYECTOS ===\n");
    printf("(Los proyectos se corrigen por orden de entrega)\n\n");
    
    // 1. Crear la cola
    struct Cola* cola = crearCola();
    
    // 2. Registrar entregas (los alumnos entregan sus proyectos)
    printf("1. REGISTRANDO ENTREGAS:\n\n");
    
    // Crear alumnos
    struct Alumno a1 = crearAlumno(12345678, "Juan", "Perez", "github.com/juanperez/proyecto");
    struct Alumno a2 = crearAlumno(23456789, "Maria", "Gomez", "github.com/mariagomez/proyecto");
    struct Alumno a3 = crearAlumno(34567890, "Carlos", "Lopez", "github.com/carloslopez/proyecto");
    struct Alumno a4 = crearAlumno(45678901, "Ana", "Martinez", "github.com/anamartinez/proyecto");
    struct Alumno a5 = crearAlumno(56789012, "Pedro", "Sanchez", "github.com/pedrosanchez/proyecto");
    
    // Encolar (agregar a la cola)
    encolar(cola, a1);
    encolar(cola, a2);
    encolar(cola, a3);
    encolar(cola, a4);
    encolar(cola, a5);
    
    // 3. Mostrar el estado de la cola
    printf("\n2. ESTADO DE LA COLA:\n");
    imprimirCola(cola);
    
    // 4. Mostrar quién es el primero
    printf("\n3. PRÓXIMO EN SER CORREGIDO:\n");
    if (!estaVacia(cola)) {
        struct Alumno primero = verFrente(cola);
        printf("  El primer proyecto en la fila es de:\n");
        printf("  %s %s (DNI: %d)\n", 
               primero.nombre, primero.apellido, primero.dni);
    }
    
    // 5. Corregir proyectos
    printf("\n4. CORRECCIÓN DE PROYECTOS:\n");
    corregirProyectos(cola);
    
    // 6. Mostrar estado final
    printf("\n5. ESTADO FINAL DE LA COLA:\n");
    imprimirCola(cola);
    printf("  Tamaño: %d\n", obtenerTamaño(cola));
    
    // 7. Liberar memoria
    printf("\n6. LIBERANDO MEMORIA:\n");
    liberarCola(cola);
    
    printf("\n¡Programa terminado!\n");
    return 0;
}
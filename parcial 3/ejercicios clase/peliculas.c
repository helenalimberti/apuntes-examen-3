#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pelicula
{
  char nombre[50];
  int anio;
  struct pelicula *siguiente;
};

void insertarAlInicio(struct pelicula **cabeza, const char *nombre, int anio)
{
  struct pelicula *nuevoNodo = (struct pelicula *)malloc(sizeof(struct pelicula));
  strcpy(nuevoNodo->nombre, nombre);
  nuevoNodo->anio = anio;
  nuevoNodo->siguiente = *cabeza;
  *cabeza = nuevoNodo;
}

void insertarAlFinal(struct pelicula **cabeza, const char *nombre, int anio)

{
  struct pelicula *nuevoNodo = (struct pelicula *)malloc(sizeof(struct pelicula));
  strcpy(nuevoNodo->nombre, nombre);
  nuevoNodo->anio = anio;
  nuevoNodo->siguiente = NULL;

  if (*cabeza == NULL)
  {
    *cabeza = nuevoNodo;
    return;
  }

  struct pelicula *temp = *cabeza;
  while (temp->siguiente != NULL)
  {
    temp = temp->siguiente;
  }
  temp->siguiente = nuevoNodo;
}

void eliminarPersona(struct pelicula **cabeza, int anio)
{
  struct pelicula *temp = *cabeza;
  struct pelicula *anterior = NULL;

  while (temp != NULL && temp->anio != anio)
  {
    anterior = temp;
    temp = temp->siguiente;
  }

  if (temp == NULL)
    return;

  if (anterior == NULL)
  {
    *cabeza = temp->siguiente;
  }
  else
  {
    anterior->siguiente = temp->siguiente;
  }

  free(temp);
}

int buscar(struct pelicula *cabeza, int anio)
{
  struct pelicula *temp = cabeza;
  while (temp != NULL)
  {
    if (temp->anio == anio)
    {
      return 1;
    }
    temp = temp->siguiente;
  }
  return 0;
}

void mostrarLista(struct pelicula *nodo)
{
  while (nodo != NULL)
  {
    printf("%s (anio: %d) -> ", nodo->nombre, nodo->anio);
    nodo = nodo->siguiente;
  }
  printf("NULL\n");
}

int main()
{
  struct pelicula *lista = NULL;

  insertarAlInicio(&lista, "Perez", 12345678);
  insertarAlInicio(&lista,  "Gomez", 87654321);

  insertarAlFinal(&lista, "Lopez", 11223344);
  insertarAlFinal(&lista, "Martinez", 55667788);

  printf("Lista actual:\n");
  mostrarLista(lista);

  eliminarPersona(&lista, 87654321);
  printf("Luego de eliminar anio 87654321:\n");
  mostrarLista(lista);

  if (buscar(lista, 11223344))
  {
    printf("La pelicula del anio 11223344 está en la lista.\n");
  }
  else
  {
    printf("La pelicula del anio 11223344 no está en la lista.\n");
  }

  return 0;
}
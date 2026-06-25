int buscar(Nodo *raiz, int valor) {
    if (raiz == NULL)
        return 0;   // No encontrado

    if (raiz->dato == valor)
        return 1;   // Encontrado

    return buscar(raiz->izq, valor) ||
           buscar(raiz->der, valor);
}
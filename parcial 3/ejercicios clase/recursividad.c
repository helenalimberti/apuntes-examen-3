#include <stdio.h>

int potencia(int base, int exp) {
    // Caso base: cualquier numero elevado a 0 es 1
    if (exp == 0) {
        return 1;
    }
    // Paso recursivo: base^exp = base * base^(exp-1)
    return base * potencia(base, exp - 1);
}

int main() {
    int base, exp;

    printf("Ingresa la base: ");
    scanf("%d", &base);

    printf("Ingresa el exponente: ");
    scanf("%d", &exp);

    int resultado = potencia(base, exp);

    printf("%d elevado a la %d es: %d\n", base, exp, resultado);

    return 0;
}
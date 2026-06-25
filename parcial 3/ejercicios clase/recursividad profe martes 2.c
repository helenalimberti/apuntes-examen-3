#include <stdio.h> 
#include <conio.h>
    
long int potencia(int base, int exponente);
        
int main ()
{
    int valor;
    int valor2;
    long int result; 
    
    printf("\nIngrese la base: "); 
    scanf("%d", &valor); 
    
    printf("Ingrese el exponente: "); 
    scanf("%d", &valor2); 
    
    // CASO ESPECIAL 1: Indeterminación matemática (0^0)
    if (valor == 0 && valor2 == 0)
    {
        printf("Error: 0 elevado a la 0 es una indeterminacion matematica.\n");
    }
    // Restricción de exponentes negativos
    else if (valor2 < 0) 
    {
        printf("Error: Este programa solo calcula exponentes mayores o iguales a 0.\n"); 
    }
    else
    {
        result = potencia(valor, valor2);
        printf("\nEl resultado de %d elevado a la %d es: %ld\n", valor, valor2, result);
    }
    
    getch(); 
    return 0;
}

long int  potencia(int base, int exponente)
{
    // CASO ESPECIAL 2: El exponente es 0 (ej: 5^0 = 1)
    // Va primero porque si la base también fuera 0, ya lo filtró el main.
    if (exponente == 0) 
        return 1;
        
    // CASO ESPECIAL 3: La base es 0 y el exponente es mayor a 0 (ej: 0^5 = 0)
    if (base == 0)
        return 0;
        
    // Caso recursivo normal
    return base * potencia(base, exponente - 1);
}
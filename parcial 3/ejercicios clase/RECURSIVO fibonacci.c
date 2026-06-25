#include <stdio.h> 
#include <conio.h>
    
long int fibonacci(int n);
        
int main ()
{
    int valor;
    long int result; 
    
    printf("\nIngrese la posicion de Fibonacci: "); 
    scanf("%d", &valor);
    
    if (valor < 0) 
    {
        printf("Error: No existen posiciones negativas.\n"); 
    }
    else
    {
        result = fibonacci(valor);
        printf("\nEl calculo de Fibonacci de la posicion %d es %ld\n", valor, result);
    }
    
    getch(); 
    return 0;
}

long int fibonacci(int n)
{
    // Casos base: Las primeras dos posiciones de la serie ya están definidas
    if (n == 0) 
        return 0;
    if (n == 1) 
        return 1;
        
    // Caso recursivo: Llama a la función para los dos números anteriores y los suma
    return fibonacci(n - 1) + fibonacci(n - 2);
}
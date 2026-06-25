#include <stdio.h> 
#include <conio.h>
	
long int factorial(int n);
		
	int main ()
	{
		int valor;
		long int result; printf("\nIngrese numero:"); scanf("%d",&valor);
		if (valor < 0) printf("Error"); 
		else
		{
			result=factorial(valor);
			printf("\nEl factorial de %d es %ld",valor,result);
		}
		getch(); return 0;
	}
	long int factorial(int n)
	{
		long int resp; 
		if(n==1 || n==0) //caso base
			return 1;
        else //recursividad
			resp=n* factorial(n-1);
		return (resp);
	}
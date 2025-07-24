//EJERCICIO 3:
#include <stdio.h>

int suma_hasta(int n);

int main(void){
    int n;
    printf("Ingrese valor de n: \n");
    scanf("%d", &n);
    if(n<0){
        printf("Error, su numero es negativo");
    }
    else{
        n = suma_hasta(n);
        printf("La suma resultante de la funcion es: %d",n);
    }
    return 0;
}

int suma_hasta(int n){
    n = (n*(n+1))/2;    
}

/*
    EJEMPLOS:
    Ingrese valor de n: 
    4
    La suma resultante de la funcion es: 10

    Ingrese valor de n: 
    30
    La suma resultante de la funcion es: 465
*/

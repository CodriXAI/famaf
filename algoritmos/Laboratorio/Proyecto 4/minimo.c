//EJERCICIO 1B1:
#include <stdio.h>
#include <assert.h>
int main(void){
    //Solicitar variables a comparar
    int x,y;

    printf("Ingrese valor para x: \n");
    scanf("%d",&x);

    printf("Ingrese valor para y: \n");
    scanf("%d",&y);

    /*Definicion de una variable entera, la cual tiene un condicional ternario que compara dos valores
        (x<y)? = Condicion
        x = Caso que sea cierto (True)
        y = Caso que no sea cierto (False)
    */
    int minimo = (x<y) ? x : y;
    printf("El valor minimo entre %d y %d es: %d",x,y,minimo);

    // Precondición: x e y son numeros enteros
    assert(sizeof(x) == sizeof(int));
    assert(sizeof(y) == sizeof(int));
    
    // Postcondición: la variable minimo es el valor mínimo entre x e y
    assert(minimo == (x < y) ? x : y);

    return 0;
}
/*
    EJEMPLOS:
    Ingrese valor para x: 
    20
    Ingrese valor para y: 
    4
    El valor minimo entre 20 y 4 es: 4

    Ingrese valor para x: 
    1
    Ingrese valor para y: 
    3
    El valor minimo entre 1 y 3 es: 1
*/
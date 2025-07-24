/*Ejercicio 3 1b:*/
#include <stdio.h>
int main(void){
    int x,y;
    printf("Ingrese valor para la variable x: \n");
    scanf("%d", &x);
    printf("Ingrese valor para la variable y: \n");
    scanf("%d", &y);
    x = x + y;
    y = y + y;
    printf("Valor de X: %d \n",x);
    printf("Valor de Y: %d \n",y);
    return 0;
}
/*
    Similar al 1a, pide DOS valores para las variables x y, el programa transforma el estado de
    cada una, y devuelve su correspondiente valor
*/
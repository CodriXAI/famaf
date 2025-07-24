/*Ejercicio 3 1b:*/
#include <stdio.h>
int main(void){
    int x,y;
    printf("Ingrese valor para la variable x: \n");
    scanf("%d", &x);
    printf("Ingrese valor para la variable y: \n");
    scanf("%d", &y);
    y = y + y;
    x = x + y;
    printf("Valor de Y: %d \n",y);
    printf("Valor de X: %d \n",x);
    return 0;
}
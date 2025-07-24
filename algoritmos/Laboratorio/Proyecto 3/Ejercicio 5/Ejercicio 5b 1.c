/*Ejercicio 5b 1:*/
#include <stdio.h>
int main(void){
    int x,y,i;
    printf("Ingrese el valor de la variable x: \n");
    scanf("%d",&x);
    printf("Ingrese el valor de la variable y: \n");
    scanf("%d",&y);
    printf("Ingrese el valor de la variable i: \n");
    scanf("%d",&i);
    i = 0;
    while(x>=y){
        x = x - y;
        i = i + 1;
        printf("Valor Parcial X = %d \n",x);
        printf("Valor Parcial Y = %d \n",y);
        printf("Valor Parcial i = %d \n",i);
        printf(" \n");
    }
    printf("Valores Finales: x y i = %d %d %d",x,y,i);
    return 0;
}

/*
    Con valores ajenos al Proyecto:

    x = 20 / y = 2 / i = 2

    {a1}
    x := 18 / y = 2 / i := 1

    {a2}
    x := 16 / y = 2 / i := 2

    {a3}
    x := 14 / y = 2 / i := 3

    ....

    {a10}
    x := 0 / y = 2 / i := 10

    - Fin del bucle -

*/

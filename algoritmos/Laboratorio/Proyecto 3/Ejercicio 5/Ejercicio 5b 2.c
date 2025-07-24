/*Ejercicio 5b 1:*/
#include <stdio.h>
#include <stdbool.h>
int main(void){
    /*Declaracion de variables:*/
    int x,i;
    int temp;
    bool res;

    /*Solicitud al usuario:*/
    printf("Ingrese el valor de la variable x: \n");
    scanf("%d",&x);
    printf("Ingrese el valor de la variable i: \n");
    scanf("%d",&i);
    printf("Ingrese el valor de la variable res (0 = False, 1 = True): \n");
    scanf("%d",&temp);

    /*Asignacion de Estados:*/
    i = 2;
    res = true;
    
    while(i<x && res){
        res = res && (x%i!=0);
        i = i + 1;

        printf("Valor Parcial X = %d \n",x);
        printf("Valor Parcial i = %d \n",i);
        printf("Valor Parcial res = %d \n",res);
        printf(" \n");
    }
    printf("Valores Finales de x,i,res = %d %d %d",x,i,res);
    return 0;
}

/*
    Con valores ajenos al proyecto:
    x = 8 / i = 4 / res = false

    {a1}
    x = 8 / i := 3 / res := false

    - Fin del bucle -

    Ahora con:
    x = 9 / i = 1 / res = true

    {a1}
    x = 9 / i := 3 / res := true

    {a2}
    x = 9 / i := 4 / res := false

    - Fin del bucle -
*/

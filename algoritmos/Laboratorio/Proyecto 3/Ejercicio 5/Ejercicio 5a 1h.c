/*Ejercicio 5 1h:*/
#include <stdio.h>
int main(void){
    int i;
    printf("Ingrese el valor de la variable i: \n");
    scanf("%d",&i);
    while(i!=0){
        i = i - 1;
        printf("Valor parcial: %d \n",i);
    }
    return 0;
}
/*
    Solicitamos un valor i y en un bucle while vamos disminuyendo de 1 en 1 hasta llegar a 0
*/
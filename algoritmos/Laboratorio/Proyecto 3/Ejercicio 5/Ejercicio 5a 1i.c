/*Ejercicio 5 1h:*/
#include <stdio.h>
int main(void){
    int i;
    printf("Ingrese el valor de la variable i: \n");
    scanf("%d",&i);
    while(i!=0){
        i = 0;
        printf("Valor parcial: %d \n",i);
    }
    return 0;
}
/*
    Solicitamos un valor i y automaticamente se cambia su estado a 0 finalizando el bucle
*/
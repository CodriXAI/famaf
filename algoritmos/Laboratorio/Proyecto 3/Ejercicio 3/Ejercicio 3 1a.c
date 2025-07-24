/*Ejercicio 3 1a:*/
#include <stdio.h>
int main(void){
    int x;
    printf("Ingrese el valor de la variable x: \n");
    scanf("%d", &x);
    x = 5;
    printf("El valor de la variable x: %d \n",x);
    return 0;
}
/*
    Este programa solicita al usuario un valor para la variable X e independientemente lo que
    el usuario coloque. Siempre va a devolver x = 5, porque nosotros cambiamos el estado posterior
    a la solicitud del dato
*/
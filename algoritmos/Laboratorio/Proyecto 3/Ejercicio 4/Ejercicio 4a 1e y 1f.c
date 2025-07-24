/*Ejercicio 4 1e y 1f:*/
#include <stdio.h>
int main(void){
    int x,y;
    printf("Ingrese valor de la variable x \n");
    scanf("%d", &x);
    printf("Ingrese valor de la variable y \n");
    scanf("%d", &y);
    if(x>=y){
        x=0;
    }else if(x<=y){
        x=2;
    }
    return 0;
}
/*
    El programa solicita dos valores iniciales para x y, luego con condiciones se modifica el
    estado dependiento el caso
*/
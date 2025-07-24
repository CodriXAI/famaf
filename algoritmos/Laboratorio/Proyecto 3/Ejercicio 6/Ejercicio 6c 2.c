/*En mi caso, voy a modificar otro programa que es el 5b 1, tambien pudiendose
utilizar las funciones pedir entero e imprimir entero*/
#include <stdio.h>
/*Definir prototipo de las funciones:*/
int pedir_entero(char name);
void imprimir_entero(int x, char name);

int main(void){
    int x,y,i;
    /*Usando pedir entero*/
    x = pedir_entero('x');
    y = pedir_entero('y');
    i = pedir_entero('i');
    i = 0;
    while(x>=y){
        x = x - y;
        i = i + 1;
        /*Usando imprimir entero*/
        imprimir_entero(x,'x');
        imprimir_entero(y,'y');
        imprimir_entero(i,'i');
        printf(" \n");
    }
    printf("Valores Finales: x y i son \n");
    /*Usando imprimir entero*/
    imprimir_entero(x,'x');
    imprimir_entero(y,'y');
    imprimir_entero(i,'i');
    return 0;
}
int pedir_entero(char name){
     int x;
     printf("Ingrese valor para la variable %c: ",name);
     scanf("%d",&x);
     return x;
}

void imprimir_entero(int x, char name){
    printf("El valor de la variable %c es %d \n",name,x);
}
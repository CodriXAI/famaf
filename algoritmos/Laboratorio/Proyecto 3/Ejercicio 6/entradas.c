/*Ejercicio 6a 1*/
#include <stdio.h>
/*Definir prototipo de las funciones:*/
int pedir_entero(char name);
void imprimir_entero(int x, char name);

/*Ejecucion de funciones*/
int main(void){
    int num = pedir_entero('n');
    imprimir_entero(num, 'n');
    return 0;
}

/*Definiciones de las funciones:*/
int pedir_entero(char name){
     int x;
     printf("Ingrese valor para la variable %c: ",name);
     scanf("%d",&x);
     return x;
}

void imprimir_entero(int x, char name){
    printf("El valor que ud ingreso en la variable %c es %d",name,x);
}


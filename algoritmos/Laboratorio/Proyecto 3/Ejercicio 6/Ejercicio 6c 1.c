/*Ejercicio 4b modificado*/
#include <stdio.h>
/*Definir prototipo de las funciones:*/
int pedir_entero(char name);
void imprimir_entero(int x, char name);

int main(void){
    /*Definicion de variables*/
    int x,y,z,m;

    /*Llamada a la funcion pedir entero en cada variable*/
    x = pedir_entero('x');
    y = pedir_entero('y');
    z = pedir_entero('z');
    m = pedir_entero('m');

    /*Programa 1: (P1)*/
    if(x<y){
        m=x;
    }else if(x>=y){
        m=y;
    }
    /*Programa 2: (P2)*/
    if(m<z){
        
    }else if(m>=z){
        m=z;
    }
    /*Valor final de m (En el ejemplo del proyecto, el valor final seria 4)*/
    imprimir_entero(m,'m');
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
    printf("El valor de la variable %c es %d",name,x);
}

/*
    La ventaja de trabajar con funciones es la optimizacion del codigo, siendo mas legible y
    ordenado.

    Si tuviera que escribir otra funcion en este ejercicio, seria una dedicada al if y sus condiciones
    para modificar el valor de m, como un filtro.
*/

/*
    Ejemplo con valores del proyecto:
    x=5 / y=4 / z=8 / m=0
    {P1 : Caso x>=y : m:=y}
    Estado Actual:
    x=5 / y=4 / z=8 / "m=4"
    {P2 : Caso m<z : skip}
    Estado Final:
    x=5 / y=4 / z=8 / m=4
*/

/*
    Ejemplo con estos valores:
    "x=8 / y=2 / z=6 / m=3"
    {P1 : Caso x>=y : m:=y}
    Estado Actual:
    x=8 / y=2 / z=6 / "m=2"
    {P2 : Caso m<z : skip}
    Estado Final:
    x=8 / y=2 / z=6 / m=2
*/
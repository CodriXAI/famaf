/*Ejercicio 4 1e y 1f:*/
#include <stdio.h>
int main(void){
    /*Definicion de variables*/
    int x,y,z,m;

    /*Solicitud de los datos de las variables x,y,z,m*/
    printf("Ingrese valor de la variable x \n");
    scanf("%d", &x);
    printf("Ingrese valor de la variable y \n");
    scanf("%d", &y);
    printf("Ingrese valor de la variable z \n");
    scanf("%d", &z);
    printf("Ingrese valor de la variable w \n");
    scanf("%d", &m);

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
    printf("El valor de la variable m es: \n %d",m);
    return 0;
}
/*Basicamente, lo que realiza este programa es, a base de ciertos casos, modifica o mantiene el valor
de la variable m, cambiando entremedio los estados de la misma
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
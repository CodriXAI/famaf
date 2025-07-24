//EJERCICIO 2A:
/*
    Especificacion del programa:
    {Pre: x = X, y = Y}
    x := x + 1
    y := X + Y;
    {Post: x = X + 1, y = X + Y}
*/
#include<stdio.h>
#include<assert.h>
//Prototipo de pedirEntero
int pedirEntero(int n, char c);

int main(void){
    /*Definimos las variables*/
    int x,y;
    x = pedirEntero(x,'x');
    y = pedirEntero(y,'y');

    //Guardo el valor inicial de x en una variable auxiliar
    int xaux = x;
    int yaux = y;

    //Precondicion:
    assert(x == xaux);
    assert(y == yaux);

    //Se produce el cambio
    x = x + 1;
    y = xaux + y;

    printf("Se han realizado cambios, ahora x = %d e y = %d\n",x,y);

    //Postcondicion:
    assert(x == xaux + 1);
    assert(y == xaux + yaux);
}
//Funcion pedirEntero general para pedir cualquier dato
int pedirEntero(int n, char c){
    printf("Ingresar valor de la variable %c\n",c);
    scanf("%d", &n);
    return n;
}

/*
    EJEMPLOS:
    Ingresar valor de la variable x
    3
    Ingresar valor de la variable y
    5
    Se han realizado cambios, ahora x = 4 e y = 8

    Ingresar valor de la variable x
    7
    Ingresar valor de la variable y
    10
    Se han realizado cambios, ahora x = 8 e y = 17
*/
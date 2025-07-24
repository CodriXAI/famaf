//EJERCICIO 2B:
/*
    Especificacion del programa
    {Pre: x = X, y = Y, z = Z}
    x := Y
    y := Y + X + Z
    z := Y + X
    {Post: x = Y, y = Y + X + Z, z = Y + X}
*/
#include<stdio.h>
#include<assert.h>
int pedirEntero(int n, char c);
int main(void){
    int x,y,z;
    
    x = pedirEntero(x,'x');
    y = pedirEntero(y,'y');
    z = pedirEntero(z,'z');
    
    int xaux = x;
    int yaux = y;
    int zaux = z;

    //Precondicion:
    assert(x == xaux);
    assert(y == yaux);
    assert(z == zaux);

    x = y;
    y = yaux + xaux + z;
    z = yaux + xaux;

    printf("Se han realizado cambios: \n Valor anterior de X = %d / Valor actual de x = %d \n Valor anterior de Y = %d / Valor actual de y = %d\n Valor anterior de Z = %d / Valor actual de z = %d \n",xaux,x,yaux,y,zaux,z);

    //Postcondicion:
    assert(x == yaux);
    assert(y == yaux + xaux + zaux);
    assert(z == yaux + xaux);
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
    6
    Ingresar valor de la variable z
    10
    Se han realizado cambios: 
    Valor anterior de X = 3 / Valor actual de x = 6
    Valor anterior de Y = 6 / Valor actual de y = 19
    Valor anterior de Z = 10 / Valor actual de z = 9

    Ingresar valor de la variable x
    4
    Ingresar valor de la variable y
    10
    Ingresar valor de la variable z
    2
    Se han realizado cambios: 
    Valor anterior de X = 4 / Valor actual de x = 10
    Valor anterior de Y = 10 / Valor actual de y = 16
    Valor anterior de Z = 2 / Valor actual de z = 14
*/
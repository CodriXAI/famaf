//EJERCICIO 1B2:

/*
    Especificacion del programa:
    var x : NUM
    if x<0 -> -x 
    ■ x
    fi

    Especificacion del programa con pre y post condicion:
    var x : NUM
    var absoluto : BOOL
    {x = sizeof(Int)}
    if x<0 -> -x 
    ■ x
    fi
    {absoluto == x<0 ? -x : x}
*/
#include<stdio.h>
#include<assert.h>
int main(void){
    int x;
    int absoluto;
    printf("Ingrese un numero entero: \n");
    scanf("%d", &x);
    //Precondicion: X es un numero entero
    assert(sizeof(x) == sizeof(int));
    //Condicion con operador ternario para detectar valor absoluto
    absoluto = (x<0) ? -x : x;

    printf("El valor absoluto de su numero es: %d",absoluto);

    //Postcondicion : absoluto es el valor absoluto de x
    assert(absoluto == ((x<0) ? -x : x));

    return 0;
}
/*
    Ejemplos:
    Ingrese un numero entero: 
    -4
    El valor absoluto de su numero es: 4

    Ejemplos:
    Ingrese un numero entero: 
    18
    El valor absoluto de su numero es: 18
*/
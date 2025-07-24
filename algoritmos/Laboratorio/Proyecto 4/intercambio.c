//EJERCICIO 1B3:
#include <stdio.h>
#include <assert.h>
int main(void){
    //Definicion de variables x,y,z
    int x,y,z;
    
    printf("Ingresar valor x: \n");
    scanf("%d",&x);
    
    printf("Ingresar valor y: \n");
    scanf("%d",&y);
    
    //Guardo los valores iniciales antes del cambio en dos variables auxiliares:
    int x_original = x;
    int y_original = y;

    //Se realiza el intercambio con la variable auxiliar z:
    z = x;
    x = y;
    y = z;

    printf("Se intercambiaron variables, ahora x=%d  y=%d \n",x,y);

    //Precondicion: x e y son enteros
    assert(sizeof(x) == sizeof(int));
    assert(sizeof(y) == sizeof(int));

    //Postcondicion: Se intercambian las variables
    assert(x == y_original);
    assert(y == x_original);
    return 0;

    /*Esto es lo que sucede:
    
        x -> Z 
             |
          <- Y

        1: x -> Z
        2: Y <- x
        3: z -> y

        Finalmente: X:=Y , Y:=X , Z nada.
    */
}
/*
    EJEMPLOS:

    Ingresar valor x: 
    23
    Ingresar valor y: 
    10
    Se intercambiaron variables, ahora x=10  y=23 

    Ingresar valor x: 
    2
    Ingresar valor y: 
    2
    Se intercambiaron variables, ahora x=2  y=2
*/
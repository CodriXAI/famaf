#include <stdlib.h>
#include <stdio.h>
//Agrego libreria, faltó esto:
#include <assert.h>

void absolute(int x, int *y) {
    /*Modificaciones hechas con punteros:*/
    if(x >= 0){
        *y = x;
    }else{
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    // --- No se deben declarar variables nuevas ---
    a = -10;
    
    /*
        Modificación, tengo que acceder al contenido al 
        ser una variable de tipo puntero (si pongo solo res, 
        me devolvería una dirección de memoria)

        Por ende no habrá macheo de patrones
    */
    absolute(a,&res);
    /* supongamos que print() muestra el valor de una variable*/
    printf("%d",res);
    /* esta ultima asignación es analoga a ' return EXIT_SUCCESS; '*/
    
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

/*
    Para pensar:

    i) - ¿El parámetro int *y de absolute() es de tipo in, de tipo out o de tipo in/out?

    ii) - ¿Qué tipo de parámetros tiene disponibles  C para sus funciones?
    Parámetros in
    Parámetros out
    Parámetros in/out

    i) - Para mí, el parámetro int *y de absolute() es de tipo out, ya que solo la uso como escritura

    ii) - Tiene parametros del tipo in (cuando usamos un argumento para comparar en if, bucles etc)
          y out al momento de escribir o asignar valores variables (escribirlo)

*/

#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if(x >= 0){
        y = x;
    }else{
        y = -x;
    }
}

int main(void) {
    int a=0, res = 2; 
    a = -10;
    absolute(a,res);
    /* supongamos que print() muestra el valor de una variable*/
    printf("%d",res);
    /* esta ultima asignación es analoga a ' return EXIT_SUCCESS; '*/
    return EXIT_SUCCESS;
}

/* El ejercicio nos muestra que no devuelve lo esperado, lo esperado sería que devuelva 10, sin embargo, nos devuelve 0 */


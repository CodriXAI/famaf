//EJERCICIO 5:
#include <stdio.h>
struct div_t {
    int cociente;
    int resto;
};
struct div_t division(int x, int y){
    struct div_t resultado;
    resultado.cociente = (x/y);
    resultado.resto = (x%y);
    return resultado;
}
int main(void){
    int x,y;
    struct div_t resultado;
    printf("Ingresar valor de la variable x (Dividendo): \n");
    scanf("%d",&x);
    printf("Ingresar valor de la variable y (Divisor): \n");
    scanf("%d",&y);
    if(y==0){
        printf("Error: El divisor no puede ser 0");
    }else{
        resultado = division(x,y);
        printf("El cociente de la division es: %d \nEl resto de la division es: %d \n",resultado.cociente,resultado.resto);
    }
}
/*
    EJEMPLOS:
    
    Ingresar valor de la variable x (Dividendo): 
    10
    Ingresar valor de la variable y (Divisor): 
    2
    El cociente de la division es: 5 
    El resto de la division es: 0

    Ingresar valor de la variable x (Dividendo): 
    5
    Ingresar valor de la variable y (Divisor): 
    3
    El cociente de la division es: 1 
    El resto de la division es: 2
*/
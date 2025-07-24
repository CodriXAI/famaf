#include <stdio.h>

struct div_t {
    int cociente;
    int resto;
};

struct div_t division (int x, int y);

struct div_t division(int x, int y){
    struct div_t resultado;
    resultado.cociente = x / y;
    resultado.resto = x % y;

    return resultado;
}

int main(){
    int dividendo;
    int divisor;
    printf("Ingrese valor del dividendo: \n");
    scanf("%d",&dividendo);
    printf("Ingrese valor del divisor: \n");
    scanf("%d",&divisor);
    if(divisor == 0){
        printf("Error, no se puede dividir por 0 \n");
        return 1;
    }else{
        struct div_t resultado = division(dividendo,divisor);
        printf("El cociente es: %d y El resto es: %d \n",resultado.cociente,resultado.resto);
        return 0;
    }
}
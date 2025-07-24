#include <stdio.h>
#include <stdbool.h>

bool esPrimo(int x){
    int i = 2;
    while(x % i != 0 && x > 1){
        i = i+1;
    }

    return(i == x);
}
/*
int main(void){
    int x;
    printf("Ingrese un valor para x: \n");
    scanf("%d", &x);
    printf("El resultado es : %d \n", esPrimo(x));
    return 0;
}
*/
//Mejorado:
int main(void){
    int x;
    printf("Ingrese un valor para x: \n");
    scanf("%d", &x);
    if(esPrimo(x) != 0){
        printf("Es un número primo \n");
    }else{
        printf("NO es un número primo \n");
    }
}



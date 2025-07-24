//Después de testear este programa, lo que me devuelve es si el número que ingresamos es primo o no

#include <stdio.h>

int f(int x){
    int i = 2;
    while(x % i != 0 && x>1){
        i = i+1;
    }
    return (i == x);
}

int main(void){
    int x;
    printf("Ingrese un valor para x: \n");
    scanf("%d", &x);
    printf("El resultado es %d \n", f(x));
    return 0;
}
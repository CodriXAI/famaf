#include <stdio.h>
/*Defino prototipos de funciones*/
void imprimir_hola(void);
void imprimir_chau(void);

int main(void){
    imprimir_hola();
    imprimir_hola();
    imprimir_chau();
    imprimir_chau();
}

void imprimir_hola(void){
    printf("Hola ");
}

void imprimir_chau(void){
    printf("Chau ");
}

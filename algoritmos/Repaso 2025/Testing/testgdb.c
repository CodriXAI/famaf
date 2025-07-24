//Archivo de Testing para GNU gdb y gcc, compilador y debugger de C:
#include <stdio.h>

//Función para crear el mensaje que se imprime:
void mensaje(){
    printf("Hola mundo \n");
}

//main
int main(){
    int x = 5;
    mensaje();
    x = x * 2;
    printf("El valor de x es: %d\n",x);
    return 0;
}
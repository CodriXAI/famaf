#include <stdio.h>

//Declaración de la estructura:
struct alumno{
    int a;
    char nombre[20];
};

int main(void) {
    //Defino los valores de la misma:
    struct alumno aLumno = {
        10,
        "name"
    };
    //No es correcto poner aLumno.nombre = "name"
    //Imprimo ambos valores de la estructura
    printf("%d %s \n",aLumno.a,aLumno.nombre);

    
    //Modifico el valor del entero de la estructura:
    aLumno.a = 2;
    printf("%d \n",aLumno.a);
    return 0;
}





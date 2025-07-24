//EJERCICIO 4:
#include <stdio.h>
#include <stdbool.h>

bool es_vocal(char letra) {
    //Devuelve un booleano
    return (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u' || letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U' );
}

int main() {
    //Solicitud de datos
    char caracter;
    printf("Ingrese un caracter: ");
    scanf(" %c", &caracter);
    
    //Condicional para ver casos de vocales y consonantes
    if (es_vocal(caracter)) {
        printf("%c es una vocal.\n", caracter);
    } else {
        printf("%c no es una vocal.\n", caracter);
    }
    
    return 0;
}

/*
    EJEMPLOS:
    Ingrese un caracter: C
    C no es una vocal.

    Ingrese un caracter: i
    i es una vocal.
*/


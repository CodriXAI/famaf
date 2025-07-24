//EJERCICIO 11:
#include <stdio.h>

// Función para encontrar la longitud del tramo inicial más largo con elementos iguales
int prim_iguales(int tam, int a[]) {
    int longitud_actual = 1; // Inicialmente, se asume un tramo de longitud 1
    int longitud_maxima = 1; // Longitud máxima encontrada hasta ahora

    for (int i = 1; i < tam; i++) {
        if (a[i] == a[i - 1]) {
            longitud_actual++;
        } else {
            if (longitud_actual > longitud_maxima) {
                longitud_maxima = longitud_actual;
            }
            longitud_actual = 1; // Reiniciar la longitud actual
        }
    }

    if (longitud_actual > longitud_maxima) {
        longitud_maxima = longitud_actual;
    }

    return longitud_maxima;
}

int main() {
    const int tam = 5; // Tamaño del arreglo (puedes cambiarlo según tus necesidades)
    int a[tam];

    printf("Ingrese %d elementos del arreglo:\n", tam);
    for (int i = 0; i < tam; i++) {
        scanf("%d", &a[i]);
    }

    int longitud_tramo = prim_iguales(tam, a);

    printf("La longitud del tramo inicial más largo con elementos iguales es: %d\n", longitud_tramo);

    return 0;
}
/*
    EJEMPLOS:

    Ingrese 5 elementos del arreglo:
    4
    6
    7
    8
    8
    La longitud del tramo inicial más largo con elementos iguales es: 2

    Ingrese 5 elementos del arreglo:
    6
    6
    6
    8
    8
    La longitud del tramo inicial más largo con elementos iguales es: 3
*/

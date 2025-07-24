//EJERCICIO 10:
#include <stdio.h>
#include <limits.h>

int minimo_pares(int tam, int a[]) {
    int min_pares = INT_MAX; // Inicializamos con un valor máximo
    for (int i = 0; i < tam; i++) {
        if (a[i] % 2 == 0 && a[i] < min_pares) {
            min_pares = a[i];
        }
    }
    return min_pares;
}

int minimo_impares(int tam, int a[]) {
    int min_impares = INT_MAX; // Inicializamos con un valor máximo
    for (int i = 0; i < tam; i++) {
        if (a[i] % 2 != 0 && a[i] < min_impares) {
            min_impares = a[i];
        }
    }
    return min_impares;
}

int main() {
    int tam;
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &tam);

    int arreglo[tam];

    printf("Ingrese los elementos del arreglo:\n");
    for (int i = 0; i < tam; i++) {
        printf("a[%d]:",i);
        scanf("%d", &arreglo[i]);
    }

    int min_pares = minimo_pares(tam, arreglo);
    int min_impares = minimo_impares(tam, arreglo);

    printf("El resultado de minimo_pares(): %d\n", min_pares);
    printf("El resultado de minimo_impares(): %d\n", min_impares);

    // Calcular el mínimo general utilizando el resultado de ambas funciones
    int min_general = (min_pares < min_impares) ? min_pares : min_impares;
    printf("El elemento mínimo del arreglo ingresado: %d\n", min_general);

    return 0;

    /*  
        El problema con este programa es que si no hay en el array
        pares o impares, las funciones se rompen, por lo tanto retornan basura
    */
}

/*
    EJEMPLOS FUNCIONALES:
    Ingrese el tamaño del arreglo: 4
    Ingrese los elementos del arreglo:
    a[0]:2
    a[1]:1
    a[2]:6
    a[3]:7
    El resultado de minimo_pares(): 2
    El resultado de minimo_impares(): 1
    El elemento mínimo del arreglo ingresado: 1

    Ingrese el tamaño del arreglo: 6
    Ingrese los elementos del arreglo:
    a[0]:6
    a[1]:9
    a[2]:4
    a[3]:5
    a[4]:10
    a[5]:8
    El resultado de minimo_pares(): 4
    El resultado de minimo_impares(): 5
    El elemento mínimo del arreglo ingresado: 4
*/

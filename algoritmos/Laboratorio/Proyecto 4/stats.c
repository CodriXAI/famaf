//EJERCICIO 13:
#include <stdio.h>

// Definición de la estructura datos_t
struct datos_t {
    float maximo;
    float minimo;
    float promedio;
};

// Función para calcular el mínimo, máximo y promedio de un arreglo de números flotantes
struct datos_t stats(int tam, float a[]) {
    struct datos_t resultado;
    
    if (tam == 0) {
        resultado.maximo = 0.0;
        resultado.minimo = 0.0;
        resultado.promedio = 0.0;
        return resultado;
    }

    resultado.maximo = a[0];
    resultado.minimo = a[0];
    resultado.promedio = a[0];

    for (int i = 1; i < tam; i++) {
        if (a[i] > resultado.maximo) {
            resultado.maximo = a[i];
        }
        if (a[i] < resultado.minimo) {
            resultado.minimo = a[i];
        }
        resultado.promedio += a[i];
    }

    resultado.promedio /= tam;

    return resultado;
}

int main() {
    int tam;
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &tam);

    if (tam <= 0) {
        printf("El tamaño del arreglo debe ser mayor que cero.\n");
        return 1;
    }

    float a[tam];
    printf("Ingrese los elementos del arreglo:\n");

    for (int i = 0; i < tam; i++) {
        scanf("%f", &a[i]);
    }

    struct datos_t resultado = stats(tam, a);

    printf("Máximo: %.2f\nMínimo: %.2f\nPromedio: %.2f\n", resultado.maximo, resultado.minimo, resultado.promedio);

    return 0;
}
/*
    EJEMPLOS:
    Ingrese el tamaño del arreglo: 2
    Ingrese los elementos del arreglo:
    1.4
    1.8
    Máximo: 1.80
    Mínimo: 1.40
    Promedio: 1.60

    Ingrese el tamaño del arreglo: 4
    Ingrese los elementos del arreglo:
    1.4
    1.8
    2.1
    4.5
    Máximo: 4.50
    Mínimo: 1.40
    Promedio: 2.45
*/
//EJERCICIO 15:
#include <stdio.h>

// Función para verificar si un número es primo
int es_primo(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Función para encontrar el n-ésimo número primo
int nesimo_primo(int N) {
    int primo = 2; // El primer número primo es 2
    int contador = 1;

    while (contador < N) {
        primo++;
        if (es_primo(primo)) {
            contador++;
        }
    }

    return primo;
}

int main() {
    int n;
    do {
        printf("Ingrese un número entero no negativo: ");
        scanf("%d", &n);
        if (n < 0) {
            printf("Error: El número no debe ser negativo. Intente de nuevo.\n");
        }
    } while (n < 0);

    int resultado = nesimo_primo(n);
    printf("El %d-ésimo número primo es %d\n", n, resultado);

    return 0;
}
/*
    EJEMPLOS:
    
    Ingrese un número entero no negativo: -2
    Error: El número debe ser no negativo. Intente de nuevo.

    Ingrese un número entero no negativo: 3
    El 3-ésimo número primo es 5

    Ingrese un número entero no negativo: 1
    El 3-ésimo número primo es 2
*/

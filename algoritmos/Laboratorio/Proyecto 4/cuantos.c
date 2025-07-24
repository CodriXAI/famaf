//EJERCICIO 12:
#include <stdio.h>

// Definición de la estructura comp_t
struct comp_t {
    int menores;
    int iguales;
    int mayores;
};

// Función para contar elementos menores, iguales y mayores que elem en el arreglo a
struct comp_t cuantos(int tam, int a[], int elem) {
    struct comp_t resultado = {0, 0, 0}; // Inicializa a 0
    
    for (int i = 0; i < tam; i++) {
        if (a[i] < elem) {
            resultado.menores++;
        } else if (a[i] == elem) {
            resultado.iguales++;
        } else {
            resultado.mayores++;
        }
    }
    
    return resultado;
}

int main() {
    int tam = 5; // Tamaño del arreglo
    int a[] = {3, 2, 5, 2, 7}; // Arreglo de ejemplo
    int elem = 4; // Número a comparar

    // Llama a la función cuantos y almacena el resultado en una estructura comp_t
    struct comp_t resultado = cuantos(tam, a, elem);

    // Imprime los resultados
    printf("Menores: %d\nIguales: %d\nMayores: %d\n", resultado.menores, resultado.iguales, resultado.mayores);

    return 0;
}
/*
    EJEMPLO DE COMPILACION:

    int tam = 5 = Tamaño del arreglo
    int a[] = {3, 2, 5, 2, 7} = Arreglo de ejemplo
    int elem = 4 =  Número a comparar

    Menores: 3
    Iguales: 0
    Mayores: 2

    OTRO EJEMPLO:
    int tam = 2 = Tamaño del arreglo
    int a[] = {2, 10} = Arreglo de ejemplo
    int elem = 3 =  Número a comparar

    Menores: 1
    Iguales: 0
    Mayores: 1
*/
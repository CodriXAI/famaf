//EJERCICIO 14:
#include <stdio.h>
#include <stdbool.h>

typedef char clave_t;
typedef int valor_t;

struct asoc {
    clave_t clave;
    valor_t valor;
};

bool asoc_existe(int tam, struct asoc a[], clave_t c) {
    for (int i = 0; i < tam; i++) {
        if (a[i].clave == c) {
            return true;
        }
    }
    return false;
}

int main() {
    int tam; // Tamaño del arreglo de asociaciones
    printf("Ingrese el tamaño del arreglo de asociaciones: \n");
    scanf("%d", &tam);

    struct asoc a[tam]; // Declarar el arreglo de asociaciones

    // Pedir al usuario que ingrese los datos del arreglo de asociaciones
    for (int i = 0; i < tam; i++) {
        printf("Ingrese la clave y el valor para el elemento %d:\n", i + 1);
        scanf("%c %d", &a[i].clave, &a[i].valor);
    }

    clave_t clave_buscar;
    printf("Ingrese la clave que desea buscar: ");
    scanf("%c", &clave_buscar);

    // Utilizar la función asoc_existe para verificar si la clave existe
    bool existe = asoc_existe(tam, a, clave_buscar);

    if (existe) {
        printf("La clave '%c' existe en el arreglo de asociaciones.\n", clave_buscar);
    } 
    else {
        printf("La clave '%c' no existe en el arreglo de asociaciones.\n", clave_buscar);
    }

    return 0;
}
/*
    EJEMPLOS:
    Ingrese el tamaño del arreglo de asociaciones: 
    3
    Ingrese la clave y el valor para el elemento 1:
    d 3
    Ingrese la clave y el valor para el elemento 2:
    e 10
    Ingrese la clave y el valor para el elemento 3:
    w 1
    Ingrese la clave que desea buscar: e
    La clave 'e' existe en el arreglo de asociaciones


    Ingrese el tamaño del arreglo de asociaciones: 
    2
    Ingrese la clave y el valor para el elemento 1:
    v 14
    Ingrese la clave y el valor para el elemento 2:
    g 120
    Ingrese la clave que desea buscar: f
    La clave 'f' no existe en el arreglo de asociaciones
*/
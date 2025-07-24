//EJERCICIO 7:
#include <stdio.h>
//Prototipo de la funcion:
int sumatoria(int tam, int a[]);

int main() {
    //Aca asigno el valor predefinido de tam, que se va a compilar 
    int tam = 5; 
    int a[tam];

    printf("Ingresar %d elementos para el array 'a':\n", tam);
    
    //Bucle for para realizar la suma
    for (int i = 0; i < tam; i++) {
        printf("a[%d]: ", i);
        scanf("%d", &a[i]);
    }

    //Variable para almacenar la suma
    int sum = sumatoria(tam, a);
    printf("La suma de los elementos es: %d\n", sum);
    return 0;
}

// Funcion que suma los elementos
int sumatoria(int tam, int a[]) {
    int res = 0;
    for (int i = 0; i < tam; i++) {
        res += a[i];
    }
    return res;
}

/*
    EJEMPLOS:
    Ingresar 5 elementos para el array 'a':
    a[0]: 2
    a[1]: 4
    a[2]: 6
    a[3]: 8
    a[4]: 10
    La suma de los elementos es: 30

    Ingresar 5 elementos para el array 'a':
    a[0]: 2
    a[1]: 1
    a[2]: 4
    a[3]: 8
    a[4]: 6
    La suma de los elementos es: 21
*/

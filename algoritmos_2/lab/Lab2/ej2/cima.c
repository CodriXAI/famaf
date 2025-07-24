#include <stdio.h>
#include <stdbool.h>
#include "cima.h"

/**
 * @brief Indica si el arreglo tiene cima.
 *
 * Un arreglo tiene cima si existe una posición k tal que el arreglo es
 * estrictamente creciente hasta la posición k y estrictamente decreciente
 * desde la posición k.
 *
 * @param a Arreglo.
 * @param length Largo del arreglo.
 */
bool tiene_cima(int a[], int length) {
    int i = 0;
    bool res = true;
    if(i != length-1){
        while(a[i] < a[i+1] && i < length-1){
            i++;
        }
        while(a[i] > a[i+1] && i < length-1){
            i++;
        }
    }
    if(i!= length-1){
        res = false;
    }
    return res;
}

/**
 * @brief Dado un arreglo que tiene cima, devuelve la posición de la cima.
 *
 * Un arreglo tiene cima si existe una posición k tal que el arreglo es
 * estrictamente creciente hasta la posición k y estrictamente decreciente
 * desde la posición k.
 * La cima es el elemento que se encuentra en la posición k.
 * PRECONDICION: tiene_cima(a, length)
 *
 * @param a Arreglo.
 * @param length Largo del arreglo.
 */

/*FUNCIÓN AUXILIAR PARA MOSTRAR EL ARRAY:*/
void array_dump(int a[] , int lenght){
    for(int i = 0; i<lenght;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}


int cima(int a[], int length) {
    //Versión simplificada del teórico:
    
    int k = 0;
    /*
    printf("k = %d\n",k);
    */
    
    while(k<length && a[k] < a[k+1]){
        /*
        array_dump(a,length);
        */
        
        k = k+1;
        /*
        printf("k = %d\n",k);
        */
    }
    return k;
}

#include <stdio.h>
#include <stdbool.h>
#include "cima_log.h"

/**
 * @brief Dado un arreglo que tiene cima, devuelve la posición de la cima
 * usando la estrategia divide y venceras.
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

int cima_log_rec(int a[], int lft, int rgt){
    int length = rgt+1;
    int mid;
    bool cima;
    int res;
    mid = (lft+rgt) / 2;
    printf("mid = %d \n",mid);
    cima = false;

    if(length == 1){
        res = lft;
        cima = true;
    }else if(length == 2){
        if(a[0] < a[1]){
            res = 1;
        }else{
            res = 0;
        }
        cima = true;
    }else{
        while(cima == false){
            if(a[mid-1] < a[mid] && a[mid]>a[mid+1]){
                res = mid;
                cima = true;
            }else if(a[mid-1]> a[mid] && a[mid] > a[mid+1]){
                res = cima_log_rec(a,lft,mid-1);
            }else{
                res = cima_log_rec(a,mid+1,rgt);
            }
        }
    }
    return res;
}
int cima_log(int a[], int length) {
    int lft = 0;
    int rgt = length-1;
    return cima_log_rec(a,lft,rgt);
}

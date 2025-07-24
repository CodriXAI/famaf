#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
    /* PRECONDITION: 
       0 <= izq < der < length of the array

     Permutes elements of a[izq..der] and returns pivot such that:
     - izq <= pivot <= der
     - elements in a[izq,pivot) all 'go_before' (according to function goes_before) a[pivot]
     - a[pivot] 'goes_before' all the elements in a(pivot,der]
    */

    unsigned int ppiv = izq;
    unsigned int i = izq+1;
    unsigned int j = der;

    while(i<=j){
        if(goes_before(a[i],a[ppiv])){
            i = i+1;
        }else if(goes_before(a[ppiv],a[j])){
            j = j-1;
        }else{
            swap(a,i,j);
            i = i+1;
            j = j-1;
        }
    }
    swap(a,ppiv,j);
    ppiv = j;
    return ppiv;

}

/*
Copiado del ejercicio anterior:
Agregué como argumento el length de forma manual
*/

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der,unsigned int length) {
    unsigned int ppiv = izq;
    if (izq < der) {
        
        printf("Antes del partition: \n");
        
        array_dump(a,length);
        
        printf("izq=%u, der=%u, pivot= %u \n \n",izq,der,ppiv);
        
        ppiv = partition(a,izq,der);

        printf("Después del partition: \n");

        array_dump(a,length);
        
        printf("izq=%u, der=%u, pivot= %u \n \n",izq,der,ppiv);
        
        quick_sort_rec(a,izq,(ppiv == 0u ? 0u : ppiv-1u),length);

        quick_sort_rec(a,ppiv+1u,der,length);
    }
}

void quick_sort(int a[], unsigned int length) {
    
    quick_sort_rec(a, 0, (length == 0u) ? 0u : length - 1u,length);
    
}


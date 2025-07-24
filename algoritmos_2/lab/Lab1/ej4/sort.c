#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length) {
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; ++j) {
        if (!goes_before(a[min_pos],a[j])) {
            min_pos = j;
        }
    }
    return (min_pos);
}

/*--------------------ALGORITMOS DE ORDENACIÓN --------------------------*/

void selection_sort(int a[], unsigned int length) {
    for (unsigned int i = 0; i < length; ++i) {
        unsigned int min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}

static void insert(int a[], unsigned int i, unsigned int length){
    unsigned int j = i;
    //Forzado a iniciar en j = 1 adaptado al lenguaje en C:
    while(j>0 && goes_before(a[j],a[j-1]) && j<length){
        array_dump(a, length);
        swap(a,j-1,j);
        j = j-1;
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1; i < length; ++i) {
        assert(array_is_sorted(a,i));
        insert(a, i, length);
    }
}


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

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
    /*
        Creando la recursión del quick-sort usando la definición del teórico:
        
        - La condición radica en que izq debe ser menor a der para que tenga sentido
        - Luego, se tiene que obtener un pivot que resultará de la función partition
        - Una vez obtenido el pivot de partition tendrémos que hacer los dos quick_sort_rec 
    */

    if (izq < der) {
        unsigned int pivot = partition(a,izq,der);

        quick_sort_rec(a,izq,(pivot == 0u ? 0u : pivot-1u));

        quick_sort_rec(a,pivot+1u,der);
    }
}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0u) ? 0u : length - 1u);
}

/*----------------------------------------------------------------------*/
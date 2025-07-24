#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void insert(int a[], unsigned int i, unsigned int length) {
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
        /*Consultar si esto está bien hecho:*/
        assert(array_is_sorted(a,i));
        insert(a, i, length);
    }
}



#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    int i = izq+1; 
    int j = der; 
    unsigned int ppiv = izq; 
    while (i <= j) {
        if (goes_before(a[i], a[ppiv])) i = i+1; 
        else if (goes_before(a[ppiv], a[j])) j = j-1;
        else if (goes_before(a[ppiv], a[i]) && goes_before(a[j],a[ppiv])) {
            swap(a, i, j);
            i = i+1;
            j = j-1;
        }
    }
    swap(a, ppiv, j);
    ppiv = j; 

    return ppiv;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = izq;
    if (der > izq) {
        ppiv = partition (a, izq, der);
        quick_sort_rec(a, izq, ((ppiv == 0u) ? 0u : ppiv - 1u));
        quick_sort_rec(a, ppiv+1u, der);
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}



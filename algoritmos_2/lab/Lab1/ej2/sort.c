#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


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

        /*quick_sort_rec(a,pivot>der ? der : pivot+1u,der); No es necesario, puesto que el problema estaba del extremo 'izq' */
        quick_sort_rec(a,pivot+1u,der);
    }

}

void quick_sort(int a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0u) ? 0u : length - 1u);
}


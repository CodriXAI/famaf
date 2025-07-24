#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "data.h"

void print_data(data_t* d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d->name, d->age, d->height);
}

int main(void) {
    //Declaro un puntero a una estructura data_t:
    data_t* messi = malloc(sizeof(data_t));
    
    //Con ayuda de strcpy de string.h, copio en el campo name del puntero messi, la string:
    strcpy(messi->name, "Leo Messi");
    //Lo mismo con los otros datos de forma normal:
    messi->age = 36;
    messi->height = 169;

    //Imprimo la información del puntero
    print_data(messi);
    
    //Libero la memoria porque no la utilizo más:
    free(messi);
    return EXIT_SUCCESS;
}


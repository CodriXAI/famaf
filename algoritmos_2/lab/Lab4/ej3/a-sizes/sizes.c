#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n\n", sizeof(messi.name), sizeof(messi.age), sizeof(messi.height), sizeof(messi));

    //Impresión de las direcciones de memoria de cada campo de la struct messi:

    //Primero con direcciones:
    char* p = NULL;
    unsigned int* q = NULL;
    p = messi.name;
    q = &messi.age;
    printf("Direcciones de Memoria:\n\n");
    printf("Dirección de Memoria de messi.name es:%p\n\n", (void *) p);
    printf("Dirección de Memoria de messi.age es:%p\n\n", (void *) q);
    q = &messi.height;
    printf("Dirección de Memoria de messi.height es:%p\n\n", (void *) q);

    //Segundo con indices:
    q = &messi.age;
    printf("Direcciones de Memoria (ÍNDICES):\n\n");
    printf("Dirección de Memoria de messi.name es:%lu\n\n", (uintptr_t) p);
    printf("Dirección de Memoria de messi.age es:%lu\n\n", (uintptr_t) q);
    q = &messi.height;
    printf("Dirección de Memoria de messi.height es:%lu\n\n", (uintptr_t) q);
    return EXIT_SUCCESS;
}

/*
    Ejercicio 1: 
        El tamaño que aparece en consola es del estilo:
        name-size: 30 bytes - En este caso con "Leo Messi"
        age-size: 4 bytes
        height-size: 4 bytes
        data_t-size: 40 bytes
        
        Las conclusiones es que la suma de todos los componentes suman 38 bytes, pero el total de la estructura
        agrega 2 bytes mas, con una suma de 40 bytes en total. (Hipótesis: ¿Puede ser porque esos 2 bytes puedan significar
        que la misma estructura por si sola ocupa 2 bytes en almacenamiento?)

        Segunda conclusión: 
        Cambié el nombre por Leo en vez de Leo Messi e igualmente almacenan 30 bytes, por ende no depende exactamente del nombre

*/

/*
    Ejercicio 2 - Conclusión: 
    Al compilar mostrando las posiciones en memoria de cada campo de la struct Messi nos topamos con lo siguiente:
    
    >>>
    NOMBRE: Leo Messi
    EDAD  : 36 años
    ALTURA: 169 cm

    name-size  : 30 bytes
    age-size   : 4 bytes
    height-size: 4 bytes
    data_t-size: 40 bytes

    Direcciones de Memoria:

    Dirección de Memoria de messi.name es:0x7ffd37e85030

    Dirección de Memoria de messi.age es:0x7ffd37e85050

    Dirección de Memoria de messi.height es:0x7ffd37e85054

    Direcciones de Memoria (ÍNDICES):

    Dirección de Memoria de messi.name es:140725541425200

    Dirección de Memoria de messi.age es:140725541425232

    Dirección de Memoria de messi.height es:140725541425236
    <<<
    Si nos ponemos a fijar, las direcciones no son simetricas, lo que tiene sentido por el tamaño que ocupan en bytes
    Pero no solo eso sino que además podríamos contar esa antisimetría por el padding (basura) entre medio de los campos
    de la struct
*/
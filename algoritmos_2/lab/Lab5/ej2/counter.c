#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"

#include <assert.h>

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    
    counter c = malloc(sizeof(struct _counter)); //Reservo memoria para el contador
    
    //Verifico que haya alojado correctamente la memoria:
    if(c != NULL){
        c->count = 0; //Inicializo el valor del contador
    }
   
    return c; //Lo devuelvo
}

void counter_inc(counter c) {
    c->count++;
}

bool counter_is_init(counter c) {
    return c->count == 0;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));

    c->count--;

}

counter counter_copy(counter c) {
    counter c_copy = malloc(sizeof(struct _counter)); //Creo nuevo contador y le alojo memoria
    c_copy->count = c->count; //Copio los valores del contador original

    return c_copy; //Devuelvo la copia
}

void counter_destroy(counter c) {
    free(c);
}

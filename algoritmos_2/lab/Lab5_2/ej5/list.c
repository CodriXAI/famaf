#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list.h"

#define MAX_LENGTH 100

struct _list {
    elem elems[MAX_LENGTH];
    int size;
};

//------------------------------CONSTRUCTORS------------------------------------------------
/**
 * @brief Creates a new empty list.
 */
list empty(){
    list new_list = malloc(sizeof(struct _list)); //Como debo hacerlo si o si con arreglos, almaceno memoria
    if(new_list != NULL){
        new_list->size = 0; //Inicializo con un tamaño en 0
    }
    return new_list; //Devuelvo esa lista con el arreglo vacío
}
/**
 * @brief Adds element `e` to the left of list `l`.
 */
list addl(elem e, list l){
    assert(l->size < MAX_LENGTH); //Verifico si l->size no llegó ya al límite (precondicion)
    for(int i = l->size-1;i>=0; i--){ //Recorro cada elemento según nuestro size
            l->elems[i+1] = l->elems[i]; //Corro todo a la derecha
    }
    l->elems[0] = e; //Agrego el elemento al inicio
    l->size++; //Aumento el size si se puede    
    return l; //Devuelvo la lista modificada
}
//------------------------------------OPERATIONS----------------------------------------------
/**
 * @brief Returns whether the list `l` is empty.
 */
bool is_empty(list l){
    return l->size == 0;
}
/**
 * @brief Returns first element of list `l`.
 *
 * PRECONDITION: !is_empty(l)
 */
elem head(list l){
    assert(!is_empty(l)); //Verifico precondición
    return l->elems[0]; //Agarro el primer elemento del arreglo
}
/**
 * @brief Removes in-place the first element of list `l`.
 *
 * PRECONDITION: !is_empty(l)
 */
list tail(list l){
    assert(!is_empty(l)); //Verifico precondición
    for(int i = 1; i<l->size;i++){ //Voy recorriendo de la segunda posición hasta la última
        l->elems[i-1] = l->elems[i]; //Sobreescribo y muevo a la izq un lugar todos los elementos
    }
    l->size = l->size-1;
    return l;
}
/**
 * @brief  Adds in-place element `e` to the right of list `l`.
 */
list addr(list l, elem e){
    assert(l->size < MAX_LENGTH); //Verifico Precondición
    l->elems[l->size] = e; //Agrego el elemento e a la derecha
    l->size++; //Aumento el tamaño size en 1
    
    return l;
}
/**
 * @brief Return the amount of elements of list `l`.
 */
int length(list l){
    return l->size; //Devuelvo el tamaño de la lista
}
/**
 * @brief Adds to the end of `l` all elements of `l0`.
 * PRECONDITION: l.size+l0.size <= MAX_LENGTH
 */
list concat(list l, list l0){
    assert(l->size+l0->size <= MAX_LENGTH); //Verifico Precondición
    for(int i = l->size; i<l->size+l0->size; i++){ //Recorro desde la primer posición a agregar hasta el tamaño total
        l->elems[l->size+i] = l0->elems[i]; //Voy copiando los elementos de l0 agregandolos a continuación de l
    }
    l->size = l->size + l0->size; //Actualizo el tamaño de la lista

    return l; //Devuelvo la concatenación
}
/**
 * @brief Return the `n`-th element of `l`.
 *
 * PRECONDITION: n < length(l)
 */
elem index(list l, int n){
    assert(n < length(l)); //Verifico Precondición
    return l->elems[n];
}
/**
 * @brief Takes the first `n` elements of `l` in-place, removing the rest.
 *  PRECONDITION: length(l) > n
 */
list take(list l, int n){
    assert(length(l) >= n); //Verifico precondición
    l->size = n; //Modifico el tamaño
    return l; //Devuelvo la lista modificada
}
/**
 * @brief Removes the first `n` elements of `l` in-place.
*  PRECONDITION: length(l) > n
 */
list drop(list l, int n){
    assert(length(l) > n); //Verifico precondición
    //Dos variables indices, una me da la pos inicial a eliminar, otra la posicion a mover
    int i = 0;
    int j = n;
    //Mientras no llegue al final, voy moviendo
    while(j < l->size){
        l->elems[i] = l->elems[j];
        i++;
        j++;
    }
    l->size = l->size - n;

    return l;
}
/**
 * @brief  Makes a copy of list `l`. Allocates new memory.
 */
list copy_list(list l){
    list result = malloc(sizeof(struct _list)); //Genero una nueva lista y reservo memoria
    if(result != NULL){
        for(int i = 0; i<l->size; i++){ //Caso contrario voy recorriendo l
            result->elems[i] = l->elems[i]; //Y voy copiando la lista l en result
        }
        result->size = l->size; //Le paso el size    
    }
    return result;  //Devuelvo la copia
}
/**
 * @brief Frees memory for `l`.
 */
void destroy_list(list l){
    free(l);
}


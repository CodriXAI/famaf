#include <stdio.h>
#include "pair.h"
#include <assert.h>
#include <stdlib.h> 


/*
 * DESC: Creates a new pair with components (x, y)
 *
 * p = pair_new(x, y);
 *
 * POS: {p --> (x, y)}
 */
pair_t pair_new(int x, int y){
    pair_t p = malloc(sizeof(struct s_pair_t)); //Reservo memoria suficiente para la nueva struct
    
    //Verifico si se ha alojado memoria:
    if (p != NULL){
        p->fst = x; //Asigno el primer elemento 
        p->snd = y; //Asigno el segundo elemento
    }
    
    return p; //Devuelvo dicho puntero
}


/*
 * DESC: Returns the first component of p
 *
 * PRE: {p --> (x, y)}
 *
 *  fst = pair_first(p);
 *
 * POS: {fst == x}
 */
int pair_first(pair_t p){
    int x = p->fst; //Guardo el primer valor de la struct p en X
    return x; //Lo devuelvo
    assert(x == p->fst); //Verifico POSCONDICIÓN
}


/*
 * DESC: Returns the second component of p
 *
 * PRE: {p --> (x, y)}
 *
 *  snd = pair_second(p);
 *
 * POS: {snd == y}
 */
int pair_second(pair_t p){
    int y = p->snd; //Guardo el segundo valor de la struct p en Y
    return y; // Lo devuelvo
    assert(y == p->snd); //Verifico POSCONDICION
}


/*
 * DESC: Return a NEW pair with the components of p reversed
 *
 * PRE: {p --> (x, y)}
 *
 *  q = pair_swapped(p)
 *
 * POS: {pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)}
 *
 */
pair_t pair_swapped(pair_t p){
    //Declaro una variable auxiliar para reservar memoria:
    pair_t q = malloc(sizeof(struct s_pair_t));
    //Intercambio los valores de p en q:
    q->fst = p->snd; 
    q->snd = p->fst;

    return q; //Devuelvo la modificada

    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)); //Verifico POSCONDICIÓN
}


/*
 * DESC: Free memory if its necesary
 *
 */
pair_t pair_destroy(pair_t p){
    free(p); //Libero la memoria de p
    return NULL; //Lo devuelvo (vacío)
}
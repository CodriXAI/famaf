#include <stdio.h>
#include "pair.h"
#include <assert.h>

/*
 * DESC: Creates a new pair with components (x, y)
 *
 * p = pair_new(x, y);
 *
 * POS: {p --> (x, y)}
 */
pair_t pair_new(int x, int y){
    pair_t p;
    p.fst = x;
    p.snd = y;

    //POS: Debe estar inicializado:
    assert(p.fst == x && p.snd == y);

    return p;
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
    int x;
    x = p.fst;
    assert(p.fst == x);
    return x;
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
    int y;
    y = p.snd;
    assert(p.snd == y);
    return y;
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
    int x,y;
    x = p.fst;
    y = p.snd;
    
    assert(p.fst == x && p.snd == y);

    p.fst = y;
    p.snd = x;

    assert((p.fst == y) && (p.snd == x));

    return p;
}
/*
 * DESC: Free memory if its necesary
 *
 */
pair_t pair_destroy(pair_t p){
    return p;
}
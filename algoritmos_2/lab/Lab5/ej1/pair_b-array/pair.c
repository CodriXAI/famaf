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
    p.values[0] = x;
    p.values[1] = y;

    assert((p.values[0] == x) && (p.values[1] == y));

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
    x = p.values[0];

    assert(x == p.values[0]);

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
    y = p.values[1];

    assert(y == p.values[1]);

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
    x = p.values[0];
    y = p.values[1];

    assert(x == p.values[0] && y == p.values[1]);

    p.values[0] =  y;
    p.values[1] = x;

    assert(x == p.values[1] && y == p.values[0]);

    return p;
}

pair_t pair_destroy(pair_t p){
    return p;
}

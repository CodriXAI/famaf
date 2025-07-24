#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node node;
/* Definimos el tipo nodo que serán los elementos de una lista*/

typedef node* list;
/* Definimos el tipo lista a utilizar en las siguientes funciones */

typedef int list_elem;
/* Simular un tipo de "polimorfismo", en realidad serán int */

//-----------------------CONSTRUCTORS------------------------------

list empty(void);
/* Crea una lista vacía */

list addl(list_elem e, list l);
/* Agrega un elemento e al inicio de la lista l */

//------------------------OPERATIONS-------------------------------

bool is_empty(list l);
/* Determina si una lista es vacía */

list_elem head(list l);
/*
    Devuelve el primer elemento de la lista l
    PRE: !is_empty(l)
*/

list tail(list l);
/*
    Elimina el primer elemento de la lista l
    PRE: !is_empty(l)
*/

list addr(list_elem e, list l);
/* Agrega el elemento e al final de la lista l */

unsigned int length(list l);
/* Calcula el largo de la lista l */

list concat(list l1, list l2);
/* Agrega al final de l1 todos los elementos de l2 */

list_elem index(list l, unsigned int n);
/*
    Devuelve el n-ésimo elemento de la lista l
    PRE: length(l) > n
*/

list take(list l, unsigned int n);
/* Deja en l solo los primeros n elementos, eliminando el resto*/

list drop(list l, int n);
/* Elimina los primeros n elementos de la lista l, dejando el resto*/

//------------------------COPY & DESTROY----------------------------

list copy_list(list l);
/* Copia la lista l en otra completamente nueva */

list destroy_list(list l);
/* Libera memoria en caso de ser necesario */
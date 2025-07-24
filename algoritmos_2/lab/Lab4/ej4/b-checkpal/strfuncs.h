#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*NO PODEMOS UTILIZAR LA LIBRERIA STRING.H*/

/*Calcula cantidad de una cadena apuntada por str, la función:*/
size_t string_length(const char *str);

/*Devuelve una nueva cadena en memoria dinámica que se obtiene tomando los carácteres de str y que son distintos a C*/
char *string_filter(const char *str, char c);

/*
    Indica si la cadena apuntada por str es simétrica en cuanto que el primer caracter coincide con el ultimo
    el segundo con el penúltimo y así.
    Ej: aba, abba, emme, etc
*/
bool string_is_symmetric(const char *str);
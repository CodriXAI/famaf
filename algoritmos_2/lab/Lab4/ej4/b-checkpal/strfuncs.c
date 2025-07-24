#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "strfuncs.h"

/*NO PODEMOS UTILIZAR LA LIBRERIA STRING.H*/

/*Calcula cantidad de una cadena apuntada por str, la función:*/
size_t string_length(const char *str){
    size_t largo = 0;
    while(str[largo]!= '\0'){
        largo++;
    }
    return largo;
}

/*Devuelve una nueva cadena en memoria dinámica que se obtiene tomando los carácteres de str y que son distintos a C*/
char *string_filter(const char *str, char c){
    /*
        Declaro dos punteros y una variable contador:
        - El puntero result es el que apuntara a la nueva cadena y el que devolveremos
        - El puntero selector es el que toma la string para ir recorriendola
        - La variable contador me indica la cantidad de caracteres distintos de C
    */
    char *result = NULL;
    const char *selector = str;
    int count = 0;

    /*
        Me fijo primeramente que str no sea vacía, y en caso que si sea no hace nada y devuelve NULL
        Luego me fijo en el bucle que mientras no haya llegado al final, voy viendo en cada posición de la cadena
        el caracter que sea distinto a c, y a ese lo agrego en el contador (esto lo hago porque debo ver)
        cuanta memoria debo reservar en heap
    */
    if(str != NULL){
        while(*selector != '\0'){
            if(*selector != c){
                count++;
            }
            selector++;
        }
        /* 
            Reservo la cantidad de memoria correspondiente por char (+1 por el \0)
            Además guardo la referencia de result en un arreglo temporal, que este hará el trabajo
            de reservar memoria, apuntamos el resultado al inicio y luego el temp irá recorriendo 
        */
        char *temp = malloc((count+1) * sizeof(char));
        result = temp;
        
        //Ahora voy copiando la nueva lista según que los caracteres no sean C:
        /*
            Con selector vuelvo al inicio de la str original a filtrar
            Y con result voy copiando los elementos que no sean c
            Luego con ambos voy avanzando
        */
        selector = str;
        while(*selector != '\0'){
            if(*selector != c){
                *temp = *selector;
                temp++;
            }
            selector++;
        }

        *temp = '\0';
    }
    return result;
}

/*
    Indica si la cadena apuntada por str es simétrica en cuanto que el primer caracter coincide con el ultimo
    el segundo con el penúltimo y así.
    Ej: aba, abba, emme, etc
*/
bool string_is_symmetric(const char *str){
    const char *lft = str;
    const char *rgt = str;
    bool is_sym = true;

    while(*rgt != '\0'){
        rgt++;
    }
    rgt--;
    
    while(lft < rgt){
        if(*lft == *rgt){
            lft++;
            rgt--;
        }else{
            is_sym = false;
            lft++;
            rgt--;
        }
    }

    return is_sym;
}
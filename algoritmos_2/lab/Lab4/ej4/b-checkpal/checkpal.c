#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 20

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;

    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);
    
    //Omitimos el scanf
    /*scanf("%s", user_input);*/
    fgets(user_input, 20, stdin);
    /*Solución al problema \n*/
    int largo = string_length(user_input);
    if(largo > 0 && user_input[largo-1] == '\n'){
        user_input[largo-1] = '\0';
    }

    filtered = string_filter(user_input, ignore_chars[0]);

    /*
        SOLUCIÓN A LOS MEMORIES LEAK:
        Basicamente en este bucle estabamos todo el tiempo llamando a string_filter 
        lo cual generaba que todo el tiempo se realicen mallocs sin liberarse lo que acumulaba
        memoria innecesariamente. Para solucionar eso primero nos aseguramos que antes de que
        se filtre el arreglo dado por el usuario, utilizamos el user_input para recien filtrarlo
        y en las proximas iteraciones, utilizamos ese filtered con un puntero temporal 
        LO IMPORTANTE: En cada iteración tenemos que ir liberando filtered, si no queremos que
        se acumule memoria innecesariamente
    */
    for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        if(filtered == NULL){
            filtered = string_filter(user_input, ignore_chars[i]);
        }else{
            char *temp = string_filter(filtered, ignore_chars[i]);
            free(filtered);
            filtered = temp;
        }
        
    }
    
    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");
    free(filtered);
    return EXIT_SUCCESS;
}
/* 
    Conclusiones - Inconvenientes con scanf:
    - Si entra una cadena mas larga que 20, se jode todo
    - Si ingreso una cadena vacia también se jode todo / Por el ignore chars
    - Hay algunos pal que no son palindromos como pal4 y pal5
    - Ignora los espacios justamente por ignore chars
*/


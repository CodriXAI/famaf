#include <stdio.h>
#include <stdlib.h>

#include "fixstring.h"
// #include "fixstring.c" no usar este en caso de compilar como la filmina lo diga

#define N_WORDS 6

int main(void) {
    fixstring words[N_WORDS]={"hola", "mundo", "auto","automovil","aeiou","aieou"};
    fixstring words1[N_WORDS]={"hola", "mundo1", "auto","automovil1","aeiou","aieou"};

    printf("Probando fstring_length()\n"
           "-------------------------\n\n");

    for (int i=0; i < N_WORDS; i++) {
        printf("La longitud de '%s' es %u\n",
                words[i],
                fstring_length(words[i]));
    }

    printf("\n"
           "Probando fstring_eq()\n"
           "-----------------------------------------\n\n");

    for (int i=0; i < N_WORDS; i++) {
        for (int j=0; j < N_WORDS; j++) {
            if (fstring_eq(words[i], words1[j])) {
                printf("Los strings '%s' y '%s' son iguales\n\n",
                        words[i], words1[j]);
            }
            printf("El string '%s' va %s alfabeticamente que '%s'\n\n", 
                words[i],
                fstring_less_eq(words[i], words[j]) ? "antes": "despues",
                words[j]);
        }
    }
    return EXIT_SUCCESS;
}


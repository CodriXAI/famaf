/* First, the standard lib includes, alphabetically ordered */
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "counter.h"

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Check if in a given file there is a perfect match between all opening and closing parentheses.\n"
           "\n",
           program_name);
}

FILE * open_input_file(const char *filepath) {
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    return (file);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/*
    Lo que hace es ir revisando desde un archivo los caracteres uno por uno
    para ver si tiene los paréntesis balanceados.

    Y va comparando si es uno que abre '(' entonces va a incrementar en uno el contador

    SINO, se pregunta si está inicializado el counter y si no es un paréntesis que cierra ')'

    SINO, directamente si detecta que es un parentesis que cierra y el contador no está en su valor
    inicial, entonces decrementa el counter.

    FALTA INICIALIZAR EL COUNTER, sino no va a funcionar nunca

    Y FALTA RESOLVER DONDE PONER EL DESTROY para liberar la memoria

*/

bool matching_parentheses(FILE * file) {
    counter c = NULL;
    bool balanced = true;
    char letter;
    //Faltaba inicializarlo primeramente asi que aquí lo hacemos:
    c = counter_init();
    while (!feof(file) && balanced) {
        letter = fgetc(file);
        if (letter == '(') {
            counter_inc(c);
        } else if (counter_is_init(c)) {
            balanced = (letter != ')');
        } else if (letter == ')') {
            counter_dec(c);
        }
    }
    //return (balanced && counter_is_init(c)); anteriormente, corregido quedaría:
    balanced = balanced && counter_is_init(c);
    
    counter_destroy(c);

    return balanced;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    FILE *file = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* open the input file */
    file = open_input_file(filepath);

    /* call the function for the matching parentheses check */
    if (matching_parentheses(file)) {
        printf("Parentheses match.\n");
    } else {
        printf("Parentheses mismatch.\n");
    }

    return (EXIT_SUCCESS);
}

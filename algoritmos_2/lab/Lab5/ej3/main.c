/* First, the standard lib includes, alphabetically ordered */
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "list.h"

#include <assert.h>

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Compute average for the list of numbers in file.\n"
           "\n",
           program_name);
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
    Para calcular el promedio es hacer:
    Suma de sus elementos / la cantidad de elementos

    RECORDAR: list_elem e int son lo mismo
*/
float average(list l) {
    
    int Suma, largo;
    Suma = 0;
    largo = length(l);
    assert(largo != 0);
    for(int i = 0; i<largo; i++){
        Suma += index(l,i);
    }

    return (float)Suma / largo;
}

list array_to_list(int array[], unsigned int length) {
    list l = empty();
    for (unsigned int i = 0u; i < length; ++i) {
        l = addr(array[i],l);
    }
    return l;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* show the array in the screen */
    array_dump(array, length);

    /* transform from array to our list type */
    list l = array_to_list(array, length);

    /* call the average function */
    printf("The average is: %.2f \n", average(l));

    return (EXIT_SUCCESS);
}

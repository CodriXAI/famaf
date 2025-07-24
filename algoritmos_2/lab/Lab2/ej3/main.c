#include <stdio.h>
#include <stdlib.h>
#include "cima_log.h"

int main(void) {
    int a[] = {8};
    int length = 1;
    int result;

    result = cima_log(a, length);

    printf("Resultado: %i\n", result);

    return EXIT_SUCCESS;
}

/*
    == TEST: VALOR DE ARGC LUEGO DE GUARDA DEL IF ==
    Prueba rápida para medir el valor de argc y comprobar que efectivamente al realizar
    "if(0 < --argc)" se disminuye literalmente el valor de argc no solo en la guarda
*/ 

#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Antes de la guarda:\n");
    printf("  argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d] = %s\n", i, argv[i]);
    }
    printf("  argv[%d] = %p (NULL)\n\n", argc, argv[argc]);

    if (0 < --argc) { //INFO A COMPROBAR
        argv[argc] = NULL;

        printf("Dentro del if:\n");
        printf("  argc = %d\n", argc);
        for (int i = 0; argv[i] != NULL; i++) {
            printf("  argv[%d] = %s\n", i, argv[i]);
        }
        printf("  argv[%d] = %p (NULL)\n", argc, argv[argc]);
    }
    
    return 0;
}

/*
    Para compilación y ejecución:
    En bash:
        gcc test_ej7.c -o test
    Ejemplos:
        ./test ls -l
        ./test ls -l -a
        ./test arg1 arg2 arg3
*/

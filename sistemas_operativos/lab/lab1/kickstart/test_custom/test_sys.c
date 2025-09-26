#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    if (fork() == 0) {
    char *argv[] = {"ls", "-l", NULL};
    execvp(argv[0], argv);
    perror("execvp");
    exit(1);
    }else {
        wait(NULL); // padre espera
    }
    return 0;
}

/*
    Instrucciones para utilizar este testing:

    Compilar con:

    gcc -Wall -Wextra -pedantic -std=c99 -c test_sys.c $(pkg-config --cflags --libs glib-2.0)

    gcc -Wall -Wextra -pedantic -std=c99  test_sys.o $(pkg-config --cflags --libs glib-2.0) -o sys
    
    Ejecutar con:
    ./sys

    Para chequear memory leaks:
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no ./sys

    NOTAR que es probable que la librería glib.h puede ser propensa a tener memory leaks
*/
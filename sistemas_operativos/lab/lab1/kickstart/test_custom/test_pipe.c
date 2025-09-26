#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int p[2];
    pid_t pid1, pid2;

    if (pipe(p) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Primer fork: proceso hijo que ejecuta "ls"
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Hijo 1
        dup2(p[1], STDOUT_FILENO); // redirige stdout al pipe
        close(p[0]); // no usa lectura
        close(p[1]); // ya duplicado

        char *argv[] = {"ls", NULL};
        execvp(argv[0], argv);
        perror("execvp ls"); // solo si falla
        exit(EXIT_FAILURE);
    }

    // Segundo fork: proceso hijo que ejecuta "wc -l"
    pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Hijo 2
        dup2(p[0], STDIN_FILENO); // redirige stdin al pipe
        close(p[1]); // no usa escritura
        close(p[0]); // ya duplicado

        char *argv[] = {"wc", "-l", NULL};
        execvp(argv[0], argv);
        perror("execvp wc"); // solo si falla
        exit(EXIT_FAILURE);
    }

    // Proceso padre: cierra los extremos del pipe
    close(p[0]);
    close(p[1]);

    // Espera a ambos hijos
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

/*
    Instrucciones para utilizar este testing:

    Compilar con:

    gcc -Wall -Wextra -pedantic -std=c99 -c test_pipe.c $(pkg-config --cflags --libs glib-2.0)

    gcc -Wall -Wextra -pedantic -std=c99  test_pipe.o $(pkg-config --cflags --libs glib-2.0) -o pipe
    
    Ejecutar con:
    ./pipe

    Para chequear memory leaks:
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no ./pipe

    NOTAR que es probable que la librería glib.h puede ser propensa a tener memory leaks
*/
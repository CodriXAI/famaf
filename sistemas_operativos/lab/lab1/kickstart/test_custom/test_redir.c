#include "../command.h"
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>

static void redir(scommand self){
    assert(self != NULL);

    if(scommand_get_redir_in(self) != NULL){
        int in = open(scommand_get_redir_in(self), O_RDONLY);
        dup2(in, STDIN_FILENO); 
        close(in);
    }
    if(scommand_get_redir_out(self) != NULL){
        int out = open(scommand_get_redir_out(self), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(out, STDOUT_FILENO);
        close(out);
    }
}

int main(void) {
    
    scommand cmd = scommand_new();
    /* COMANDO DE PRUEBA */
    scommand_push_back(cmd, "ls");
    scommand_push_back(cmd, "-l");

    /* Establezco la redirección de salida a un archivo de texto */
    char *out = malloc(sizeof(char *));
    strcpy(out, "a.txt");
    scommand_set_redir_out(cmd, out);

    /* Redirecciono */
    redir(cmd);

    printf("Fui redireccionado al archivo");

    scommand_destroy(cmd);

    return 0;
}

/*
    Instrucciones para utilizar este testing:

    Compilar con:

    gcc -Wall -Wextra -pedantic -std=c99 -c command.c test_redir.c $(pkg-config --cflags --libs glib-2.0)

    gcc -Wall -Wextra -pedantic -std=c99  command.o test_redir.o $(pkg-config --cflags --libs glib-2.0) -o redir
    
    Ejecutar con:
    ./main

    Para chequear memory leaks:
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no ./main

    NOTAR que es probable que la librería glib.h puede ser propensa a tener memory leaks
*/
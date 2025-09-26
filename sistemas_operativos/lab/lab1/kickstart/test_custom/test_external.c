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

static char **scommand_to_array(scommand self){
    assert(self != NULL);

    unsigned int length = scommand_length(self);
    char **argv = malloc((length + 1) * sizeof(char*));

    for (unsigned int i = 0; !scommand_is_empty(self); i++){
        char *aux = g_strdup(scommand_front(self));
        argv[i] = aux;
        printf("array[%d] = %p. ", i, argv[i]);
        printf("Which points to : %s\n", argv[i]);
        scommand_pop_front(self);
    }
    argv[length] = NULL;
    printf("array[%d] = %p. ", length, argv[length]);
    printf("Which points to : %s\n", argv[length]);

    return argv;
}
/* Genera la lista dinámica de punteros char ** o *arg[]
 * Requires = self != NULL
 */

/*
static void destroy_array(char **argv){
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        free(argv[i]);  
    }
    free(argv);
}
*/

static void run_external(scommand self){
    /* Posiblemente muy rigurosa */
    assert(!scommand_is_empty(self) && true); 
    // assert(self != NULL) maybe?
    redir(self);
    char **argv = scommand_to_array(self);
    execvp(argv[0], argv);
    perror("execvp");
    exit(1);
} 

int main(void) {
    scommand cmd = scommand_new();
    
    scommand_push_back(cmd, "wc");
    scommand_push_back(cmd, "test_external.c");
    
    run_external(cmd);
    
    scommand_destroy(cmd);

    return 0;
}

/*
    Instrucciones para utilizar este testing:

    Compilar con:

    gcc -Wall -Wextra -pedantic -std=c99 -c command.c test_external.c $(pkg-config --cflags --libs glib-2.0)

    gcc -Wall -Wextra -pedantic -std=c99  command.o test_external.o $(pkg-config --cflags --libs glib-2.0) -o external
    
    Ejecutar con:
    ./external

    Para chequear memory leaks:
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no ./main

    NOTAR que es probable que la librería glib.h puede ser propensa a tener memory leaks
*/
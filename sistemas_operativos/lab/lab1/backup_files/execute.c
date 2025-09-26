#include <assert.h>
#include "builtin.h" 
#include "command.h"
#include "execute.h"
#include <fcntl.h> /* Para las macros de open */
#include <stdlib.h>
#include <glib.h>
#include <wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h> /* Para syscalls como fork, execvp, exit, wait, etc */
#include "tests/syscall_mock.h"


/* -----------------------------------------------MODULOS------------------------------------------------- */

static char **scommand_to_array(scommand self){
    assert(self != NULL);

    unsigned int length = scommand_length(self);
    char **argv = malloc((length + 1) * sizeof(char*));

    for (unsigned int i = 0; !scommand_is_empty(self); i++){
        char *aux = g_strdup(scommand_front(self));
        argv[i] = aux;
        scommand_pop_front(self);
    }
    argv[length] = NULL;
    
    return argv;
}
/* Genera la lista dinámica de punteros char ** o *arg[]
 * Requires = self != NULL
 */

static void destroy_array(char **argv){
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        free(argv[i]);  
    }
    free(argv);
}
/* Destruye la lista dinámica de punteros
 */

static void redir(scommand self){
    assert(self != NULL);

    if(scommand_get_redir_in(self) != NULL){
        int in = open(scommand_get_redir_in(self), O_RDONLY, 0);
        dup2(in, STDIN_FILENO); 
        close(in);
    }
    if(scommand_get_redir_out(self) != NULL){
        int out = open(scommand_get_redir_out(self), O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        dup2(out, STDOUT_FILENO);
        close(out);
    }
}
/* Se encarga de redireccionar en caso que haya una entrada y/o salida que no sea la estandar
 * Requires = self != NULL
 *  
 * EXPLICACIÓN DE MACROS:
 *      Para entrada (in) se usa O_RDONLY (read only) solo lectura
 *      Para salida (out) se utilizan: O_WRONLY | O_CREAT | O_TRUNC, 0644+
 *              O_WRONLY: sólo escritura.
 *              O_CREAT: crear si no existe.
 *              O_TRUNC: vaciar el archivo si ya existe.
 *              0644: permisos típicos (rw-r--r--).
 */

static void run_argv(char **argv){
    assert(argv != NULL && argv[0] != NULL);
    execvp(argv[0], argv);
    perror("execvp");
    exit(1);
}
/* Tomo el arreglo de punteros y lo ejecuto
 *
 */

static void run_command(scommand self){
    assert(self != NULL);
    redir(self);
    char **argv = scommand_to_array(self);
    run_argv(argv);
    destroy_array(argv);
} 
/* Ejecuto el comando si es externo
 *
 */


/* Se encarga de ejecutar un comando simple externo
 * Requires = (self != NULL && !scommand_is_empty(self) && !builtin_is_internal(self))
 */

/* -----------------------------------------FUNCIÓN GENERAL--------------------------------------------- */

void execute_pipeline(pipeline apipe){
    if(apipe != NULL && pipeline_length(apipe) != 0){
        unsigned int n = pipeline_length(apipe);

        int (*pipes)[2] = malloc((n-1) * sizeof *pipes); /* Array multidim que tiene [pipes][in/out] */

        for(unsigned int i = 0; i<n-1; i++){
            int p = pipe(pipes[i]); /* Creo una pipe */
        
            /* Si mientras creo pipes, haya surgido alguna con error, lo comunico */

            if(p == -1){
                perror("pipe()");
                exit(1);
            }
        }

        for(unsigned int i = 0; i < n; i++){

            /* Tomo el primer commando de la pipeline */
            scommand cmd = pipeline_front(apipe);

            if(builtin_alone(apipe)){
                builtin_run(cmd);
                pipeline_pop_front(apipe);
            }else if(cmd != NULL && !scommand_is_empty(cmd)){
                size_t pid = fork(); /* Bifurcación */

                if (pid == 0){ /* Proceso hijo */
                    if(i > 0){ /* Si NO soy el primer comando */
                        dup2(pipes[i-1][0], STDIN_FILENO);  /* Entonces tomo el stdin del comando anterior */
                    }
                    if(i < n-1){ /* Si NO soy el último comando */
                        dup2(pipes[i][1], STDOUT_FILENO);   /* Entonces escribo en el pipe correspondiente */
                    }

                    /* Cerrar los pipes que no utilizamos */
                    for(unsigned int j = 0; j < n-1; j++){  
                        close(pipes[j][0]);
                        close(pipes[j][1]);
                    }

                    /* Ejecución del comando dependiendo si es o no es interno */
                    if(builtin_is_internal(cmd)){
                        builtin_run(cmd);
                        exit(0); /* El reemplazo del execvp */
                    }else{
                        run_command(cmd);
                    }
                }else{
                    /* Proceso Padre: */
                    pipeline_pop_front(apipe);
                }
            }
    
        }

        for(unsigned int k = 0; k < n-1; k++){
            close(pipes[k][0]);
            close(pipes[k][1]);
        }

        free(pipes);
        /* Si está en foreground, debe esperar a todos los hijos */
        if(pipeline_get_wait(apipe)){
            for(unsigned int l = 0; l < n; l++){
                wait(NULL);
            }
        }
    }
}


#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtin.h"
#include "command.h"
#include "tests/syscall_mock.h"

bool builtin_is_internal (scommand cmd) {
	assert (cmd != NULL);
	char *cmd_name = scommand_front(cmd); 

	return (strcmp(cmd_name, "cd") == 0 || strcmp(cmd_name, "help") == 0 || strcmp(cmd_name, "exit") == 0); 
}

bool builtin_alone(pipeline p) {
	assert (p != NULL);
	return ((pipeline_length(p) == 1) && (builtin_is_internal(pipeline_front(p))));
}

void builtin_run(scommand cmd) {
    assert(cmd != NULL && !scommand_is_empty(cmd));
    
    char *cmd_name = scommand_front(cmd);
    
    if (strcmp(cmd_name, "cd") == 0) {
        scommand_pop_front(cmd);
        
        if (scommand_is_empty(cmd)) {
            const char *home = getenv("HOME");
            if (home != NULL) {
                if (chdir(home) != 0) {
					perror("cd");
                }
            }else {
                fprintf(stderr, "cd: variable HOME no definida\n");
            }
        } else {
            char *dir = scommand_front(cmd);
            if (chdir(dir) != 0) {
                perror("cd");
            }
        }
    }
    else if (strcmp(cmd_name, "help") == 0) {
        fprintf(stdout, 
			"NOS FALTA EL NOMBRE DE LA SHELL.\n"
			"cd [directorio] → cambia el directorio actual de trabajo. si no se especifica, va al directorio HOME.\n"
			"help → muestra información sobre los comandos internos disponibles.\n"
			"exit → termina la ejecución de la shell.\n"
			"\n"
		    "integrantes: Julian Arabel, Orlando Vigetti, Cristian Colares y Noah Casini.\n"
		);
    }    
	else if (strcmp(cmd_name, "exit") == 0) {
		fprintf(stdout, "saliendo del shell...\n");
        exit(EXIT_SUCCESS);
    }
    else {
        fprintf(stderr, "Error: comando builtin no reconocido: %s\n", cmd_name);
    }
}
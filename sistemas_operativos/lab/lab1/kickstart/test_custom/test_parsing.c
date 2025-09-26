#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "parsing.h"
#include "parser.h"
#include "command.h"

// Variables globales del parser
static Parser parser = NULL;
static FILE *input = NULL;

// Inicializa parser con contenido de string
static void init_parser(char *content) {
    assert(parser == NULL);
    assert(input == NULL);

    input = fmemopen(content, strlen(content), "r");
    parser = parser_new(input);
}

// Destruye parser y archivo asociado
static void destroy_parser() {
    if (parser != NULL) {
        parser_destroy(parser);
        parser = NULL;
    }
    if (input != NULL) {
        fclose(input);
        input = NULL;
    }
}

int main() {
    // Casos de prueba
    char *tests[] = {
        "ls |",
        "&   ",
        "|",
        ">",
        "grep || cd",
        "ls > >",
        "ls | &",
        "ls | cd",
        "ls             "
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);
    

    for (int i = 0; i < n_tests; i++) {
        printf("Test %d: '%s'\n", i+1, tests[i]);

        init_parser(tests[i]);

        // Parseamos la pipeline
        pipeline pl = parse_pipeline(parser);

        if (pl == NULL || pipeline_is_empty(pl)) {
            printf("-> Pipeline vacía o error de parseo\n\n");
        } else {
            printf("-> Pipeline parseada correctamente. Comandos:\n");
            int idx = 0;
            while (pl != NULL && !pipeline_is_empty(pl)) {
                scommand cmd = pipeline_front(pl);
                idx++;
                printf("   Comando %d: %s\n", idx, scommand_to_string(cmd));

                char *in = scommand_get_redir_in(cmd);
                char *out = scommand_get_redir_out(cmd);
                if (in) printf("     Redir IN: %s\n", in);
                if (out) printf("     Redir OUT: %s\n", out);

                pipeline_pop_front(pl);  // avanza al siguiente comando y libera memoria de este
            }
            pipeline_destroy(pl);  // destruimos la pipeline completa
        }

        destroy_parser();  // destruimos el parser y cerramos el archivo
        printf("\n");
    }

    return 0;
}




/* 
PARA TESTEAR BUILTIN ejecucion 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command.h"

// Prototipos de tus funciones builtins
bool builtin_is_internal(scommand cmd);
bool builtin_alone(pipeline p);
void builtin_run(scommand cmd);

// Función auxiliar para simular scommand simple
scommand create_scommand(int argc, char *argv[]) {
    scommand cmd = scommand_new();
    for (int i = 0; i < argc; i++) {
        scommand_push_back(cmd, argv[i]);
    }
    return cmd;
}

int main() {
    char *cmd1[] = {"help"};
    char *cmd2[] = {"cd", "/tmp"};
    char *cmd3[] = {"cd"};        // va al HOME
    char *cmd4[] = {"exit"};      // termina el programa

    scommand sc1 = create_scommand(1, cmd1);
    scommand sc2 = create_scommand(2, cmd2);
    scommand sc3 = create_scommand(1, cmd3);
    scommand sc4 = create_scommand(1, cmd4);

    printf("Test help:\n");
    builtin_run(sc1);
    printf("\n");

    printf("Test cd /tmp:\n");
    builtin_run(sc2);
    printf("Directorio actual: ");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n\n", cwd);

    printf("Test cd (HOME):\n");
    builtin_run(sc3);
    printf("Directorio actual: ");
    getcwd(cwd, sizeof(cwd));
    printf("%s\n\n", cwd);

    printf("Test exit:\n");
    builtin_run(sc4); // Esto terminará el programa

    return 0; // nunca se llega
}


gcc main.c parsing.c command.c objects-x86_64/parser.o objects-x86_64/lexer.o -o test ` pkg-config --cflags --libs glib-2.0 `
    
Ejecutar con:
./test

Para chequear memory leaks:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no ./test


*/


























/* #include <check.h>
#include <stdlib.h>

  	ESTE ES PARA DEBUGGEAR PARSING
// La función que ya definiste en test_parsing.c
Suite *parser_suite(void);

int main(void) {
    int number_failed;
    Suite *s = parser_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
*/ 

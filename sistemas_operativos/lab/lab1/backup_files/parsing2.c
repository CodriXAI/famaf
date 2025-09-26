#include <stdlib.h>
#include <stdbool.h>

#include "parsing.h"
#include "parser.h"
#include "command.h"

static bool handle_arguments (scommand new_cmd, char *arg, arg_kind_t type){
    bool control = false;

    if (type == ARG_NORMAL){
        scommand_push_back(new_cmd, arg);
        control = true;
    } else if (!scommand_is_empty(new_cmd)){
        if (type == ARG_INPUT && scommand_get_redir_in(new_cmd) == NULL){
            scommand_set_redir_in(new_cmd, arg);
            control = true; 
        } else if (type == ARG_OUTPUT && scommand_get_redir_out(new_cmd) == NULL){
            scommand_set_redir_out(new_cmd, arg); 
            control = true; 
        }
    } 
    
    if(!control){
      free(arg);
    }

    return control; 
}   

static scommand parse_scommand(Parser p){
    scommand new_cmd = scommand_new(); 
    bool done = false;
    arg_kind_t type; 
    char *arg = NULL; 

    parser_skip_blanks(p);

    while(!parser_at_eof(p) && !done){
        arg = parser_next_argument(p, &type);
        if (arg == NULL || !handle_arguments(new_cmd, arg, type)) {
                done = true; 
        }
    }

    return new_cmd; 
}

static void scommand_push (Parser p, pipeline result, bool *error, bool *another_pipe) {
    scommand cmd = parse_scommand(p);
    if (cmd != NULL && !scommand_is_empty(cmd)){
        pipeline_push_back(result, cmd);
    }  
    
    *error = (cmd==NULL || scommand_is_empty(cmd));   
    parser_op_pipe(p, another_pipe); 
}

static pipeline should_pipe_die (Parser p, pipeline result, bool *error){  
    bool garbage = false; 
    parser_garbage(p, &garbage);

    if (result != NULL){
        if (((*error && !pipeline_is_empty(result))) || 
            (parser_at_eof(p) && pipeline_is_empty(result))) {
            result = pipeline_destroy(result); 
        }
    }

    return result; 
}

pipeline parse_pipeline(Parser p){
    pipeline result = pipeline_new();   
    bool error = false, another_pipe=true, background = true;
   
    scommand_push(p, result, &error, &another_pipe); 

    while (another_pipe && !error && !parser_at_eof(p)){
        scommand_push(p, result, &error, &another_pipe);
    }

    if (!error){
        parser_op_background(p, &background); 
        pipeline_set_wait(result, !background);
    }
  
    result = should_pipe_die(p, result, &error);

    return result; 
}



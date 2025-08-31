#include <assert.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

struct scommand_s{
    GQueue *cmd;
    char *in;
    char *out;
};

scommand scommand_new(void){
    scommand new = malloc(sizeof(struct scommand_s));
    assert(new != NULL); 

    new->cmd = g_queue_new();
    new->in = NULL;
    new->out = NULL;

    return new;
}

scommand scommand_destroy(scommand self){
    assert(self != NULL);  

    while (!g_queue_is_empty(self->cmd)){ 
        char *elem = g_queue_pop_head(self->cmd);
        free(elem);
    }

    g_queue_free(self->cmd);
    free(self->in);
    free(self->out);
    free(self);
    
    self = NULL; 

    return self;
}

void scommand_push_back(scommand self, char * argument){
    assert(self!=NULL && argument!=NULL);
    g_queue_push_tail(self->cmd, g_strdup(argument));
    assert(!scommand_is_empty(self)); 
}

void scommand_pop_front(scommand self){
    assert(self!=NULL && !scommand_is_empty(self)); 
    char *front = g_queue_pop_head(self->cmd);
    free(front);
    front = NULL;
}

void scommand_set_redir_in(scommand self, char * filename){
    assert (self != NULL); 
    if (filename != NULL){
        if (self->in != NULL){
            free(self->in); 
        }
        self->in = filename; 
    }
    else{
        self->in = NULL; 
    }
}

void scommand_set_redir_out(scommand self, char * filename){
    assert (self != NULL); 
    if (filename != NULL){
        if (self->out != NULL){
            free(self->out);
        }
        self->out = filename; 
    }
    else{
        self->out = NULL; 
    }
}

bool scommand_is_empty(const scommand self){
    assert(self != NULL);
    return g_queue_get_length(self->cmd) == 0;
}

unsigned int scommand_length(const scommand self){
    assert(self != NULL);
    assert((g_queue_get_length(self->cmd) == 0) == scommand_is_empty(self));
    return g_queue_get_length(self->cmd);
}

char * scommand_front(const scommand self){
    assert(self != NULL && !scommand_is_empty(self));
    char *front = g_queue_peek_head(self->cmd);
    assert(front != NULL);
    return front;
}

char * scommand_get_redir_in(const scommand self){
    assert(self != NULL);
    return self->in;
}

char * scommand_get_redir_out(const scommand self){
    assert(self != NULL);
    return self->out;
}

char *scommand_to_string(const scommand self){
    assert(self != NULL);

    size_t total_len = 0;
    char *arg;

    for (guint i = 0; i < scommand_length(self); i++){
        arg = g_queue_peek_nth(self->cmd, i);
        total_len += strlen(arg) + 1; // +1 por el espacio o \0
    }
    
    if (scommand_get_redir_in(self)){
        total_len += strlen(" < ") + strlen(scommand_get_redir_in(self)); // "< " + archivo
    }
    if (scommand_get_redir_out(self)){
        total_len += strlen(" > ") + strlen(scommand_get_redir_out(self)); // "> " + archivo
    }

    char *straux;

    if (scommand_is_empty(self)){
        straux = malloc(1);
        straux[0] = '\0';
    }
    else{
        straux = malloc(total_len + 1);
        straux[0] = '\0';

        for (guint i = 0; i < scommand_length(self); i++){
            strcat(straux, g_queue_peek_nth(self->cmd, i));
            if (i < scommand_length(self) - 1){
                strcat(straux, " "); // espacios
            }
        }

        if (scommand_get_redir_in(self) != NULL){
            strcat(straux, " < ");
            strcat(straux, scommand_get_redir_in(self));
        }
        if (scommand_get_redir_out(self) != NULL){
            strcat(straux, " > ");
            strcat(straux, scommand_get_redir_out(self));
        }
    }

    return straux;
}

struct pipeline_s{
    GQueue *cmdline;
    bool wait;
};

pipeline pipeline_new(void){
    pipeline new = malloc(sizeof(struct pipeline_s)); 
    
    new->cmdline = g_queue_new(); 
    new->wait = true; 

    assert((new != NULL) && pipeline_is_empty(new) && pipeline_get_wait(new));

    return new; 
}

pipeline pipeline_destroy(pipeline self){
    assert(self != NULL); 

    while (!g_queue_is_empty(self->cmdline)){
        scommand sc = g_queue_pop_head(self->cmdline); 
        scommand_destroy(sc);  
    }

    g_queue_free(self->cmdline);  
    free(self);

    self = NULL; 
    
    assert(self == NULL); 

    return self; 
}

void pipeline_push_back(pipeline self, scommand sc){
    assert(self != NULL && sc != NULL);
    g_queue_push_tail(self->cmdline, sc);
    assert(!pipeline_is_empty(self)); 
}

void pipeline_pop_front(pipeline self){
    assert(self != NULL && !pipeline_is_empty(self)); 
    scommand front = g_queue_pop_head(self->cmdline);
    front = scommand_destroy(front);
}

void pipeline_set_wait(pipeline self, const bool w){
    assert(self != NULL);
    self->wait = w;
}

bool pipeline_is_empty(const pipeline self){
    assert(self != NULL);
    bool result = (g_queue_get_length(self->cmdline) == 0);
    return result;
}

unsigned int pipeline_length(const pipeline self){
    assert(self != NULL);
    unsigned int result = g_queue_get_length(self->cmdline);
    assert((result == 0) == pipeline_is_empty(self));
    return result;
}

scommand pipeline_front(const pipeline self){
    assert(self != NULL && !pipeline_is_empty(self));
    scommand result = g_queue_peek_head(self->cmdline);
    assert(result != NULL);
    return result;
}

bool pipeline_get_wait(const pipeline self){
    assert(self != NULL);
    return self->wait;
}

char *pipeline_to_string(const pipeline self){
    assert(self != NULL);
    
    char *straux;
    char *pipe;
    char *ampersand;
    scommand arg;

    straux = malloc(1);
    straux[0] = '\0';
    
    if(!pipeline_is_empty(self)){
        for(guint i = 0; i<pipeline_length(self);i++){
            arg = g_queue_peek_nth(self->cmdline, i);
            straux = strcat(straux, scommand_to_string(arg));
            if(i<pipeline_length(self)-1){
                pipe = malloc(4);
                pipe = " | ";
                straux = strcat(straux, pipe);
            }
        }
        if(!self->wait){
            ampersand = malloc(3);
            ampersand = " &";
            straux = strcat(straux, ampersand);
        }
    }
    return straux;
}
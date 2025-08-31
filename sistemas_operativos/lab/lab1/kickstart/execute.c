#include <assert.h>
#include "builtin.h" 
#include "command.h"
#include <stdlib.h>
#include <stdio.h>


void execute_pipeline(pipeline apipe){
    assert(apipe != NULL);

    /* Habría que verificar primero si es un comando interno antes de realizar lo otro */

    if(!builtin_is_internal()){

    }else{
       
    }
}

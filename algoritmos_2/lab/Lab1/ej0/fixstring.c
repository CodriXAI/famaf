#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length = 0;
    for(int i = 0; i<FIXSTRING_MAX;i++){
        if(s[i] != '\0'){
            length++;
        }
    }
    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool eq = true;
    /*
        Cantidad excesiva de Texto:
        if(fstring_length(s1) != fstring_length(s2)){
        eq = false;
        }else{
            for(unsigned int i = 0; i<FIXSTRING_MAX; i++){
                if(s1[i] == s2[i]){
                    eq = eq && true;
                }else{
                    eq = eq && false;
                }
            }
        }
    */
    for(int i=0;i<FIXSTRING_MAX;i++){
        eq = (s1[i] == s2[i]) && eq;
    }
    return eq;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    /*
    Forma Fer:
    */
    unsigned int i = 0u;
    bool less_eq = true;
    
    while(less_eq && s1[i] != '\0' && s2[i] != '\0'){
        less_eq = (less_eq && (s1[i] == s2[i])) || s1[i] < s2[i];
        i++;
    }

    return less_eq && (fstring_length(s1) <= fstring_length(s2));
    
    /*
    Incapaz de resolverlo
    */
}       

    
    





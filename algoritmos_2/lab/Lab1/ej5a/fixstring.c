#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    unsigned int i = 0;
    while(i < FIXSTRING_MAX && s[i] != '\0'){
        i++;
    }

    assert(i < FIXSTRING_MAX);

    return i;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool rest = true;
    unsigned int i = 0;
    unsigned int tam1 = fstring_length(s1);
    unsigned int tam2 = fstring_length(s2);
    if(tam1 != tam2){
        rest = false;
    }  

    while(rest && i < tam1){
        if(s1[i] != s2[i]){
            rest = false;
        }
    }

    return rest;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool res = false;
    unsigned int i = 0;
    unsigned int tam1 = fstring_length(s1);
    unsigned int tam2 = fstring_length(s2);

    while (s1[i] == s2[i] && i < tam1 && i < tam2) {
        i++;
    }
    res = s1[i] <= s2[i];
    return res;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    fstring_set(aux,s1);
    fstring_set(s1,s2);
    fstring_set(s2,aux);
}



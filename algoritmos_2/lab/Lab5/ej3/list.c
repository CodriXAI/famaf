#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

struct _node{
    list_elem elem; //Elemento del nodo
    node* next; //Puntero que apunta al siguiente nodo de la lista
};
/* 
    Definición de lo que es un nodo, o elemento de lista, con su elemento y puntero
    Colocado en la implementación para garantizar encapsulamiento.
*/

//-----------------------CONSTRUCTORS------------------------------

/* Crea una lista vacía */
list empty(void){
   return NULL;
}

/* Agrega un elemento e al inicio de la lista l */
list addl(list_elem e, list l){
    node* new_node = malloc(sizeof(node)); //Reservo memoria para otro nodo
    new_node->elem = e; //Al contenido del elem le asigno 'e'
    new_node->next = l; //Conecto por izquierda el nodo a la lista que tenía

    return new_node; //Devuelvo la lista final
}

//------------------------OPERATIONS-------------------------------

/* Determina si una lista es vacía */
bool is_empty(list l){
    return l == NULL;
}

/*
    Devuelve el primer elemento de la lista l
    PRE: !is_empty(l)
*/
list_elem head(list l){
    assert(!is_empty(l)); //Verifico PRECONDICIÓN
    list_elem e = l->elem; //Le asigno el primer elemento de la lista a e
    
    return e; //Lo devuelvo
}

/*
    Elimina el primer elemento de la lista l
    PRE: !is_empty(l)
*/
list tail(list l){
    assert(!is_empty(l)); //Verifico PRECONDICIÓN
    node* fst_node = l; //Guardo el primer elemento
    l = l->next; //Paso al siguiente
    free(fst_node); //Elimino el primer elemento

    return l; //Devuelvo la l modificada
}

/* Agrega el elemento e al final de la lista l */
list addr(list_elem e, list l){
    node* search; //Puntero para ir recorriendo la lista
    node* new_node; //Nodo a agregar
    new_node = malloc(sizeof(node)); //Reservo memoria para el nuevo nodo
    
    new_node->elem = e; //Asigno el elemento
    new_node->next = NULL; //De momento no apunta a nada
    
    //Nos posicionamos en el último nodo de la lista con search, y agregamos por derecha a new_node
    if(!is_empty(l)){
        search = l;
        while(search->next != NULL){
            search = search->next;
        }
        search->next = new_node;
    }else{
        l = new_node;
    }

    return l; //Devolvemos la lista modificada

}

/* Calcula el largo de la lista l */
unsigned int length(list l){
    node* search = l; //Puntero de búsqueda
    int n = 0; //Variable contador

    //Por cada elemento que encontremos, incrementamos en 1 n
    while(search != NULL){
        n++;
        search = search->next;
    }

    return n; //Devolvemos el largo
}

/* Agrega al final de l1 todos los elementos de l2 */
list concat(list l1, list l2){
    list result,search; //Creo un puntero para la lista concatenada y otro para conectar ambas listas
    
    result = l1; //Inicio siempre desde l1

    //Primer caso: La primer lista es vacía, entonces directamente la concatenacion es la segunda
    if(is_empty(l1) && !is_empty(l2)){
        result = l2;
    }else{ //Segundo caso, hay una primer lista no vacia y hay que recorrerla
        search = l1;
        while(search->next != NULL){
            search = search->next;
        }
        search->next = l2;
    }

    return result;
}

/*
    Devuelve el n-ésimo elemento de la lista l
    PRE: length(l) > n && n>0
*/
list_elem index(list l, unsigned int n){
    assert(length(l) > n); //Verifico PRECONDICIÓN
    
    node* search = l; //Declaro puntero de búsqueda del n-ésimo elemento
    unsigned int i = 0; //Variable contador para determinar cuando llegué

    //Mientras no haya llegado al valor necesario, sigo incrementando
    while(i<n){
        search = search->next;
        i++;
    }

    return search->elem; //Devuelvo el elemento
}

/* Deja en l solo los primeros n elementos, eliminando el resto*/
list take(list l, unsigned int n){
    //Un puntero para recorrer, el otro para eliminar y otro para devolver el resultado:
    node* search;
    node* kill; 
    node* result; 
    unsigned int i; //Indice para ir recorriendo la lista
    result = l; //Apuntamos al inicio de la lista
    //Si la lista es vacía no habría nada que eliminar
    if(!is_empty(l)){
        //Si tomamos 0 elementos, eliminamos todo:
        if(n == 0){
            while(l != NULL){
                kill = l;
                l = l->next;
                free(kill);
            }
            result = NULL; //Eliminamos todo, asi que nos queda la lista vacía
        }else if(n > 0){
            search = l;
            i = 1;
            //Buscamos el n-ésimo elemento:
            while(i < n && search->next != NULL){
                search = search->next;
                i++;
            }
            //Cortamos la lista en el n-ésimo elemento:
            node* aux = search->next;
            search->next = NULL;

            //Eliminamos los posteriores al n-ésimo elemento con el puntero auxiliar:
            while(aux!= NULL){
                kill = aux;
                aux = aux->next;
                free(kill);
            }
        }
    }

    return result; //Devolvemos la lista modificada
}

/* Elimina los primeros n elementos de la lista l, dejando el resto*/
list drop(list l, int n){
    node* kill; //Un puntero para eliminar

    //Si la lista es vacía no se puede eliminar nada
    if(!is_empty(l) && n!=0){
        while(n>0 && l!=NULL){ //Vamos contando con n los nodos que vamos eliminando, y cuando se elimine el último ya está
            kill = l;
            l = l->next;
            free(kill);
            n--; //Idea de chatgpt, ingenioso :0
        }
    }

    return l;
}

/* Copia la lista l en otra completamente nueva */
list copy_list(list l){
    /*
        NOTA: node* y list son lo mismo practicamente, uso uno u otro para mayor
        comodidad según lo que quiero hacer referencia
    */
    node* search;
    list l_copy = empty();

    search = l;

    while(search != NULL){
        l_copy = addr(search->elem,l_copy);
        search = search->next;
    }

    return l_copy;
}

/* Libera memoria en caso de ser necesario */
list destroy_list(list l){
    node* kill;

    while(l != NULL){
        kill = l;
        l = l->next;
        free(kill);
    }

    return NULL;
}





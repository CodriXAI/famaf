#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef Node *List;

/**
 * @brief Construye y devuelve una lista de ejemplo de 3 elementos
 */
List setup_example() {
    int i = 2;
    List my_list = NULL;
    Node *a_node;

    //Creo el primer nodo de la lista:
    my_list = malloc(sizeof(Node));
    a_node = my_list;
    
    //Agrego los demás elementos de la lista:
    while(i > 0){
        a_node->data = i*10;
        a_node->next = malloc(sizeof(Node));
        a_node = a_node->next;
        i--;
    }
    a_node->data = 0;    
    a_node->next = NULL;
    return my_list;
}

/**
 * @brief Elimina el primer elemento de la lista
 *
 * Precondicion: la lista xs no debe ser vacía
 */
List tail_example(List xs){
    assert(xs != NULL);
    Node *a_node;
    a_node = xs;
    xs = xs->next;
    free(a_node);
    a_node = NULL;

    return xs;
}

void show_list(List xs) {
    printf("[ ");
    while (xs != NULL) {
        printf("%i, ", xs->data);
        xs = xs->next;
    }
    printf("]\n");
}

int main(void) {
    List my_list;

    my_list = setup_example();

    printf("Lista antes del tail: ");

    show_list(my_list);

    my_list = tail_example(my_list);

    printf("Lista después del tail: ");

    show_list(my_list);

    return 0;
}

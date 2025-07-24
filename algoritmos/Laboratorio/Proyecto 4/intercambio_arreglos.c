//EJERCICIO 9:
#include <stdio.h>

//Prototipos de funciones:
void intercambiar(int tam, int a[], int i, int j);

int main(){
    //Defino todas las variables que voy a utilizar:
    int tam = 2;
    int a[tam];
    int i;
    int j;

    //Solicitando todos los elementos del array
    for(int i = 0; i < tam; i++){
        printf("Ingresar a[%d]:\n",i);
        scanf("%d",&a[i]);
    }
    //Pidiendo las posiciones a reemplazar
    printf("------------------------------------\n");
    printf("Ingresar posicion 1 del array:\n");
    scanf("%d",&i);
    printf("Ingresar posicion 2 del array:\n");
    scanf("%d",&j);

    //En caso de salirse del rango:
    if(i>tam || j > tam || i<0 || j<0){
        printf("Error: posiciones invalidas \nAsegurese que esten dentro del rango (0-%d) del array",tam);
    }else{
        //Llamo a intercambiar
        intercambiar(tam,a,i,j);
        printf("Se han intercambiado posiciones, el array resultante es:\n");
        //Decoracion
        printf("[");
        //Muestro los elementos de la lista
        for(i=0;i<tam;i++){
            //If para mas estetica
            if(i<tam-1){
                printf("%d,",a[i]);
            }else{
                printf("%d",a[i]);
            }
        }
        printf("] de nada :)");
    }
}

//Funcion intercambiar especificada
void intercambiar(int tam, int a[], int i, int j){
    int z;
    z = a[i];
    a[i] = a[j];
    a[j] = z;
}
/*
    EJEMPLO CON ARRAY DE TAMAÑO 2:
    Ingresar a[0]:
    2
    Ingresar a[1]:
    4
    ------------------------------------
    Ingresar posicion 1 del array:
    4
    Ingresar posicion 2 del array:
    3
    Error: posiciones invalidas 
    Asegurese que esten dentro del rango (0-2) del array

    OTRO EJEMPLO:

    Ingresar a[0]:
    2
    Ingresar a[1]:
    4
    ------------------------------------
    Ingresar posicion 1 del array:
    0
    Ingresar posicion 2 del array:
    1
    Se han intercambiado posiciones, el array resultante es:
    [4,2] de nada :)
*/
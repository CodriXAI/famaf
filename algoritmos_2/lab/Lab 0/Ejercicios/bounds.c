/*
La idea del programa es ofrecer al usuario un valor, un arreglo de longitud length
Y ver si:
    Todos los elementos del arreglo son mayores a value
    Lo mismo pero si son menores
    Si value está en el arreglo
    En qué posición está
Lo almacenamos a esa información en una struct
Y el proceso se hace en la función check_bound que toma los valores value, arr y length y devuelve una struct
*/
#include <stdio.h>
#include <stdbool.h>


struct bound_data{
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length);

struct bound_data check_bound(int value, int arr[], unsigned int length){
    struct bound_data resultado = {0,0,0,0};
    unsigned int upper_count, lower_count = 0;
    for(unsigned int i = 0;i<length;i++){
        if(value>=arr[i]){
            upper_count = upper_count + 1;
        }
        if(value<=arr[i]){
            lower_count = lower_count + 1;
        }
        if(value == arr[i]){
            resultado.exists = 1;
            resultado.where = i;
        }
    }
    if(upper_count == length){
        resultado.is_upperbound = 1;
    }
    if(lower_count == length){
        resultado.is_lowerbound = 1;
    }
    return(resultado);
}
int main(){
    int value, length;
    printf("Ingrese el tamaño del arreglo: \n");
    scanf("%d",&length);
    int arr[length];
    for(int i = 0; i<length; i++){
        printf("Ingresar valor N°%d:\n",i+1);
        scanf("%d",&arr[i]);
    }
    printf("Arreglo creado exitosamente:\n[");
    for(int i = 0;i<length;i++){
        if(i<length-1){
            printf("%d,",arr[i]);
        }else{
            printf("%d",arr[i]);
        }
    }
    printf("]\n");
    printf("Ingrese valor a comparar: \n");
    scanf("%d",&value);
    struct bound_data result = check_bound(value,arr,length);
    if(result.exists == 1){
        if(result.is_upperbound == 1){
            printf("El valor %d es el mayor\nFue encontrado en la posición N°%d\n del arreglo",value,result.where);
        }else if(result.is_lowerbound == 1){
            printf("El valor %d es el menor\nFue encontrado en la posición N°%d\n del arreglo",value,result.where);
        }else{
            printf("El valor %d no es ni el mayor ni el menor\nFue encontrado en la posición N°%d del arreglo\n",value,result.where);
        }
    }else{
        printf("El valor no ha sido encontrado en el arreglo\n");
    }
    return 0;
}
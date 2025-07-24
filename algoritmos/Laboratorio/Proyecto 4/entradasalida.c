//EJERCICIO 6:
#include<stdio.h>
//Prototipo de funciones:
void pedir_arreglo(int n_max, int a[n_max]);
void imprimir_arreglo(int n_max, int a[n_max]);
int main(void){
    //Definicion y solicitud del tamaño del array:
    int n_max;
    printf("Ingrese el tamaño del arreglo: \n");
    scanf("%d",&n_max);
    //Definicion del arreglo y ejecucion de funciones:
    int a[n_max];
    pedir_arreglo(n_max, a);
    imprimir_arreglo(n_max,a);
}
void pedir_arreglo(int n_max, int a[]){
    //Solicitando los valores de cada posicion del arreglo
    printf("Ingresar los valores del arreglo: \n");
    for(int i=0;i<n_max;i++){
        printf("a[%d]: ",i);
        scanf("%d",&a[i]);
    }
}
void imprimir_arreglo(int n_max, int a[]){
    //Recorriendo cada posicion y armando el arreglo con un poco de estilo:
    printf("El array resultante es: \n");
    printf("[");
    for(int i=0;i<n_max;i++){
        if(i<(n_max-1)){
            printf("%d,",a[i]);
        }else{
            printf("%d",a[i]);
        }
    }
    printf("] :)");
}
/*
    EJEMPLOS:
    Ingrese el tamaño del arreglo: 
    3
    Ingresar los valores del arreglo: 
    a[0]: 2
    a[1]: 4
    a[2]: 5
    El array resultante es: 
    [2,4,5] :)

    Ingrese el tamaño del arreglo: 
    2
    Ingresar los valores del arreglo: 
    a[0]: 6
    a[1]: 101
    El array resultante es: 
    [6,101] :)
*/
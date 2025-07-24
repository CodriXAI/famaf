#include <stdio.h>

struct comp_t {
    int menores;
    int iguales;
    int mayores;
};

struct comp_t cuantos(int tam, int a[], int elem);

struct comp_t cuantos(int tam, int a[], int elem){
    struct comp_t resultado = {0,0,0};
    int i=0;
    for(i=0;i<tam; i++){
        if(a[i] < elem){
            resultado.menores = resultado.menores+1;
        }else if(a[i] == elem){
            resultado.iguales = resultado.iguales+1;
        }else if(a[i] > elem){
            resultado.mayores = resultado.mayores+1;
        }
    }
    return resultado;
}

int main(){
    int tam;
    printf("Ingresar tamaño del arreglo: \n");
    scanf("%d",&tam);
    if(tam > 0 && tam < 5){
        int a[tam];
        int i;
        int elem;
        for(i = 0; i<tam; i++){
            printf("Ingresar valor: %d\n",i+1);
            scanf("%d",&a[i]);
        }
        printf("Ingresar valor a comparar: \n");
        scanf("%d",&elem);
        i = 0; //reset
        int flag=0;
        while(i < tam){
            if(a[i] == elem){
                flag = 1;
                break;
            }else{
                i++;
            }
        }
        if(flag == 0){
            printf("Valor no encontrado dentro del arreglo \n");
            return 1;
        }else{
            printf("El valor del arreglo es: \n");
            i = 0; //reset
            printf("[");
            while(i < tam){
                if(i < tam-1){
                    printf("%d, ",a[i]);
                }else{
                    printf("%d",a[i]);
                }
                i++;
            }
            printf("] \n");
            struct comp_t resultado = cuantos(tam,a,elem);
            printf("Hay %d elementos menores a %d \nHay %d elementos iguales a %d \nHay %d elementos mayores a %d \n",resultado.menores,elem,resultado.iguales,elem,resultado.mayores,elem);
            return 0;
        }
    }else{
        printf("No amigo no te sarpes .-. \n");
        return 1;
    }
}

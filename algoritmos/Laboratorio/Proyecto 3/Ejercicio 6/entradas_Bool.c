#include <stdio.h>
#include <stdbool.h>
bool pedir_booleano(char name);
void imprimir_booleano(bool x, char name);
int main(void){
    bool a = pedir_booleano('n');
    imprimir_booleano(a,'n');
}
bool pedir_booleano(char name){
    int temp;
    bool x;
    printf("Ingrese valor de verdad de la variable %c (0=False / 1=True): ",name);
    scanf("%d",&temp);
    x=temp;
    return x;
}
void imprimir_booleano(bool x, char name){
    if(x==false){
        printf("Variable %c es falso",name);
    }else if(x==true){
        printf("Variable %c es verdadero",name);
    }
}

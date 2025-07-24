//Programa que pide un caracter y me dice si es una vocal o no
#include <stdio.h>
#include <stdbool.h>

char pedirChar();
bool esVocal(char);

char pedirChar(){
    char car;
    printf("Ingrese un carácter: \n");
    scanf("%c",&car);
    return car;
}

bool esVocal(char car){
    return (car == 'a' || car == 'e' || car == 'i' || car == 'o' || car == 'u' || car == 'A' || car == 'E' || car == 'I' || car == 'O' || car == 'U');
}

int main(){
    char car = pedirChar();

    if(esVocal(car)){
        printf("El carácter %c es vocal \n",car);
    }else{
        printf("El carácter %c no es vocal \n",car);
    }
}
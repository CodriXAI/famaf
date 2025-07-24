#include <stdio.h>

int main(void){
    int x,y;

    x = 1;
    y = 1;

    if(x>=y){
        x=0;
        printf("Primera condicion activada :D \n");
    }else{
        if(x<=y){
            x=2;
            printf("Segunda condicion activada :D \n");
        }
    }

    printf("El resultado de x es %d",x);
}

/*
    Conclusion: No utilizar vs code en programas de logica pura, ya que se sabe que el "if"
    trabaja con la primer condicion que se satisfaga (True) ignorando a las demas
*/
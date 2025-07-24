//Intento de TA-TE-TI:
/*
Tablero:
- - -
- - -
- - -

info:
0 = -
1 = x (player)
2 = o (cpu)

Formas de ganar:
Una fila igual y distinta a 0
Una columna igual y distinta a 0
Una Diagonal igual y distinta a 0

Solución:
Crear un array de char llamado tablero, simulará el tablero
Crear un array mod, que dirá si ya se modificó cierta posición (0 = libre, 1 = por player, 2 = por cpu)

Información importante:
Detección de filas: Sucesión de a 1
Detección de columnas: Sucesión de a 3
Detección Diagonal 1: Sucesión de a 4
Detección Diagonal 2: Sucesión de a 2
TODOS SON DISTINTOS

Nos queda implementar el WIN y el LOSE
*/
#include <stdio.h>

void imprimirTablero(char[]);
void modTab(char[], int, int[]);
void cpuTab(char[], int[]);
//Función auxiliar:
void showMod(int[]);
int result(int[]);


void imprimirTablero(char tablero[]){
    int i = 0;
    printf("Tablero Actual: \n");
    while(i < 9){
        if(i == 2 || i == 5 || i == 8){
            printf(" %c \n",tablero[i]);
        }else{
            printf(" %c",tablero[i]);
        }
        i++;
    }
}
void modTab(char tablero[], int pos, int mod[]){
    int k = 1;
    while(k < 10){
        if(pos == k && mod[k-1] == 0){
            tablero[k-1] = 'x';
            mod[k-1] = 1;
            k++;
        }else{
            k++;
        }
    }
    imprimirTablero(tablero);
}
void cpuTab(char tablero[],int mod[]){
    //HACER DETECCIÓN:
    int m = 0;
    while(m < 9){
        if(mod[m]==0){
            tablero[m] = 'o';
            mod[m] = 2;
            break;
        }else{
            m++;
        }
    }
    imprimirTablero(tablero);
}
void showMod(int mod[]){
    int j = 0;
    while(j < 9){
        if(j == 2 || j == 5 || j == 8){
            printf(" %d \n",mod[j]);
        }else{
            printf(" %d",mod[j]);
        }
        j++;
    }
}

int main(){
    int defeat = 0; //Decide si termino o no el juego
    int pos; //Posicion donde jugaremos
    char tablero[] = {'-','-','-','-','-','-','-','-','-'};
    int mod[9] = {0,0,0,0,0,0,0,0,0};
    //Imprimimos el tablero en pantalla:
    imprimirTablero(tablero);
    //Prueba modificar tablero
    while(defeat == 0){
        printf("Ingresar posición a modificar [1-9]: \n");
        scanf("%d", &pos);
        modTab(tablero, pos, mod);
        cpuTab(tablero, mod);
        printf("\n");
        showMod(mod);
    }
    return 0;
}

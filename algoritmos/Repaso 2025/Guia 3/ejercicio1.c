#include <stdio.h>

int main(void){
    int valores[3];
    char nombres[3] = {'x', 'y', 'z'};
    int i = 0;
    //Carga de valores para x y z:
    while(i<3){
        printf("Ingrese valor de %c \n",nombres[i]);
        scanf("%d", &valores[i]);
        i++;
    }
    i = 0; //reset
    //Operaciones aritméticas del Ejercicio
    int operacionesAri[3] = {valores[0]+valores[1]+1,valores[2]*valores[2]+valores[1]*45-15*valores[0],valores[1] / 2 * valores[0]};
    printf("Los valores son: \n x = %d \n y = %d \n z = %d \n", valores[0],valores[1],valores[2]);
    while(i < 3){
        printf("Operacion aritmética solicitada nro.%d = %d \n", i+1, operacionesAri[i]);
        i++;
    }
    i = 0; //reset
    //Desigualdades
    while(i < 2){
        printf("Valor de desigualdad nro.%d = ",i+1);
        //y - 2 == (x * 3 + 1) % 5
        if(i == 0){
            if(valores[1]-2 == ((valores[0])*3+1) % 5){ 
                printf("True \n");
            }else{
                printf("False \n");
            }
        }else{
            //y < x * z
            if(valores[1] < valores[0] * valores[2]){
                printf("True \n");
            }else{
                printf("False 'n");
            }
        }
        i++;
    }
    return 0;
}






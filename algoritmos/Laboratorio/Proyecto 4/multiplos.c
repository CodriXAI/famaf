//EJERCICIO 8:
#include <stdio.h>
#include <stdbool.h>

//Prototipos de funciones:
bool todos_pares(int tam, int a[]);
bool existe_multiplo(int m, int tam, int a[]);

int main(){
    //definicion de funciones:
    int tam = 5;
    int a[tam];
    int m;
    int eleccion = 0;

    //Bucle de almacenamiento de elementos del array:
    for(int i = 0; i < tam; i++){
        printf("Ingrese el elemento %d del array:\n",i);
        scanf("%d",&a[i]);
    }

    //Eleccion de la funcion a ejecutar con mensaje de error opcional si elige algo que este fuera del rango:
    printf("¿Qué funcion deseas ejecutar?  0 = todosPares //  1 = existeMultiplo \n");
    scanf("%d",&eleccion);

    //Condicional de elecciones:
    if(eleccion == 0){
        //Eleccion todos pares:
        bool sonPares = todos_pares(tam,a);
        if(sonPares == true){
            printf("Todos los elementos del array son Pares");
        }else{
            printf("NO Todos los elementos del array son Pares");
        }
    }else if(eleccion == 1){
        //Eleccion hay multiplo:
        bool hayMultiplo = existe_multiplo(m,tam,a);
        if(hayMultiplo == true){
            printf("Hay un elemento del array multiplo");
        }else{
            printf("NO hay un elemento del array multiplo");
        }
    }else{
        //Eleccion equivocada:
        printf("Error: No eligio la opcion correcta :(");
    }
    
    return 0;
}
bool todos_pares(int tam, int a[]){
    /*
        El mecanismo de esta funcion es una flag que se activa si al menos encuentra en el
        array algun elemento que no cumpla el resto 0 al dividir el elemento por 2, por lo tanto
        cambiara su estado y lo cual hará que automaticamente se haga falso

        En caso contrario no pasara nada y seguira como true
    */
    bool flagPares = true;
    for(int i = 0; i < tam;  i++){
        if(a[i] % 2 == 0){
        }else{
            flagPares = false;
        }
    }
    return flagPares;
}
bool existe_multiplo(int m, int tam, int a[]){
    /*
        Mismo mecanismo pero a la inversa en este caso, una flag que se activa solo si encuentra
        al menos un elemento del array que de resto 0 al dividirlo por m

        Caso contrario se mantendra desacivado y por lo tanto no habra nisiquiera un elemento del
        array multiplo del mismo
    */
    bool flagmultiplo = false;
    printf("Ingrese valor de la variable m: \n");
    scanf("%d",&m);

    for(int i = 0; i < tam; i++){
        if(a[i] % m == 0){
            flagmultiplo = true;
        }else{

        }
    }
    return flagmultiplo;
}
/*
    EJEMPLOS:
    
    Ingrese el elemento 0 del array:
    2
    Ingrese el elemento 1 del array:
    4
    Ingrese el elemento 2 del array:
    6
    Ingrese el elemento 3 del array:
    7
    Ingrese el elemento 4 del array:
    1
    ¿Qué funcion deseas ejecutar?  0 = todosPares //  1 = existeMultiplo 
    0
    NO Todos los elementos del array son Pares

    
    Ingrese el elemento 0 del array:
    5
    Ingrese el elemento 1 del array:
    7
    Ingrese el elemento 2 del array:
    9
    Ingrese el elemento 3 del array:
    10
    Ingrese el elemento 4 del array:
    3
    ¿Qué funcion deseas ejecutar?  0 = todosPares //  1 = existeMultiplo 
    1
    Ingrese valor de la variable m: 
    2
    Hay un elemento del array multiplo
*/

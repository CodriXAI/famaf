#include <stdio.h>
#include <stdbool.h>

/*Ejercicio 1:*/
int main(void){
	/*Definicion de variables y solicitud de sus datos*/
	int x,y,z;
	printf("Ingrese valor de la variable x: \n");
	scanf("%d", &x);
	printf("Ingrese valor de la variable y: \n");
	scanf("%d", &y);
	printf("Ingrese valor de la variable z: \n");
	scanf("%d", &z);
	
	int exp1,exp2,exp4;
	int temp;
	bool exp3, exp5;
	
	exp1 = x + y + 1;
	exp2 = z * z + y * 45 - 15 * x;
	exp3 = y - 2 == (x * 3 + 1) % 5;
	exp4 = y / 2 * x;
	exp5 = y < x * z;
	
	printf("Expresion 1: %d \n",exp1);
	printf("Expresion 2: %d \n",exp2);
	printf("Expresion 3: %d \n",exp3);
	printf("Expresion 4: %d \n",exp4);
	printf("Expresion 5: %d \n",exp5);
	return 0;
}
/*
Para (x→7, y→3, z→5)
Expresion 1: 11 
Expresion 2: 55 
Expresion 3: 0 (False) 
Expresion 4: 7 
Expresion 5: 1 (True)

Para (x→1, y→10, z→8)
Expresion 1: 12 
Expresion 2: 499 
Expresion 3: 0 (False)
Expresion 4: 5 
Expresion 5: 0 (False)

En la Expresion 5, el tipo que devuelve es "Entero", 0 o 1 dependiendo su condición, simulando el comportamiento de un valor de tipo "Bool" 
*/




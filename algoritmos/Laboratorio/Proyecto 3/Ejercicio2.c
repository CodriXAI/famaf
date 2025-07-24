/*Ejercicio2:*/
#include <stdio.h>
#include <stdbool.h>
int main(void){
	/*Declaracion de variables:*/
	int x = (-4);
	int y = 4;
	int z = (-8);
	int temp;
	bool b,w,exp1,exp2,exp3;
	b = temp;
	w = temp;
	/*Definicion de expresiones:*/
	
	exp1 = x % 4 == 0 ; /*Tiene que dar 1(True)*/
	exp2 = x + y == 0 && y - x == (-1) * z; /*Tiene que dar 1(True)*/
	exp3 = !b && w; /*Tiene que dar 0(False)*/
	
	printf("Expresion 1: %d \n",exp1);
	printf("Expresion 2: %d \n",exp2);
	printf("Expresion 3: %d \n",exp3);
	return 0;
	
	/*
	Valores: 
	x = -4
	y = 4
	z = -8
	b = temp
	w = temp
	*/
}

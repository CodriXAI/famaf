//EJERCICIO 1A:
#include <stdio.h>
#include <assert.h>
/*Prototipo de las funciones a utilizar*/
void hola_hasta(int n);
int pedirEntero(int n);

int main(void){
	int n;
	n = pedirEntero(n);
	//Precondicion con assert
	assert (n>0);
	hola_hasta(n);
	return 0;
}

//Funcion que permite repetir el Hola si es cumplida la precondicion
void hola_hasta(int n){
	while(n>0){
		printf("Hola \n");
		n=n-1;
	}
	//Postcondicion despues del while
}

//Puedo usar la funcion pedirEntero para solicitarle al usuario el valor n de la siguiente forma:
int pedirEntero(int n){
	printf("Ingrese cantidad de veces a mostrar hola \n");
	scanf("%d", &n);
	return n;
}

/*
	EJEMPLOS:
	Ingrese cantidad de veces a mostrar hola 
	2
	Hola 
	Hola

	Ingrese cantidad de veces a mostrar hola 
	10
	Hola 
	Hola
	Hola 
	Hola
	Hola 
	Hola
	Hola 
	Hola
	Hola 
	Hola
*/
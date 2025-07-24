#include <stdio.h>

void swap(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

int main(void){
   int x,y;
   x = 6;
   y = 4;
   printf("Antes del swap: \n");
   printf("x = %d, y = %d\n",x,y);
   swap(&x,&y);
   printf("Después del swap: \n");
   printf("x = %d, y = %d\n",x,y); 
   return 0; 
}




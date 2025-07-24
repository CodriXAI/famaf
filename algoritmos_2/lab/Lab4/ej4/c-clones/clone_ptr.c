#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ansicolors.h"

#define MAX_LENGTH 1820

//Creo la función auxiliar para calcular el largo sin usar string.h
size_t string_length(const char *str){
    size_t largo = 0;
    while(str[largo]!= '\0'){
        largo++;
    }
    return largo;
}

char *string_clone(const char *str, size_t length) {
    char *output= malloc((length + 1) * sizeof(char)); // <-- Reservo memoria +1 (por el \0) por cada tamaño de caracter
    for (size_t i=0; i<length;i++) {
        output[i] = str[i];
    }
    output[length] = '\0';
    return output;
}

/*
    Devolución de valgrind:
    ==3760== Invalid write of size 1
    ==3760==    at 0x1092AF: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Address 0x1ffeffe710 is on thread 1's stack
    ==3760==  1856 bytes below stack pointer
    ==3760== 
    ==3760== Invalid write of size 1
    ==3760==    at 0x1092BD: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Address 0x1ffeffe711 is on thread 1's stack
    ==3760==  1855 bytes below stack pointer
    ==3760== 
    ==3760== Invalid write of size 1
    ==3760==    at 0x1092CB: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Address 0x1ffeffe712 is on thread 1's stack
    ==3760==  1854 bytes below stack pointer
    ==3760== 
    ==3760== Invalid write of size 1
    ==3760==    at 0x1092D9: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Address 0x1ffeffe713 is on thread 1's stack
    ==3760==  1853 bytes below stack pointer
    ==3760== 
    ==3760== Invalid write of size 1
    ==3760==    at 0x1092E7: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Address 0x1ffeffe714 is on thread 1's stack
    ==3760==  1852 bytes below stack pointer
    ==3760== 
    ==3760== Invalid write of size 1
    ==3760==    at 0x1092F5: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Address 0x1ffeffe715 is on thread 1's stack
    ==3760==  1851 bytes below stack pointer
    ==3760== 
    ==3760== Conditional jump or move depends on uninitialised value(s)
    ==3760==    at 0x484F289: __strlen_sse2 (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==3760==    by 0x48D6DA7: __printf_buffer (vfprintf-process-arg.c:435)
    ==3760==    by 0x48D773A: __vfprintf_internal (vfprintf-internal.c:1544)
    ==3760==    by 0x48CC1B2: printf (printf.c:33)
    ==3760==    by 0x109315: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Uninitialised value was created by a stack allocation
    ==3760==    at 0x48D50A0: __printf_buffer (vfprintf-internal.c:600)
    ==3760== 
    ==3760== Conditional jump or move depends on uninitialised value(s)
    ==3760==    at 0x484F298: __strlen_sse2 (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==3760==    by 0x48D6DA7: __printf_buffer (vfprintf-process-arg.c:435)
    ==3760==    by 0x48D773A: __vfprintf_internal (vfprintf-internal.c:1544)
    ==3760==    by 0x48CC1B2: printf (printf.c:33)
    ==3760==    by 0x109315: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Uninitialised value was created by a stack allocation
    ==3760==    at 0x48D50A0: __printf_buffer (vfprintf-internal.c:600)
    ==3760== 
    ==3760== Syscall param write(buf) points to uninitialised byte(s)
    ==3760==    at 0x4988574: write (write.c:26)
    ==3760==    by 0x48FF974: _IO_file_write@@GLIBC_2.2.5 (fileops.c:1181)
    ==3760==    by 0x48FE570: new_do_write (fileops.c:449)
    ==3760==    by 0x48FE570: _IO_do_write@@GLIBC_2.2.5 (fileops.c:426)
    ==3760==    by 0x48FFAAE: _IO_new_file_xsputn (fileops.c:1244)
    ==3760==    by 0x48FFAAE: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1197)
    ==3760==    by 0x48CCCC8: __printf_buffer_flush_to_file (printf_buffer_to_file.c:59)
    ==3760==    by 0x48CCCC8: __printf_buffer_to_file_done (printf_buffer_to_file.c:120)
    ==3760==    by 0x48D7742: __vfprintf_internal (vfprintf-internal.c:1545)
    ==3760==    by 0x48CC1B2: printf (printf.c:33)
    ==3760==    by 0x109315: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Address 0x4a81052 is 18 bytes inside a block of size 1,024 alloc'd
    ==3760==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==3760==    by 0x48F11B4: _IO_file_doallocate (filedoalloc.c:101)
    ==3760==    by 0x4901523: _IO_doallocbuf (genops.c:347)
    ==3760==    by 0x48FEF8F: _IO_file_overflow@@GLIBC_2.2.5 (fileops.c:745)
    ==3760==    by 0x48FFAAE: _IO_new_file_xsputn (fileops.c:1244)
    ==3760==    by 0x48FFAAE: _IO_file_xsputn@@GLIBC_2.2.5 (fileops.c:1197)
    ==3760==    by 0x48CCB48: __printf_buffer_flush_to_file (printf_buffer_to_file.c:59)
    ==3760==    by 0x48CC7E4: __printf_buffer_do_flush (printf_buffer_flush.c:53)
    ==3760==    by 0x48CC7E4: __printf_buffer_flush (Xprintf_buffer_flush.c:65)
    ==3760==    by 0x48CCDA8: __printf_buffer_write (Xprintf_buffer_write.c:33)
    ==3760==    by 0x48D551B: __printf_buffer (vfprintf-process-arg.c:501)
    ==3760==    by 0x48D773A: __vfprintf_internal (vfprintf-internal.c:1544)
    ==3760==    by 0x48CC1B2: printf (printf.c:33)
    ==3760==    by 0x1092A7: main (in /home/cris/FAMAF/Algoritmos_2/Lab/Lab4/ej4/c-clones/clone)
    ==3760==  Uninitialised value was created by a stack allocation
    ==3760==    at 0x48D50A0: __printf_buffer (vfprintf-internal.c:600)
    ==3760== 


    Posible problema:
        El problema se origina en char *output = clone, ya que alojo el puntero en memoria stack
        
        Quizás se deba a que en vez de clonar el elemento, estemos clonando
        la dirección en memoria, cuando realmente deberíamos ir accediendo al contenido del mismo
        e ir modificándolo para que sea el original - descartado ya que ambos son caracteres

        Posible solución: Reservar en memoria heap el espacio suficiente para output y ahi empezar a modificarlo
        NO OLVIDAR liberarlo

    Valor de length habiendo utilizado gdb:
    $1 = 1812

    Y ese valor está dado por:
    sizeof(original) / sizeof(*original)
    Donde sizeof(original) = 1812
          sizeof(*original) = 1
    Lo cual es un problema al generalizarlo porque demuestra que el tamaño depende del tipo, en este caso funciona
    porque original es un array en memoria stack

    Posible solución: Calcular de forma manual la longitud real de original y guardarla en el copy medinate string_clone
    

*/


int main(void) {
    char *original=""
         "______ time ago in a galaxy far, far away...\n\n\n"
         ANSI_BRGOLD
         "         _______..___________.     ___      .______             \n"
         "        /       ||           |    /   \\     |   _  \\          \n"
         "       |   (----``---|  |----`   /  ^  \\    |  |_)  |          \n"
         "        \\   \\        |  |       /  /_\\  \\   |      /        \n"
         "    .----)   |       |  |      /  _____  \\  |  |\\  \\----.    \n"
         "    |_______/        |__|     /__/     \\__\\ | _| `._____|     \n"
         "                                                                \n"
         "____    __    ____      ___      .______           _______.     \n"
         "\\   \\  /  \\  /   /     /   \\     |   _  \\         /       |\n"
         " \\   \\/    \\/   /     /  ^  \\    |  |_)  |       |   (----` \n"
         "  \\            /     /  /_\\  \\   |      /         \\   \\    \n"
         "   \\    /\\    /     /  _____  \\  |  |\\  \\----..----)   |   \n"
         "    \\__/  \\__/     /__/     \\__\\ | _| `._____||_______/     \n"
         "\n\n\n"
         "                           Episode II \n\n"
         "                      ATTACK OF THE CLONES\n\n"
         "                There is  unrest in the Galactic\n"
         "                Senate. Several  thousand  solar\n"
         "                systems  have   declared   their\n"
         "                intentions to leave the Republic.\n\n"
         "                This      separatist     movement,\n"
         "                under  the   leadership   of  the\n"
         "                mysterious   Count   Dooku,   has\n"
         "                made it difficult for the limited\n"
         "                number   of   Jedi   Knights   to\n"
         "                maintain   peace   and  order  in\n"
         "                the galaxy.\n\n"
         "                Senator   Amidala,   the   former\n"
         "                Queen   of  Naboo,  is  returning\n"
         "                to  the  Galactic  Senate to vote\n"
         "                on the critical issue of creating\n"
         "                an    ARMY    OF   THE   REPUBLIC\n"
         "                to    assist    the   overwhelmed\n"
         "                Jedi....\n" ANSI_WHITE;
    char *copy=NULL;

    //Creo una variable que me guarde el tamaño de original de forma correcta:
    size_t tam = string_length(original);
    copy = string_clone(original, tam);
    printf("Original:\n" ANSI_CYAN
            " %s\n", original);
    copy[0] = 'A';
    copy[1] = ' ';
    copy[2] = 'l';
    copy[3] = 'o';
    copy[4] = 'n';
    copy[5] = 'g';
    printf("Copia   :\n" ANSI_CYAN
           " %s\n", copy);
    free(copy); // <-- Libero la memoria y evito Memory Leak
    return EXIT_SUCCESS;
}

/*
    Error dado en terminal al cambiar char original = "..." por char *original = "...":
    clone_ptr.c: In function ‘main’:
    clone_ptr.c:166:51: error: division ‘sizeof (char *) / sizeof (char)’ does not compute the number of array elements [-Werror=sizeof-pointer-div]
    166 |     copy = string_clone(original, sizeof(original)/sizeof(*original));
        |                                                   ^
    clone_ptr.c:127:11: note: first ‘sizeof’ operand was declared here
    127 |     char *original=""
        |           ^~~~~~~~
    cc1: all warnings being treated as errors

    Al parecer no puede hacer la división porque quiere tomar el tamaño de original como arreglo, el tema es que ahora original
    es un puntero, y por ende solo tomará 8 bits (al estar en 64 bits). 

    Posible Solución: Como se muestra arriba, fue llamar a una función auxiliar que se encargue de calcular el largo de la cadena
    Luego reservar suficiente memoria en copy para poder copiarla correctamente y luego liberarla en el main para evitar
    Memory Leak
*/

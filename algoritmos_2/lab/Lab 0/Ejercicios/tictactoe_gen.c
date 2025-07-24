/*
    Ejercicio 3a) Con ta te ti 4x4:

    Notaciones:
    \t - espacio de tabulador en pantalla
    A = A == B ? B : C - Operador ternario, como un if compacto
    Equivalencia:
    if(A == B){
        B
    }else{
        C    
    }
    char board[3][3] - matriz de carácteres llamada board de 3x3
*/


#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */
#include <assert.h>  /* assert() */

#define CELL_MAX (4 * 4 - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");
}

void print_board(char board[4][4]){
    int cell = 0;

    print_sep(4);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column){
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(4);
    }
}


//La idea es ver las condiciones para que gane 'X', o que gane 'O':
char get_winner(char board[4][4]){
    char winner = '-';
    return winner;
}

/*La misión aquí es poder detectar cuando todos los espacios de la matriz sean distintos de '-'*/
bool has_free_cell(char board[4][4]){
    bool free_cell=true; /*modifico esto a true a ver que sucede con el while*/
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            if(board[row][column] == '-'){
                free_cell=true;
                break;
            }else{
                free_cell=false;
            }        
        }
    }
    return free_cell;
}

int main(void){
    printf("TicTacToe\n");

    char board[4][4] = {
        { '-', '-', '-', '-' },
        { '-', '-', '-', '-' },
        { '-', '-', '-', '-' },
        { '-', '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0 || scanf_result>CELL_MAX) { //Corrección de rango del lado derecho
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / 3;
            int colum = cell % 3;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}

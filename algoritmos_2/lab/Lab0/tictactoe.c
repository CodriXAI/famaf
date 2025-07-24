/*
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

#define CELL_MAX (3 * 3 - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");
}

void print_board(char board[3][3]){
    int cell = 0;

    print_sep(3);
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column){
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(3);
    }
}


//La idea es ver las condiciones para que gane 'X', o que gane 'O':
char get_winner(char board[3][3]){
    char winner = '-';
    for(int i=0;i<3;i++){
        if(board[i][0] == 'X' && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            winner = 'X';
        }else if(board[i][0] == 'O' && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
            winner = 'O';
        }else if(board[0][i] == 'X' && board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            winner = 'X';
        }else if(board[0][i] == 'O' && board[0][i] == board[1][i] && board[1][i] == board[2][i]){
            winner = 'O';
        }
    }
    if(board[0][0] == 'X' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        winner = 'X';
    }else if(board[2][0] == 'X' && board[2][0] == board[1][1] && board[1][1] == board[0][2]){
        winner = 'X';
    }else if(board[0][0] == 'O' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        winner = 'O';
    }else if(board[2][0] == 'O' && board[2][0] == board[1][1] && board[1][1] == board[0][2]){
        winner = 'O';
    }
    return winner;
}

/*La misión aquí es poder detectar cuando todos los espacios de la matriz sean distintos de '-'*/
bool has_free_cell(char board[3][3]){
    /*
    Solución previamente pensada:
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            if(board[row][column] == '-'){
                free_cell=true;
                break;
            }else{
                free_cell=false;
            }        
        }
    }
    No puedo usar break :)
    */
    bool free_cell=false; //modifico esto a true a ver que sucede con el while del main
    for(int row = 0; row<3; ++row){
        for(int column = 0; column<3; ++column){
            if(board[row][column] == '-'){
                free_cell = true;
            }
        }
    }
    return free_cell;
}

int main(void){
    printf("TicTacToe\n");

    char board[3][3] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
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

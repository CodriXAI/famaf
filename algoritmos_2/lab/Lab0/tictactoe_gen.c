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

int n;

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");
}

void print_board(char board[n][n]){
    int cell = 0;
    print_sep(n);
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column){
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(n);
    }
}


//La idea es ver las condiciones para que gane 'X', o que gane 'O':
char get_winner(char board[n][n]){
    char winner = '-';
    bool row_win,col_win,diagon_win,antidiagon_win;
    diagon_win = true;
    antidiagon_win = true;
    for(int i = 0; i < n; i++){
        row_win = true;
        col_win = true;
        for(int j = 0; j < n; j++){
            //Filas:
            if(board[i][j] != board[i][0] || board[i][j] == '-'){
                row_win = false;
            }
            //Columnas:
            if(board[j][i] != board[0][i] || board[j][i] == '-'){
                col_win = false;
            }
        }
        if(board[i][i] != board[0][0] || board[i][i] == '-'){
            diagon_win = false;
        }
        if(board[i][n-1-i] != board[0][n-1] || board[i][n-1-i] == '-'){
            antidiagon_win = false;
        }
        if(row_win && board[i][0] != '-'){
            winner = board[i][0];
        }
        if(col_win && board[0][i] != '-'){
            winner = board[0][i];
        }
    }
    if(diagon_win && board[0][0] != '-'){
        winner = board[0][0];
    }
    if(antidiagon_win && board[0][n-1] != '-'){
        winner = board[0][n-1];
    }
    return winner;
}

/*La misión aquí es poder detectar cuando todos los espacios de la matriz sean distintos de '-'*/
bool has_free_cell(char board[n][n]){
    bool free_cell=false; //modifico esto a true a ver que sucede con el while del main
    for(int row = 0; row<n; ++row){
        for(int column = 0; column<n; ++column){
            if(board[row][column] == '-'){
                free_cell = true;
            }
        }
    }
    return free_cell;
}

int main(void){
    printf("TicTacToe\n");
    printf("Ingresar dimensión de su Tic Tac Toe:\n");
    scanf("%d",&n);
    char board[n][n];
    for(int row=0; row<n; row++){
        for(int column=0;column<n;column++){
            board[row][column] = '-';
        }
    } 
    int CELL_MAX = (n * n - 1);
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
            int row = cell / n;
            int colum = cell % n;
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

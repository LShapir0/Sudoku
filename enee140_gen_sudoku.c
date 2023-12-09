/*
 * enee140_gen_sudoku.c
 *
 *  Generate Sudoku boards.
 *
 */

#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int board[9][9];
    int bit;
    srand(time(0));


     if(atoi(argv[2]) & 1<<1){
       int blanks = rand() % (61 - 31 + 1)) + 31;
         new_sudoku_board(board,  blanks);
     }




    if(atoi(argv[2]) & 1<<1){

    }


    return 0;
}



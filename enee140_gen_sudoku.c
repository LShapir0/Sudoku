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
    int board[9][9]; // Initializing board
    int args = atoi(argv[2]); // Converts arg string argument to int

    srand(time(0)); // Seeding random number generation

    if( args & 1<<0){
        read_sudoku_board(argv[1], board);
        is_valid_board(board);
        if ((read_sudoku_board(argv[1], board)) != 0){
            printf("Invalid input.");
            return 0;
        }
    } else {
        int blanks = rand() % (61 - 31 + 1) + 31;
        new_sudoku_board(board, blanks);
    }
    if(args & 1<<1){
        transform_permute_rows(board);
    }
    if(args & 1<<2){
        transform_permute_bands(board);
    }
    if(args & 1<<3){
        transform_permute_columns(board);
    }
    if(args & 1<<4){
        transform_permute_stacks(board);
    }
    if(args & 1<<5){
        transform_flip_main_diagonal(board);
    }
    if(args & 1<<6){
        transform_flip_minor_diagonal(board);
    }
    if(args & 1<<7){
        print_sudoku_board(board);
    }

    return 0;
}



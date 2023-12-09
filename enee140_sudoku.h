/*
 * enee14_sudoku.h
 *
 *  Function prototypes for the Sudoku library.
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

int is_valid_board(int board[9][9]);

void new_sudoku_board(int board[9][9], int blanks);

void transform_permute_rows(int board[9][9]);

void transform_permute_columns(int board[9][9]);

void transform_flip_main_diagonal(int board[9][9]);

void transform_flip_minor_diagonal(int board[9][9]);

int print_sudoku_board(int board[9][9]);


int read_sudoku_board(const char file_name[], int board[9][9]);



int print_board(int board[9][9]); // Print the board. For testing purposes only.

int swap_rows(int row1, int row2, int board[9][9]); // Swap rows.

int swap_cols(int col1, int col2, int board[9][9]); // Swap columns.


#endif /* SUDOKU_H_ */

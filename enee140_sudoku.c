#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 *  Checks if the board is valid.
 */
int is_valid_board(int board[9][9]) {
    int testBucket[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0; //Loop variable for row
    int j = 0; //Loop variable for column
    int k = 0; //Iterates through the tested row or column
    int boxcolumn = 0;
    int boxtest = 0;

    /* An algorithm to check if the rows have repeated values. If it does, return 0;
     *
     * k - Looks at a value, starting at index of the next column of the value, so it doesn't count itself as a match, and checks the row for a match.
     * j - Iterates across the columns.
     * i - Iterates down the rows.
     */
    for (i = 0; i < 9; i++) { // Rows
        for (j = 0; j < 9; j++) { // Columns
            for (k = j + 1; k < 9; k++) { // Checks the row, starting at the next number in the row.
                if (board[i][j] == board[i][k] && board[i][j] != 0) {
                    return 0; // Repeated value has been found.
                }
            }
        }
    }

    /* An algorithm to check if the columns have repeated values. If it does, return 0;
     *
     * k - Looks at a value, starting at index of the next row down of the value, so it doesn't count itself as a match, and checks the column for a match.
     * j - Iterates across the columns.
     * i - Iterates down the rows.
     */
    for (j = 0; j < 9; j++) { //Rows
        for (i = 0; i < 9; i++) { //Columns
            for (k = i + 1; k < 9; k++) { // Runs down the column, starting at the number down the column.
                if (board[i][j] == board[k][j] && board[i][j] != 0) {
                    return 0; // Repeated value has been found.
                }
            }
        }
    }

    /* An algorithm to check if the every number is between 0 and 9 (inclusive).
     *
     * j - Iterates across the columns.
     * i - Iterates down the rows.
     */
    for (j = 0; j < 9; j++) { //Rows
        for (i = 0; i < 9; i++) { //Columns
            if (board[i][j] < 0 ||
                board[i][j] > 9) { //Checks each value in the matrix if it is less than 0 or more than 9;
                return 0; // Repeated value has been found.
            }
        }
    }

    /* An algorithm to test if there are repeated numbers in a box. It works by putting every 3x3 box
     * in an array, and testing that array for repeated values.
     *
     * j - Iterates across the columns.
     * i - Iterates down the rows.
     */
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if ((j + 1) % 3 == 0 &&
                (i + 3) % 3 == 0) { // This stops the loop if it reaches the upper right hand corner of a box.
                // The following code puts the values of the corresponding box in to testBucket, which
                // is the array used to test for repeated values.

                //These are the 2 values before (left of) the corner (including the corner).
                testBucket[0] = board[i][j - 2];
                testBucket[1] = board[i][j - 1];
                testBucket[2] = board[i][j];

                //These are the values under the row that were identified above.
                testBucket[3] = board[i + 1][j - 2];
                testBucket[4] = board[i + 1][j - 1];
                testBucket[5] = board[i + 1][j];

                //These are the values under the row that were identified above (again) which completes one 3x3 box.
                testBucket[6] = board[i + 2][j - 2];
                testBucket[7] = board[i + 2][j - 1];
                testBucket[8] = board[i + 2][j];

                for (boxcolumn = 0; boxcolumn < 9; boxcolumn++) { // Goes through every column of the test array.
                    for (boxtest = boxcolumn + 1; boxtest < 9; boxtest++) { // Checks every index in the array, starting at one past the index being looked at.
                        if ((testBucket[boxcolumn] == testBucket[boxtest]) && testBucket[boxcolumn] != 0) {
                            return 0; // Repeated value has been found.
                        }
                    }
                }
            }
        }
    }

    return 1; // Success.
}

/**
 * Generates new sudoku boards.
 */
void new_sudoku_board(int board[9][9], int blanks) {
    int i; // Rows
    int j; // Columns
    int k; // Counts number of blanks generated.
    srand((time(0))); // Seeding random number generation.

    // Beginning with generic board.
    int GenericBoard[9][9] = {{1, 2, 3, 4, 5, 6, 7, 8, 9},
                              {4, 5, 6, 7, 8, 9, 1, 2, 3},
                              {7, 8, 9, 1, 2, 3, 4, 5, 6},
                              {2, 3, 4, 5, 6, 7, 8, 9, 1},
                              {5, 6, 7, 8, 9, 1, 2, 3, 4},
                              {8, 9, 1, 2, 3, 4, 5, 6, 7},
                              {3, 4, 5, 6, 7, 8, 9, 1, 2},
                              {6, 7, 8, 9, 1, 2, 3, 4, 5},
                              {9, 1, 2, 3, 4, 5, 6, 7, 8}};

    // Copying generic board in to main board.
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            board[i][j] = GenericBoard[i][j];
        }
    }

    /*
    * Blanking out 'blanks' amount of indices in the board by randomly setting
    * indices in the board to zero. If the loop randomly selects an index that is already
    * 0, it selects another index.
    */
    for (k = 1; k <= blanks; k++) {
        i = rand() % 10; // Selecting row index
        j = rand() % 10; // Selecting column index
        if (i != 0 && j != 0) { // Checking if that index is already zero.
            board[i][j] = 0; // Setting index to zero.
        } else {
            k--; // If it is already zero, amount of blanks selected, k, is reset.
        }
    }
}

/**
 * Permute rows
 */
void transform_permute_rows(int board[9][9]) {
    int row1swap;
    int row2swap;

    // Permute rows of first band.
    row1swap = (rand() % (2 - 0 + 1)) + 0;
    row2swap = (rand() % (2 - 0 + 1)) + 0;
    swap_rows(row1swap, row2swap, board);

    // Permute rows of second band.
    row1swap = (rand() % (5 - 3 + 1)) + 3;
    row2swap = (rand() % (5 - 3 + 1)) + 3;
    swap_rows(row1swap, row2swap, board);

    // Permute rows of third band.
    row1swap = (rand() % (8 - 6 + 1)) + 6;
    row2swap = (rand() % (8 - 6 + 1)) + 6;
    swap_rows(row1swap, row2swap, board);
}

/**
 * Permutes columns
 */
void transform_permute_columns(int board[9][9]) {
    int col1swap;
    int col2swap;

    // Permute rows of first band.
    col1swap = (rand() % (2 - 0 + 1)) + 0;
    col2swap = (rand() % (2 - 0 + 1)) + 0;
    swap_cols(col1swap, col2swap, board);

    // Permute rows of second band.
    col1swap = (rand() % (5 - 3 + 1)) + 3;
    col2swap = (rand() % (5 - 3 + 1)) + 3;
    swap_cols(col1swap, col2swap, board);

    // Permute rows of third band.
    col1swap = (rand() % (8 - 6 + 1)) + 6;
    col2swap = (rand() % (8 - 6 + 1)) + 6;
    swap_cols(col1swap, col2swap, board);
}

/**
 * Permutes on main diagonal
 */
void transform_flip_main_diagonal(int board[9][9]) {
    int i; // Iterates through rows.
    int j; // Iterates through columns.
    int tmp[9][9]; // Copy of board.

    // Making a copy of the board.
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            tmp[i][j] = board[i][j];
        }
    }

    // Reflecting indices: j (column index) becomes i (row index).
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            board[i][j] = tmp[j][i];
            board[j][i] = tmp[i][j];
        }
    }
}

/**
 * Permutes on minor diagonal
 */
void transform_flip_minor_diagonal(int board[9][9]) {
    int i; // Iterates through rows.
    int j; // Iterates through columns.
    int tmp[9][9]; // Copy of board.

    // Making a copy of the board.
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            tmp[i][j] = board[i][j];
        }
    }

    // Reflecting indices: j (column index) becomes i (row index).
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            board[i][j] = tmp[8 - j][8 - i];
            board[8 - j][8 - i] = tmp[i][j];
        }
    }
}

/**
 * Print sudoku board in user friendly fashion.
 */
int print_sudoku_board(int board[9][9]) {
    printf("Function print_sudoku_board not implemented.");
}

/**
 * Function to read user inputted boards.
 *
 * Runs by interpreting the user file as a board, ignoring everything
 * after the 9th line and 9th character of the file.
 *
 * Returns 0 if everything is a success and the file has been read.
 * Returns -1 if the file cannot be opened.
 * Returns -2 of an invalid character has been read.
 * Returns -3 if there aren't enough lines or characters.
 */
int read_sudoku_board(const char file_name[], int board[9][9]) {
    FILE *file;
    file = fopen(file_name, "r");

    if (file == NULL) {
        //returns -1 if there was an error opening the file
        return -1;
    }

    int i; // Iterate through rows.
    int j; // Iterate through columns.
    int line_tracker = 0; //tracks which line you've looped through
    int character_tracker = 0; //tracks how many characters are in each line
    char temp_line[13];

    while (fgets(temp_line, 12, file) != NULL) {
        //loops through the first 9 lines of the file
        line_tracker++;
        i = line_tracker - 1;

        if (line_tracker > 9) {
            //ensures it only reads the first 9 lines
            break;
        }

        for (j = 0; j < 9; ++j) {
            //loops through the first 9 indexes of the line copied to the temp_line variable
            // Then adds them to board[][]

            if (temp_line[j] > '0' && temp_line[j] <= '9') {
                //if it's a valid digit
                board[i][j] = (int) (temp_line[j] - '0');
                character_tracker++;
            } else if (temp_line[j] == '0' || temp_line[j] == '-') {
                //if it's a zero or '-'
                board[i][j] = 0; // Setting the board = to zero at that index.
                character_tracker++;
            } else {
                //Not a valid number
                return -2;
            }
        }
        if (character_tracker < 9) {
            return -3; // Not enough characters
        }
    }
    fclose(file);

    if (line_tracker < 9) {
        return -3; // Not enough lines.
    }

    return 0; // Success
}

/**
 * Saves the board to a file.
 *
 * Returns -1 if reading was unsuccessful.
 */
int write_sudoku_board(const char file_name[], int board[9][9]) {
    FILE *file;

    file = fopen(file_name, "w");

    if (file == NULL) {
        //returns -1 if there was an error opening the file
        return -1;
    }

    int i; // Iterates through rows
    int j; // Iterates through columns

    for (i = 0; i < 9; i++) { // Rows
        for (j = 0; j < 9; j++) { // Columns

            if (board[i][j] > 9 || board[i][j] < 0) {
                // Checks if index is a valid number
                return -2;
            }

            if (board[i][j] != 0) {
                // If it is not zero, print the index
                fprintf(file, "%d", board[i][j]);
            } else {
                //if the index equals 0, print "-"
                fprintf(file, "-");
            }
        }

        fprintf(file, "\n"); // Print new line as normal.
    }

    fclose(file);
    return 0; // Success
}
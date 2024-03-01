#include <stdio.h>
#include <stdbool.h>

#define N 9    // Size of the Sudoku puzzle
int count = 0; // Global count that will be used to store the number of iterations

// Function that will print out the board given an 9*9 2-D array as input
void print(int grid[N][N])
{
    printf("\n");
    for (int row = 0; row < N; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf(" -------------------------------\n");
        }

        for (int col = 0; col < N; col++)
        {

            if (col % 3 == 0 && col != 0)
            {
                printf(" | ");
            }

            printf(" %d ", grid[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
 Function that will check if a given number from 1-9 is valid to be placed in a given block.
 This function checks three main conditions: whether the choice is in any row, column, or subgrid.
*/
bool isValid(int grid[N][N], int row, int col, int choice)
{
    // Check row for the choice
    for (int i = 0; i < N; i++)
    {
        if (grid[row][i] == choice)
        {
            return false; // If the choice already exists in the row it is not valid
        }
    }

    // Check column for the choice
    for (int i = 0; i < N; i++)
    {
        if (grid[i][col] == choice)
        {
            return false; // If the choice already exists in the column, it is not valid
        }
    }

    // Check 3x3 subgrid for the choice
    int startRow = row - row % 3; // Determine the start row index of the subgrid
    int startCol = col - col % 3; // Determine the start column index of the subgrid
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == choice)
            {
                return false; // If the choice already exists in the subgrid, it is not valid
            }
        }
    }

    return true; // If the choice passes all checks, it is valid
}

bool solveSudoku(int grid[N][N], int row, int col)
{
    count++; // Increment the count every time that the function is called

    // Base case that is implying that the end of the grid has been reached thus the puzzle is solved
    if (row == 9)
    {
        return true;
    }

    // If the current column is 9 then we move to the next row and start from the first column
    if (col == 9)
    {
        return solveSudoku(grid, row + 1, 0); // Move to the next row
    }

    // If the cell is already filled move to the next column
    if (grid[row][col] != 0)
    {
        return solveSudoku(grid, row, col + 1); // Skip the blocks that are filled with a non-zero
    }

    // Try all possible numbers for the a given cell
    for (int choice = 1; choice <= 9; choice++)
    {
        // Check if the current choice is valid for the current cell
        if (isValid(grid, row, col, choice))
        {
            grid[row][col] = choice; // Temporarily assign the cell with the choice

            // Recursively try to solve the Sudoku starting from the next column
            if (solveSudoku(grid, row, col + 1))
            {
                return true; // Found a valid solution
            }

            grid[row][col] = 0; // Backtrack if the current choice leads to a dead end, reset the cell to 0
        }
    }

    return false; // There was not a valid number found for this cell thus backtrack further
}

int main()
{
    int grid[N][N] = {
        {0, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 6, 0, 0, 0, 0, 3},
        {0, 7, 4, 0, 8, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 2},
        {0, 8, 0, 0, 4, 0, 0, 1, 0},
        {6, 0, 0, 5, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 7, 8, 0},
        {5, 0, 0, 0, 0, 9, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 4, 0}};

    printf("The input Sudoku puzzle:\n");
    // Assuming 'print' is a function defined to print the grid

    print(grid);
    if (solveSudoku(grid, 0, 0))
    {
        // If the puzzle is solved:
        printf("Solution found after %d iterations:\n", count);
        print(grid);
    }
    else
    {
        printf("No solution exists.");
    }

    return 0;
}

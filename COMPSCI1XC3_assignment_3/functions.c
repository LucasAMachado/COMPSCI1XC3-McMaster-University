#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateMatrix(int rows, int cols, double matrix[rows][cols])
{
    // Iterate over each row of the matrix
    for (int i = 0; i < rows; i++)
    {
        // Within each row iterate over each column
        for (int j = 0; j < cols; j++)
        {
            // Assign a random double from -10.0 to 10.0 to the current matrix element
            matrix[i][j] = ((double)rand() / (double)(RAND_MAX)) * 20.0 - 10.0;
        }
    }
}

// Prints a matrix with specified dimensions
void printMatrix(int rows, int cols, double matrix[rows][cols])
{
    // Loop through each row.
    for (int i = 0; i < rows; i++)
    {
        // Loop through each column in the current row
        for (int j = 0; j < cols; j++)
        {
            // Print the current element with 6 decimal places
            printf("%.6f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Adds two matrices A and B and then stores result in the result matrix
void addMatrices(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double result[N1][M1])
{
    // Check if dimensions of both matrices are the same
    if ((N1 == N2) && (M1 == M2))
    {
        for (int i = 0; i < N1; i++)
        {
            for (int j = 0; j < M1; j++)
            {
                // Add corresponding elements and store in result
                result[i][j] = A[i][j] + B[i][j];
            }
        }
    }
    else
    {
        printf("Cannot add the matrices because of incompatible matrix sizes\n");
    }
}

// Subtracts matrix B from matrix A and stores in a result matrix
void subtractMatrices(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double result[N1][M1])
{
    // check that matrices A and B have the same dimensions
    if ((N1 == N2) && (M1 == M2))
    {
        for (int i = 0; i < N1; i++)
        {
            for (int j = 0; j < M1; j++)
            {
                // Subtract element of B from A and store in result
                result[i][j] = A[i][j] - B[i][j];
            }
        }
    }
    else
    {
        printf("Cannot subtract the matrices due to incompatible sizes\n");
    }
}

// Function to multiply two matrices and stores in result in result matrix
void multiplyMatrices(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double result[N1][M2])
{
    // checking to make sure that the matrix multiplication can be done
    if (M1 == N2)
    {
        // iterate through the rows of the matrix
        for (int rowA = 0; rowA < N1; rowA++)
        {
            // iterate through the cols of the matrix
            for (int colB = 0; colB < M2; colB++)
            {
                double sum = 0.0;
                /*
                iterate along the rows and down the columns to perform the multiplication
                by multiplying the values and then adding them up
                */
                for (int k = 0; k < M1; k++)
                {
                    sum += A[rowA][k] * B[k][colB];
                }
                // assign the sum to the result matrix
                result[rowA][colB] = sum;
            }
        }
    }
    else
    {
        printf("Cannot add the matrices because of incompatible matrix sizes\n");
    }
}

void solveLinearSystem(int N1, int M1, double A[N1][M1], int N2, int M2, double B[N2][M2], double x[N1][M2])
{
    /*
    Check if the dimesnsions are right to be able to sovle the linear system,
    if not then we will print a message saying that we cannot solve the system becuase of this
    */
    if (N1 == M1 && N1 == N2 && M2 == 1)
    {
        // initalize an augmented matrix that holds matrix A and the vector B
        double augmentedMatrix[N1][M1 + 1];

        // use a nested for loop to create the augmented matrix by adding the values to the matrix
        for (int row = 0; row < N1; row++)
        {
            for (int col = 0; col < M1; col++)
            {
                augmentedMatrix[row][col] = A[row][col];
            }
            // Setting b as the last column in the augmented matrix,
            //  after filling in the values from matrix A
            augmentedMatrix[row][M1] = B[row][0];
        }

        // Forward elimination to put the augmented matrix in an upper triangular form
        for (int pivotRow = 0; pivotRow < N1; pivotRow++)
        {
            // Check if the pivot element is 0 if it is 0 then there will be division by zero
            // thus we cannot do that
            if (augmentedMatrix[pivotRow][pivotRow] != 0)
            {
                // Normalize the pivot row by dividing by the pivot element
                double pivot = augmentedMatrix[pivotRow][pivotRow];
                for (int col = pivotRow; col <= M1; col++)
                {
                    augmentedMatrix[pivotRow][col] /= pivot;
                }

                // Eliminate elements below the pivot to create zeros
                for (int elimRow = pivotRow + 1; elimRow < N1; elimRow++)
                {
                    double factor = augmentedMatrix[elimRow][pivotRow];
                    for (int col = pivotRow; col <= M1; col++)
                    {
                        augmentedMatrix[elimRow][col] -= factor * augmentedMatrix[pivotRow][col];
                    }
                }
            }
            else
            {
                printf("Math error a zero pivot the solution may not be correct\n");
            }
        }

        // Back substitution to solve for variables
        for (int row = N1 - 1; row >= 0; row--)
        {
            // Initialize with the value from the augmented matrix
            x[row][0] = augmentedMatrix[row][M1];
            for (int col = row + 1; col < N1; col++)
            {
                // subtract the known variables
                x[row][0] -= augmentedMatrix[row][col] * x[col][0];
            }
            // make sure that the row is normalized
            if (augmentedMatrix[row][row] != 1)
            {
                x[row][0] /= augmentedMatrix[row][row];
            }
        }
    }
    else
    {
        printf("Incompatible dimensions.\n");
    }
}

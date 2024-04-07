#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <time.h>

int main(int argc, char *argv[])
{
    // Check if the number of arguments is correct
    if (argc < 6 || argc > 7)
    {
        printf("Usage: %s nrowsA ncolsA nrowsB ncolsB <operation> [print]\n", argv[0]);
        return 1;
    }

    // Creating variables based on the input form the command line
    int nrowsA = atoi(argv[1]);
    int ncolsA = atoi(argv[2]);
    int nrowsB = atoi(argv[3]);
    int ncolsB = atoi(argv[4]);
    char *operation = argv[5];

    // Seed the random number generator
    srand(time(NULL));

    // Initalize two sizes for matrix A and matrix B
    double matrixA[nrowsA][ncolsA];
    double matrixB[nrowsB][ncolsB];

    // Fill in matrix A and matrix B with random values
    generateMatrix(nrowsA, ncolsA, matrixA);
    generateMatrix(nrowsB, ncolsB, matrixB);

    // Checking which operation the user wants to perform (add)
    if (strcmp(operation, "add") == 0)
    {
        // Initializing the side for the result matrix
        double resultMatrix[nrowsA][ncolsA];

        // Calling the add matrices funtion to add matrix A and B
        addMatrices(nrowsA, ncolsA, matrixA, nrowsB, ncolsB, matrixB, resultMatrix);

        /*
        Check if the user wants to print the result matrix,
        and that the matrix addition is possible, if so
        then print out the matrix A and B and the result matrix
        */
        if (argc == 7 && strcmp(argv[6], "print") == 0 && (nrowsA == nrowsB) && (ncolsA == ncolsB))
        {
            printf("Matrix A:\n");
            printMatrix(nrowsA, ncolsA, matrixA);

            printf("\nMatrix B:\n");
            printMatrix(nrowsB, ncolsB, matrixB);

            printf("\nResult of A + B:\n");
            printMatrix(nrowsA, ncolsA, resultMatrix);
        }
    }
    // Checking which operation the user wants to perform (subtract)
    else if (strcmp(operation, "subtract") == 0)
    {
        // Initializing the side for the result matrix
        double resultMatrix[nrowsA][ncolsA];
        // Calling the function to subtract matrix A and B
        subtractMatrices(nrowsA, ncolsA, matrixA, nrowsB, ncolsB, matrixB, resultMatrix);

        /*
        Check if the user wants to print the result matrix,
        and that the matrix subtraction is possible, if so
        then print out the matrix A and B and the result matrix
        */
        if (argc == 7 && strcmp(argv[6], "print") == 0 && (nrowsA == nrowsB) && (ncolsA == ncolsB))
        {
            printf("Matrix A:\n");
            printMatrix(nrowsA, ncolsA, matrixA);

            printf("\nMatrix B:\n");
            printMatrix(nrowsB, ncolsB, matrixB);

            printf("\nResult of A - B:\n");
            printMatrix(nrowsA, ncolsA, resultMatrix);
        }
    }
    // Checking which operation the user wants to perform (multiply)
    else if (strcmp(operation, "multiply") == 0)
    {
        // Initializing the side for the result matrix
        double resultMatrix[nrowsA][ncolsB];

        // call the multiply matrices function
        multiplyMatrices(nrowsA, ncolsA, matrixA, nrowsB, ncolsB, matrixB, resultMatrix);

        /*
        Check if the user wants to print the result matrix,
        and that the matrix addtion is possible, if so
        then print out the matrix A and B and the result matrix
        */
        if (argc == 7 && strcmp(argv[6], "print") == 0 && (ncolsA == nrowsB))
        {
            printf("Matrix A:\n");
            printMatrix(nrowsA, ncolsA, matrixA);
            printf("\nMatrix B:\n");
            printMatrix(nrowsB, ncolsB, matrixB);

            printf("\nResult of A * B:\n");
            printMatrix(nrowsA, ncolsB, resultMatrix);
        }
    }

    // Checking which operation the user wants to perform (solve)
    else if (strcmp(operation, "solve") == 0)
    {
        //initialized vector to store the solution
        double resultVector[nrowsA][1]; 

        // Call the solveLinearSystem function
        solveLinearSystem(nrowsA, ncolsA, matrixA, nrowsB, ncolsB, matrixB, resultVector);

        /*
        Check if the user wants to print the result and 
        that the input matrices are valid; if so, then print out the matrices A and B and the result matrix
        */
        if ((argc == 7 && strcmp(argv[6], "print") == 0) && (nrowsA == ncolsA && nrowsA == nrowsB && ncolsB == 1))
        {
            printf("Matrix A:\n");
            printMatrix(nrowsA, ncolsA, matrixA);

            printf("\nMatrix B:\n");
            printMatrix(nrowsB, ncolsB, matrixB); 

            // print out the solution 
            printf("\nResult of x=B/A:\n");
            for (int i = 0; i < nrowsA; i++)
            {
                printf("%f\n", resultVector[i][0]);
            }
        }
    }

    else
    {
        printf("Invalid operation specified.\n");
    }

    return 0;
}

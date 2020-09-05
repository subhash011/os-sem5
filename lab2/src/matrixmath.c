#include "../include/matrixmath.h"
#include "../include/transform.h"
#include <stdio.h>

/*
 * takes two matrices A and  B and puts the product in the matrix
 * pointed to by P
 * */
int multiply(matrix* P, matrix A, matrix B) {
    int rowsA = A -> rows, colsA = A -> cols;
    int rowsB = B -> rows, colsB = B -> cols;
    /*initialise the matrix*/
    *P = initialise(rowsA, colsB);
    if(colsA != rowsB) {
        fprintf(stderr, "\nRows and columns of the matrices are not compatible");
        return 1;
    }
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                (*P)->array[i][j] += A -> array[i][k] * B -> array[k][j];
            }
        }
    }
    return 0;
}

/*
 * elementwise product of two matrices A and B and put the product in the
 * matrix pointed to by P this is used for convolution
 * */
int elementwiseProduct(matrix* P, matrix A, matrix B) {
    int rowsA = A -> rows, colsA = A -> cols;
    int rowsB = B -> rows, colsB = B -> cols;
    *P = initialise(rowsA, rowsB);
    if(rowsA != rowsB || colsB != colsA) {
        fprintf(stderr, "\nRows and columns of the matrices are not compatible");
        return 1;
    }
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            (*P)->array[i][j] += A -> array[i][j] * B -> array[i][j];
        }
    }
    return 0;
}

/*
 * sum of all elements of a matrix
 * */

int sumOfAllElements(matrix mat) {
    int ans = 0;
    for (int i = 0; i < mat -> rows; ++i) {
        for (int j = 0; j < mat -> cols; ++j) {
            ans += mat -> array[i][j];
        }
    }
    return ans;
}

/*
 * take a pad side and pad the matrix toPad with
 * zeros so as to obtain same dimensions after the convolution*/
void zeroPadding(matrix *toPad, int padSize) {
    int rows = (*toPad) -> rows + 2 * padSize;
    int cols = (*toPad) -> cols + 2 * padSize;
    matrix newMatrix = allocateMemory();
    newMatrix = initialise(rows, cols);
    copyMatrix(&newMatrix, padSize, padSize, *toPad);
    (*toPad) = initialise(rows, cols);
    (*toPad) = newMatrix;
}
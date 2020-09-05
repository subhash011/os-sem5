#include "../include/matrixmath.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * allocate space for 2D array with dimensions rows x cols
 * */
uint8 **allocateArray(int rows, int cols) {
    uint8 **arr = (uint8 **)malloc(rows * sizeof(uint8 *));
    for (int i = 0; i < rows; i++) {
        arr[i] = (uint8 *)malloc(cols * sizeof(uint8));
    }
    return arr;
}

/*
 * allocate memory for matrix but here array has no memory
 * */
matrix allocateMemory() {
    matrix mat = (matrix)malloc(sizeof(matrix));
    mat -> rows = 0;
    mat -> cols = 0;
    return mat;
}

/*
 * initialise a matrix, allocate space for matrix and
 * allocate space for array in that matrix
 * */
matrix initialise(int rows, int cols) {
    matrix mat = allocateMemory();
    mat -> rows = rows;
    mat -> cols = cols;
    uint8 **arr = allocateArray(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j]=0;
        }
    }
    mat -> array = arr;
    return mat;
}

/*
 * print matrix
 * */
void printStruct(matrix m) {
    printf("Number or rows: %d\n", m -> rows);
    printf("Number or cols: %d\n", m -> cols);
    printf("Matrix: \n");
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            printf("%hhu ", m->array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
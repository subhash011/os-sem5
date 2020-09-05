#ifndef MATRIXMATH_H
#define MATRIXMATH_H
#include "matrix.h"

int multiply(matrix* P, matrix A, matrix B);
int elementwiseProduct(matrix* P, matrix A, matrix B);
int sumOfAllElements(matrix mat);
void zeroPadding(matrix *toPad, int padSize);
#endif

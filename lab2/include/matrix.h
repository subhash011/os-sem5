#ifndef MATRIX_H
#define MATRIX_H

typedef unsigned char uint8;

struct matrix {
    int rows;
    int cols;
    uint8 **array;
};

typedef struct matrix * matrix;

matrix allocateMemory();
matrix initialise(int rows, int cols);
void printStruct(matrix m);
uint8 **allocateArray(int rows, int cols);


#endif

#include "../include/matrixmath.h"


/*
 * copy child matrix to the parent matrix from index
 * startRow to startCol
 * */
void copyMatrix(matrix *parent, int startRow, int startCol, matrix child) {
    uint8 **array = (*parent) -> array;
    int childRows = child -> rows;
    int childCols = child -> cols;
    for (int i = startRow; i < startRow + childRows; ++i) {
        for (int j = startCol; j < startCol + childCols; ++j) {
            array[i][j] = child -> array[i - startRow][j - startCol];
        }
    }
    (*parent)->array = array;
}

/*
 * get submatrix from src into dest depending on other params*/
void getSubmatrix(matrix *dest, int startRow, int numRows, int startCol, int numCols, matrix src) {
    for (int i = startRow; i < startRow + numRows; ++i) {
        for (int j = startCol; j < startCol + numCols; ++j) {
            (*dest) -> array[i - startRow][j - startCol] = src -> array[i][j];
        }
    }
}

/*
 * convolution function
 * */
matrix convolve(matrix kernel, matrix toConvolve) {
    int kernelSize = kernel -> rows;
    int beforeConvolveRows = toConvolve -> rows;
    int beforeConvolvecols = toConvolve -> cols;
    int padSize = kernelSize/2;
    zeroPadding(&toConvolve, padSize);//pad the matrix to retain dimensions
    matrix  answer = initialise(beforeConvolveRows, beforeConvolvecols);
    matrix multiplierA = initialise(kernelSize, kernelSize);
    matrix productMatrix = initialise(kernelSize, kernelSize);
    for (int i = 0; i <= toConvolve -> rows - kernelSize; ++i) {
        for (int j = 0; j <= toConvolve -> cols - kernelSize; ++j) {
            //get submatrix to convolve with the kernel
            getSubmatrix(&multiplierA, i, kernelSize, j, kernelSize, toConvolve);
            //convolve the submatrix with kernel
            elementwiseProduct(&productMatrix, multiplierA, kernel);
            //take the sum and put it in the answer matrix, this ends one convolution
            answer -> array[i][j] = sumOfAllElements(productMatrix);
        }
    }
    return answer;
}

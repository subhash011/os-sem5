#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
matrix convolve(matrix kernel, matrix toConvolve);
void copyMatrix(matrix *parent, int startRow, int startCol, matrix child);
#endif

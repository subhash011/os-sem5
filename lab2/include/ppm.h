#ifndef PPM_H
#define PPM_H

#include <assert.h>
#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned int uint;

typedef struct {
    uint w, h;
    uint8 *data;
} Image;

uint newImage(Image *pImg, uint w, uint h);
void freeImage(Image *pImg);
int readPPM(FILE *f, Image *pImg);
void writePPM(char *filename, Image *pImg);
void matrixToImage(matrix mat, Image *img);
void imageToMatrix(matrix* mat, Image img);
#endif

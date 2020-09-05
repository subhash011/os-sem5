#include "../include/matrixmath.h"
#include "../include/ppm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*allocate memory to image and if successfull return sie of the image*/
uint newImage(Image *pImg, uint w, uint h)
{
    uint size = w * h * 3;
    if (!pImg) return 0;
    pImg->data = malloc(size);
    pImg->w = pImg->data ? w : 0; pImg->h = pImg->data ? h : 0;
    if (!pImg->data) {
        fprintf(stderr,
                "Allocation of %u bytes for image data failed!\n", size);
        return 0;
    }
    return size;
}

/*free the allocated memory if any error occurs*/
void freeImage(Image *pImg)
{
    if (!pImg) return;
    free(pImg->data);
    pImg->data = 0;
}

/*
 * read ppm file
 * returns 1 on success
 * */
int readPPM(FILE *f, Image *pImg)
{
    char buffer[32] = ""; uint w = 0, h = 0, t = 0, size = 0, i = 0;
    if (!pImg) return 0;


    /* parse header */
    if ((i = 1, !fgets(buffer, sizeof buffer, f))
        || (i = 2, strcmp(buffer, "P6\n") != 0) // header should be P6
        || (i = 3, fscanf(f, "%u %u %u", &w, &h, &t) != 3)
        || (i = 4, t != 255)) {
        fprintf(stderr, "Not a PPM image! (%u)\n", i);
        return -1;
    }

    /*allocate appropriate memory*/
    if (!(size = newImage(pImg, w, h))) return -1;

    /*read data*/
    if (fread(pImg->data, 1, size, f) != size) {
        fprintf(stderr, "Not enough data in PPM image!\n");
        freeImage(pImg);
        return -1;
    }
    /*success*/
    return 0;
}

/*
 * write to ppm file
 * */
void writePPM(char *outFile, Image *pImg)
{
    FILE*  f;
    if (!(f = fopen(outFile, "wb"))) {
        fprintf(stderr, "Cannot create output file '%s'!, check if you have specified the output path and the directory exists\n", outFile);
        return;
    }
    if (!pImg || !pImg->data) return;
    fprintf(f, "P6\n%u %u 255\n", pImg->w, pImg->h);
    uint size = pImg->w * pImg->h * 3, i;
    for (i = 1; i <= size; i += 3) {
        fprintf(f, "%c%c%c",
                pImg->data[i + 0], pImg->data[i + 1], pImg->data[i + 2]);
    }
    fclose(f);
}

/*convert the Image struct to matrix struct
 * because image struct was obtained throught the reference
 * https://stackoverflow.com/questions/42544773/convolution-for-edge-detection-in-c
 * so we converted it to suit our operations and declarations
 * */
void imageToMatrix(matrix* mat, Image img) {
    uint8 *array = img.data;
    int rows = img.h;
    int cols = img.w;
    *mat = initialise(rows, cols);
    uint8 *tdArray = (uint8 *)malloc(rows * cols * sizeof(uint8));
    for (int i = 0; i < rows * cols * 3; i += 3) {
        tdArray[i/3] = (array[i]*0.33 + array[i + 1]*0.33 + array[i + 2]*0.33);
    }
    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            index = cols * i + j;
            (*mat) -> array[i][j] = tdArray[index];
        }
    }
}

/*
 * convert our matrix back to Image struct to write back to a ppm file*/
void matrixToImage(matrix mat, Image *img) {
    int rows = mat -> rows;
    int cols = mat -> cols;
    newImage(img, cols, rows);
    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            uint8 value = mat -> array[i][j];
            img -> data[index] = value;
            index++;
            img -> data[index] = value;
            index++;
            img -> data[index] = value;
            index++;
        }
    }
}
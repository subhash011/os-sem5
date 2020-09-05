#include <stdio.h>
#include <stdlib.h>
#include "../include/matrixmath.h"
#include "../include/transform.h"
#include "../include/ppm.h"

void assign_array_to_matrix(matrix* mat, uint8 (*array)[3]) {
    for (int i = 0; i < (*mat)->rows; ++i) {
        for (int j = 0; j < (*mat)->cols; ++j) {
            (*mat) -> array[i][j] = array[i][j];
        }
    }
}

int main(int argc, char **argv)
{
    FILE *f;


    char *inFile = argv[1], *outFile = argv[2];

    int transformation = 2;

    if(argc >= 4) {
        transformation = atoi(argv[3]);
    }

    if (!(f = fopen(inFile, "rb"))) {
        fprintf(stderr, "Cannot open input file '%s'!\n", inFile);
        return -1;
    }

    Image img = { 0, 0, NULL };
    if (readPPM(f, &img)) return -1;//read the ppm file into the Image struct
    fclose(f);

    /*define our kernels for edge detection*/
    uint8 kernels[2][3][3] =
            {
                    { {0, 0, 0}, {0, 1, 0}, {0, 0, 0} }, // identity operation
                    { {0, -1, 0}, {-1, 2, -1}, {0, -1, -1} }, //edge detector
            };

    /*store incoming image in this matrix*/
    matrix image_in;
    Image image = { 0, 0, NULL };

    /*first transformation is the conversion from RGB to greyscale*/

    /*take the input image and store it in struct matrix
     * this function also internally converts RGB to greyscale
     * takes r, g, b and uses the formula (0.33*r + 0.33*g + 0.33b)
     * and stores the output of all such operations in a 2D matrix
     * */
    imageToMatrix(&image_in, img);

    /*assign kernel*/
    matrix kernel = initialise(3, 3);
    assign_array_to_matrix(&kernel, kernels[1]);

    /*second transformation is convoluting the image with a kernel (edge detector)*/

    /*now the image_in matrix contains the grayscale image, this function
     * runs the edge detector on that grayscale image
     * */
    matrix mans = NULL;
    if(transformation == 2) {
        mans = convolve(kernel, image_in);
        /*this function take the matrix after the convolution and changes it to the
         * struct Image for writing back to the ppm file
         * */
        matrixToImage(mans, &image);
    } else {
        matrixToImage(image_in, &image);
    }

    /*write to the ppm file*/
    writePPM(outFile, &image);
    return 0;
}
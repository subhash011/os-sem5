### Default input, output paths and the make utilty
 -  For input, in the current directory create a folder named **inppm** and add images to it.
 -  The make utility creates the output directory as **outppm**
 -  For running test cases, the input directory can contain ppm files with any name.
 -  The 'make run' command uses **inppm/input.ppm** as input and writes the output to **outppm/output.ppm**.
 -  The 'make prepare' command runs all prerequisite targets and prompts the user for the input file path and the output file path.
 -  'make tests' or 'make test' takes all the images in the **inppm** directory, performs both the transformations and writes the output to the **outppm** directory.
 -  'make testi' (replace the last 'i' with a number in the range 1 to number of images in the input directory) takes the ith image in the input directory, , performs both the transformations and writes the output to the **outppm** directory.
 -  'make T1' runs RGB-Grayscale and input path is input/input.ppm, output path is outppm/output.ppm
 -  'make T2' runs edge detection and input path is input/input.ppm, output path is outppm/output.ppm
 -  'make liba' generates static libraries in the folder lib/
 -  'make libso' generate shared objects in the folder libs/
 -  'make clean' removes object files, libraries and output images if any.

### Image processor
 -  The statically generate binary is stored as imageprocess in the bin directory and can be obtained by 'make build'.
 -  This executable needs three inputs
    1. Input file path (must be a ppm image).
    2. Output file path (directory to which the file has to be written must exist).
    3. which transformation to perform
        1. 1 means RGB - Grayscale
        2. 2 means edge detection
        3. by default both are performed if neither 1 or two is passed
 -  The binary generated from shared objects is stored as imageprocess_so in the bin directory and can be obtainer by 'make buildso'.
 
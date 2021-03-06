### If any of the commands fail, check the following
 -  Check if the testscript.sh has executable permission
 -  Run 'make inppm', add input.ppm and try again.

#### default input path assumed = inppm/input.ppm
#### default output path assumed = outppm/output.ppm

### Default input, output paths and the make utilty
 -  For input, in the current directory create a folder named **inppm** and add images to it **(atleast one image must be named input.ppm)**.
 -  The make utility creates the output directory as **outppm** and the output for tests are written to **testout**
 -  For running test cases, the input directory can contain ppm files with any name.
 -  The 'make run' command uses **inppm/input.ppm** as input and writes the output to **outppm/output.ppm**.
 -  The 'make prepare' prompts the user for the input file path and the output file path. The input and output paths are saved, now the user can run 'make run' to get the output.
 -  'make run' after 'make prepare' uses the input from the user and running 'make run' again defaults back to the default paths.
 -  'make tests' or 'make test' takes all the images in the **inppm** directory, performs both the transformations and writes the output to the **testout** directory.
 -  'make testi' (replace the last 'i' with a number in the range 1 to number of images in the input directory) takes the ith image in the input directory, , performs both the transformations and writes the output to the **testout** directory.
 -  'make T1' runs RGB-Grayscale and input path is **input/input.ppm**, output path is **outppm/output.ppm**
 -  'make T2' runs edge detection and input path is **input/input.ppm**, output path is **outppm/output.ppm**
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
 

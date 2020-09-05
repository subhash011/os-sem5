cmake_minimum_required(VERSION 3.17)
project(git)

set(CMAKE_CXX_STANDARD 14)

file(GLOB LAB1 "lab1/*.c")
file(GLOB LAB2 "lab2/*.c")

add_executable(lab1 ${LAB1} lab2/include/transformations.h lab2/include/ppm.h)
add_executable(lab2 ${LAB2} lab2/matrix.c lab2/include/matrix.h lab2/include/matrixmath.h lab2/matrixmath.c lab2/transformations.c lab2/ppm.c)

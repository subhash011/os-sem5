cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

file(GLOB LAB2 "src/*.c")

add_executable(lab2 ${LAB2} src/matrix.c include/matrix.h include/matrixmath.h include/transform.h src/matrixmath.c src/transform.c src/ppm.c)

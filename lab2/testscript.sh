#!/bin/bash

inputs=($(find ./inppm -type f -name "*.ppm"))

test_number="${1: -1}"

if [ -z "$1" ]; then
  for input in "${inputs[@]}"
  do
     ./bin/imageprocess "$input" "testout/$(basename "$input" ".ppm").ppm" 2
  done
else
   ./bin/imageprocess "${inputs[$(($test_number - 1))]}" "testout/$(basename "${inputs[$(($test_number - 1))]}" ".ppm").ppm" 2
fi
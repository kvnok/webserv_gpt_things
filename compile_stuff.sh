#!/bin/bash

# Directory containing your .cpp files
src_dir="srcs"

# Compile each .cpp file into the root directory
for file in ${src_dir}/*.cpp; do
    filename=$(basename -- "$file")
    filename_no_ext="${filename%.*}"
    g++ -o "${filename_no_ext}" "${file}" -lpthread
    chmod +x "${filename_no_ext}"
done

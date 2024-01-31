#!/bin/sh
mkdir -p build/
rm -rf build/CMakeFiles/
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/release/

(cd build/release/ && make)

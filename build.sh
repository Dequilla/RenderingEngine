#!/bin/sh
# Ensure folder exists
mkdir -p build/

# Clear
#rm -rf build/release/

cmake -DCMAKE_BUILD_TYPE=Release -DRENDERER_OPENGL=ON -S . -B build/release/

(cd build/release/ && make)

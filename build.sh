#!/bin/sh
mkdir -p build/
rm -rf build/release/
cmake -DCMAKE_BUILD_TYPE=Release -DRENDERER_OPENGL=ON -S . -B build/release/

(cd build/release/ && make)

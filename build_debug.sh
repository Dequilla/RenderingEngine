#!/bin/bash
mkdir -p build/
rm -rf build/debug/
cmake -DCMAKE_BUILD_TYPE=Debug -DRENDERER_OPENGL=ON -S. -B./build/debug

(cd build/debug/ && make)

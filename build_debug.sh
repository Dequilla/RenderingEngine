#!/bin/bash
mkdir -p build/
rm -rf build/CMakeFiles/
cmake -DCMAKE_BUILD_TYPE=Debug -S. -B./build/debug

(cd build/debug/ && make)
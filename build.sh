#! /bin/bash

cmake --build build/ -j$((`nproc`+1));
cd build/src/;
mv asteroids ../../;

#! /bin/bash

cmake --build build/;
cd build/src/;
mv asteroids-sdl ../../;

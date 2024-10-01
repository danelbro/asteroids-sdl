#! /bin/bash

cmake --build build/ -j$((`nproc`+1))
cp -r data/ build/src/data

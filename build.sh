#! /bin/bash

cmake --build out/build/$1 -j$((`nproc`+1))

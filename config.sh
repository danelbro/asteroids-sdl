#! /bin/bash

mkdir -p build
cd build
cmake -DBUILD_SHARED_LIBS=OFF -DSDL_TEST_LIBRARY=OFF ..

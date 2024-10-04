#! /bin/bash

mkdir -p out/build/$1
cd out/build/$1
cmake -DCMAKE_BUILD_TYPE=$1 -DBUILD_SHARED_LIBS=OFF -DSDL_TEST_LIBRARY=OFF -DSDLTTF_VENDORED=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../../../
cp compile_commands.json ../../../

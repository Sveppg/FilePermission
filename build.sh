#!/bin/bash

mkdir HEADER_FILES
mv *.h HEADER_FILES/

mkdir SOURCE_FILES
mv *.c SOURCE_FILES/

mkdir build/
cd build/ 
cmake ..
make
cd ..
./build/executable "$@"

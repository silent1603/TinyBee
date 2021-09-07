#! /bin/bash
if [ -d "./build" ]; then
    cd build
else
    mkdir build && cd build
fi
conan install ..
#fix for manajro arch
conan install .. --build=missing 

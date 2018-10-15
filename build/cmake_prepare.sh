#!/bin/sh
rm -rf CMakeFiles
rm Makefile
rm CMakeCache.txt
rm cmake_install.cmake
cmake .. -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND"

#!/bin/sh
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../Toolchain-linux_mingw.cmake

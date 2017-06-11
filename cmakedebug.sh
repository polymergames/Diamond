#!/bin/bash

rm -r Debug
mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
make

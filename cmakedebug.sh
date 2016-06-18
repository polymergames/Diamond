#!/bin/bash

rm -r Debug
mkdir Debug
cd Debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

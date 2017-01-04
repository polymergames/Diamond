#!/bin/bash

rm -r Release
mkdir Release
cd Release
cmake ..
make

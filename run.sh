#!/bin/bash

name=${PWD##*/}
exe=$name.exe
if [ -e bin/$exe ]; then
    ./bin/$exe
else
    ./makeBuild.sh && ./run.sh
fi

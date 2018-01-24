#!/bin/bash

name=${PWD##*/}
mingw32-make $name -C ./build

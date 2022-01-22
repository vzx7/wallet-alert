#!/usr/bin/bash
# Compile and run

APP="wallet-alert"
ARGS=$*

mkdir -p build

g++ src/main.cc -o build/$APP && ./build/$APP $ARGS

exit 0
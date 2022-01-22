#!/usr/bin/bash
# Compile and run

APP="wallet-alert"
mkdir -p build
g++ src/main.cc -o build/$APP && ./build/$APP
exit 0
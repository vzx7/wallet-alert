#!/usr/bin/bash
# Compile and run

APP="wallet-alert"

g++ src/main.cc -o build/$APP && ./build/$APP
exit 0
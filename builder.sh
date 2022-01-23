#!/usr/bin/bash
# Compile and run

APP="wallet-alert"

mkdir -p build

g++ src/main.cpp -std=c++14 -pthread -o build/$APP

echo "Congratulations, successful build!!!"
exit 0
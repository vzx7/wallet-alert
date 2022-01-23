#!/usr/bin/bash
# Compile and run

APP="wallet-alert"

mkdir -p build

g++ src/main.cpp -pthread -fconcepts -o build/$APP

echo "Congratulations, successful build!!!"
exit 0
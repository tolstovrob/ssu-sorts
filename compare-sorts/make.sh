#!/bin/bash

clear
g++ -o sort_comparison ./main.cpp

if [ $? -eq 0 ]; then
    echo "Compiled successfully"
    echo
    ./sort_comparison data/input50000.txt data/input100000.txt data/input500000.txt data/input1000000.txt 
else
    echo "Compilation error"
fi
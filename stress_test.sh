#!/bin/bash
g++ stress_test.cpp -o stress  --std=c++11 -pthread  
./stress

#!/bin/bash

g++ main.cpp -std=c++17 -I/opt/homebrew/Cellar/sfml/2.5.1_1/include/ -o main -L /opt/homebrew/Cellar/sfml/2.5.1_1/lib/ -l sfml-graphics -l sfml-window -l sfml-system

#!/bin/bash

gcc -Wall -fpic -c datehack.c
ld -shared -o datehack.so datehack.o -ldl

LD_PRELOAD=./datehack.so date

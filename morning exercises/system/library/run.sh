#!/bin/bash

gcc -fpic -shared library.c -o library.so
gcc app.c -L"$PWD"/ -lrary -o app
ldd app
export LD_LIBRARY_PATH=$PWD/:$LD_LIBRARY_PATH
./app $1 $2

rm app
rm *.o
unset LD_LIBRARY_PATH

gcc app.c -L"$PWD"/ -Wl,-rpath="$PWD"/ -lrary -o app
ldd app
./app $1 $2

rm app
rm *.o

gcc -c app.c -o app.o
ld -rpath="$PWD"/ app.o -o app

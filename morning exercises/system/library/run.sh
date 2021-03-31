#!/bin/bash

gcc -g -m32 -fpic -shared library.c -o library.so
gcc -g -m32 app.c -L"$PWD"/ -lrary -Wl,--stats -Wl,--dll-verbose  -o app
ldd app
export LD_LIBRARY_PATH=$PWD/:$LD_LIBRARY_PATH
./app $1 $2

rm app
rm *.o
unset LD_LIBRARY_PATH

gcc -g -m32 app.c -L"$PWD"/ -Wl,-rpath="$PWD"/ -lrary -o app
ldd app
./app $1 $2

#GDB
# set environment variable
# set environment LD_LIBRARY_PATH=.
# set stop-on-solib-events 1 - stop if DSO load or unload

#### Set ld debug symbols
# sudo apt-get install libc6-dbg

#!/bin/bash
mkdir -p ./build/

gcc -Wall -Wextra -c chogger.c -o ./build/chogger.o
ar rcs ./build/libchogger.a ./build/chogger.o
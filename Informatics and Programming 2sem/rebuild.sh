#!/bin/sh

find . -name $1 | entr clang++ -fstandalone-debug --debug $1 -o $(echo "$1" | cut -f 1 -d '.')

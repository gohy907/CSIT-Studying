#!/bin/sh

path1=$(echo "${1%.*}")
echo "$1" | entr clang++ -fstandalone-debug --debug "$1" -o "$path1"

#!/bin/sh

path1=$(echo "${1%.*}")
dir=$(pwd)
input="${dir%/}"
result=$(basename "$input")
path2="${result}"/"${path1}"
gitignore="../.gitignore"
if ! grep -qxF "$path2" "$gitignore"; then
  (echo "$path2") >> $gitignore
fi

echo "$1" | entr clang++ -fstandalone-debug --debug "$1" -o "$path1"

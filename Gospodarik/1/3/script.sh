#!/bin/bash

directory="$PWD/dir"

files_list=$(find "$directory" -type f)

for file in "$directory"/*; do
  if [[ -x "$file" && "$file" == *.sh ]]; then
    echo "Cкрипт: $file"
    $file
  fi
done

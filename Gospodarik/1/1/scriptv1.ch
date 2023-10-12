#!/bin/bash
if [ -e file1.txt ] && [ -e file2.txt ]; then
  cat file1.txt > file2.txt
  echo "Содержимое файла file1.txt было записано в файл file2.txt"
else
  echo "Один из файлов не существует."
fi

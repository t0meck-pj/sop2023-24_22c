#!/bin/bash

# Wypisanie zawartości plików od początku do końca
echo "Zawartość plików od początku do końca:"
for file in "$@"; do
    echo "Plik: $file"
    cat "$file"
    echo
done

# Wypisanie zawartości plików od końca do początku
echo "Zawartość plików od końca do początku:"
for file in "$@"; do
    echo "Plik: $file"
    tac "$file"
    echo
done

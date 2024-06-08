#!/bin/bash

file_count=$(find . -maxdepth 1 -type f | wc -l)


if [ "$file_count" -gt 5 ]; then
    echo "W bieżącym katalogu jest więcej niż 5 plików."
else
    echo "W bieżącym katalogu jest 5 lub mniej plików."
fi

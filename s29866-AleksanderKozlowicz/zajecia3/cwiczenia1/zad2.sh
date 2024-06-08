#!/bin/bash

if [ -f "config.cfg" ]; then
    ./config.cfg

elif [ $# -eq 1 ]; then
    if [ -f "$1" ]; then
        ./$1
    else
        echo "Plik $1 nie istnieje."
    fi
else
    echo "Brak pliku config.cfg lub/i argumentu."
fi

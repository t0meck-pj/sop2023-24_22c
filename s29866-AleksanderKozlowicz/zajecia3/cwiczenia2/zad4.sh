#!/bin/bash


for plik in *.c; do    
    if [ -e "$plik" ]; then        
        bezRozszerzenia="${plik%.c}"        
        cc "$plik" -o "$bezRozszerzenia"
    fi
done

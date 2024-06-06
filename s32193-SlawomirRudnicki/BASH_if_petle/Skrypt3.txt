#!/bin/bash
var_name=$(basename "$0")

if [[ $var_name == *.sh ]]; then
    echo "Dziala"
elif [[ $var_name != *.sh ]]; then
    echo 'dziala 2'
    mv "$var_name" "$(basename "$var_name" .txt).sh"
fi 
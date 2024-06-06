#!/bin/bash

file_var='mleko.cfg'
alter_file_var='EAT-17.sh'

if [[ -f "$file_var" ]]; then
    bash "$file_var"
elif [[ -z ${var+alter_file_var} ]]; then
    bash "$alter_file_var"
else
    echo "Error"
fi

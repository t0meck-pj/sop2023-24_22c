#!/bin/bash
ls_array=($(ls))
ls_array_length=${#ls_array[@]}
for ((i=0; i < ls_array_length; i++)); do
    if [[ -f ${ls_array[i]} ]]; then
        echo "Prosze panstwa o to plik: ${ls_array[i]}"
    elif [[ -d ${ls_array[i]} ]]; then
        echo "Prosze panstwo o to katalog: ${ls_array[i]}"
    else
        echo "mleko"
    fi
        
done

#!/bin/bash

current_directory=($(ls))

for (( i=1; i<="$#"; i++ )); do
    if [[ ${current_directory[@]} =~ ${!i} ]]; then
        cat ${!i}
        tac ${!i} | rev #zadna z moich idei nie zadzialala, jesli bede mial czas, poprawie
    fi
done

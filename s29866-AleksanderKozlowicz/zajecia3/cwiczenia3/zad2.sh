#!/bin/bash

#coś mi tu nie zadziałało, mam taki błąd:
#./zad2.sh: linia 14: return: : wymagany argument numeryczny

fibonacci() {
    local n=$1

    if [ "$n" -le 1 ]; then
        echo "$n"
    else
        local a=$(fibonacci "$((n-1))")
        local b=$(fibonacci "$((n-2))")
        echo "$((a + b))"
    fi

	return "$result"
}


result=$(fibonacci 10)

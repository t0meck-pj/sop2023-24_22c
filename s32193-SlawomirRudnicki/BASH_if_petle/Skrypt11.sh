#!/bin/bash

colour () {
    if [[ $2 == "red" ]]; then
        echo -e "\e[31m$1 \e[0m"
    elif [[ $2 == "yellow" ]]; then
        echo -e "\e[33m$1 \e[0m" 
    elif [[ $2 == "green" ]]; then
        echo -e "\e[32m$1 \e[0m"
    elif [[ $2 == "black" ]]; then
        echo -e "\e[30m$1 \e[0m" 
    fi  
}
#!/bin/bash

fibonacci () {
    
    if [[ $1 == 0 ]]; then
        return 0
    elif [[ $1 == 1 ]]; then 
        return 1
    else
        return $(( $(fibonacci $(($1-1))) + $(fibonacci $(($1-1))) ))
        
    fi
}
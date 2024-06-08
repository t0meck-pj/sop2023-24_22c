#!/bin/bash
x=($(ls -l | grep '^-' | wc -l))

if [[ $x -gt $1 ]]; then
    echo "jest wiecej"
else
    echo "nie jest"
fi

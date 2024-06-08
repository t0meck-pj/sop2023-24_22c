#!/bin/bash
a=$(cat text.txt)
b="\e[31mSlawek\e[0m"
echo -e ${a//Slawek/$b}

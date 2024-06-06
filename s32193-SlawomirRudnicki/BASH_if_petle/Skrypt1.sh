#!/bin/bash
x=1
y=2
z=3
v=$(bash -c 'echo $#' _ x y z)
if [[ $v -ge 1 ]]; then
echo $x
else
echo "Nie podano parametrow"
fi
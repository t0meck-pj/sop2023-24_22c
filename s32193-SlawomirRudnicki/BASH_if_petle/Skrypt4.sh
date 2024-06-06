#!/bin/bash
file_number=$(ls -1 | wc -l)
echo $file_number

if [[ $file_number -gt 5 ]]; then
echo "mleko"
fi
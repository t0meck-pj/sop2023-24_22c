#!/bin/bash
ls_array=($(ls | grep "\.sh"))
length=${#ls_array[@]}
for (( i = 0; i < $length; i++ )); do 
    new_name=${ls_array[i]/".sh"/""}
    old_name=${ls_array[i]}

    cc ($old_name) -o ($new_name)
     
done

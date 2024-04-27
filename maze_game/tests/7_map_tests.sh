#!/bin/bash

echo -e "\n\n~~ Map Validation ~~\n"


echo -n "1. Testing map with mixed case valid inputs - "
timeout 0.2 ./maze ./mazes/valid/3_min_5x5.txt < ./inputs/6_valid_map.in > out
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "./outputs/5_valid_map.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "2. Testing map with mixed case valid and invalid inputs - "
timeout 0.2 ./maze ./mazes/valid/3_min_5x5.txt < ./inputs/7_invalid_map.in > out 
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "./outputs/6_invalid_map.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
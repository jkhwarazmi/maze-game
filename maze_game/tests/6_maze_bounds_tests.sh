#!/bin/bash

echo -e "\n\n~~ Bounds Testing ~~\n"


echo -n "1. Testing walking into walls in all directions - "
timeout 0.2 ./maze ./mazes/valid/3_min_5x5.txt < ./inputs/5_walls.in > out
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "./outputs/3_walls.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "2. Testing walking out of bounds in all directions - "
timeout 0.2 ./maze ./mazes/valid/5_no_walls_5x5.txt < ./inputs/12_bounds.in > out
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "./outputs/4_bounds.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
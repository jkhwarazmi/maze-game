#!/bin/bash

echo -e "\n\n~~ Loading Valid Mazes ~~\n"


echo -n "1. Testing largest maze - "
timeout 0.2 ./maze ./mazes/valid/2_max_100x100.txt > out
if grep -q "Maze ./mazes/valid/2_max_100x100.txt (100x100) successfully loaded" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "2. Testing smallest maze - "
timeout 0.2 ./maze ./mazes/valid/3_min_5x5.txt > out
if grep -q "Maze ./mazes/valid/3_min_5x5.txt (5x5) successfully loaded" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "3. Testing maze ending with newline - "
timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt > out
if grep -q "Maze ./mazes/valid/4_nl_12x18.txt (12x18) successfully loaded" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "4. Testing maze ending with multiple newlines - "
timeout 0.2 ./maze ./mazes/valid/6_2_nl_9x15.txt > out
if grep -q "Maze ./mazes/valid/6_2_nl_9x15.txt (9x15) successfully loaded" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
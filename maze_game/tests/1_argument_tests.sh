#!/bin/bash

echo -e "\n\n~~ Argument Tests ~~\n"


echo -n "1. Testing no arguments - "
./maze > out
if grep -q "Usage: ./maze <mazefile path>" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "2. Testing 2 arguments - "
./maze x x > out
if grep -q "Usage: ./maze <mazefile path>" out;
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
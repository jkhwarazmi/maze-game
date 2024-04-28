#!/bin/bash

echo -e "\n\n~~ File Handling ~~\n"


echo -n "1. Testing bad filename - "
./maze ./fake.txt > out
if grep -q "Error: Could not open file" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
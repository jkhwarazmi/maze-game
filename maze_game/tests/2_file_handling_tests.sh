#!/bin/bash

# Remove read permission
chmod -r ./mazes/valid/1_bad_perms_13x27.txt

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

# This test is adapted from Amy's solution to lab 2
echo -n "2. Testing bad permissions - "
./maze ./mazes/valid/1_bad_perms_13x27.txt > out
if grep -q "Error: Could not open file" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi


# Restore read permission
chmod +r ./mazes/valid/1_bad_perms_13x27.txt
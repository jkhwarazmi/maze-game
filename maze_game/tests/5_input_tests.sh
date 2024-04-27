#!/bin/bash

echo -e "\n\n~~ Input Validation ~~\n"


# This and similar tests are adapted from chatGPT’s response to the prompt 
# "How do I make my bash script stop as soon as the the input file has ended?"
echo -n "1. Testing lowercase direction inputs - "
timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt < ./inputs/1_lowercase.in > out
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "./outputs/1_directions.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "2. Testing uppercase direction inputs - "
timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt < ./inputs/2_uppercase.in > out
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "./outputs/1_directions.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "3. Testing mixed case direction inputs - "
timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt < ./inputs/3_mixed.in > out
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "./outputs/1_directions.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "4. Testing empty input - "
echo "" | timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt > out
if grep -q "Please enter a valid direction (W, A, S or D to move or M to view the map)" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "5. Testing newline input - "
echo "\n" | timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt > out
if grep -q "Please enter a valid direction (W, A, S or D to move or M to view the map)" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "6. Testing null input - "
echo "\0" | timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt > out
if grep -q "Please enter a valid direction (W, A, S or D to move or M to view the map)" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "7. Testing invalid character input - "
echo "x" | timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt > out
if grep -q "Please enter a valid direction (W, A, S or D to move or M to view the map)" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

# Checking that words with first characters that would be valid inputs are not accepted
echo -n "8. Testing string input with valid first character - "
echo "Walk" | timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt > out
if grep -q "Please enter a valid direction (W, A, S or D to move or M to view the map)" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

# Checking that numbers whose ASCII values are valid inputs are not accepted
echo -n "9. Testing number input with valid ASCII - "
echo "87" | timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt > out
if grep -q "Please enter a valid direction (W, A, S or D to move or M to view the map)" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "10. Testing mixed valid and invalid inputs - "
timeout 0.2 ./maze ./mazes/valid/4_nl_12x18.txt < ./inputs/4_varied.in > out
all_lines_match=true

while read line; do
    if ! grep -qiF -- "$line" out; 
    then
        all_lines_match=false
        break
    fi
done < "outputs/2_varied.out"

if $all_lines_match; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
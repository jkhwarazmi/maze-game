#!/bin/bash

echo -e "\n\n~~ Loading Invalid Mazes ~~\n"


echo -n "1. Testing empty file - "
./maze ./mazes/invalid/1_empty.txt > out
if grep -q "Error: Maze must have minimum height of 5" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "2. Testing too few columns - "
./maze ./mazes/invalid/2_4_cols_12x4.txt > out
if grep -q "Error: Maze must have minimum width of 5" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "3. Testing too many columns - "
./maze ./mazes/invalid/3_101_cols_6x101.txt > out
if grep -q "Error: Maze must have maximum width of 100" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "4. Testing too few rows - "
./maze ./mazes/invalid/4_4_rows_4x12.txt > out
if grep -q "Error: Maze must have minimum height of 5" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "5. Testing too many rows - "
./maze ./mazes/invalid/5_101_rows_101x5.txt > out
if grep -q "Error: Maze must have maximum height of 100" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "6. Testing irregular rows - "
./maze ./mazes/invalid/6_irreg_rows_10x12.txt > out
if grep -q "Error: Maze must have constant width" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "7. Testing irregular cols - "
./maze ./mazes/invalid/7_irreg_cols_9x11.txt > out
if grep -q "Error: Maze must have constant width" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "8. Testing invalid characters - "
./maze ./mazes/invalid/8_invalid_chars_16x13.txt > out
if grep -q "Error: Invalid characters in maze" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "9. Testing no start - "
./maze ./mazes/invalid/9_no_start_7x7.txt > out
if grep -q "Error: Maze must have exactly one start" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "10. Testing 2 starts - "
./maze ./mazes/invalid/10_2_starts_25x25.txt > out
if grep -q "Error: Maze must have exactly one start" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "11. Testing no end - "
./maze ./mazes/invalid/11_no_end_6x12.txt > out
if grep -q "Error: Maze must have exactly one end" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "12. Testing 2 ends - "
./maze ./mazes/invalid/12_2_ends_17x5.txt > out
if grep -q "Error: Maze must have exactly one end" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "13. Testing 2 mazes in the same file - "
./maze ./mazes/invalid/13_2_mazes_9x15.txt > out
if grep -q "Error: Invalid characters in maze" out; 
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
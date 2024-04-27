#!/bin/bash

echo -e "\n\n~~ Successes ~~\n"


echo -n "1. Testing shortest route on smallest maze - "
./maze ./mazes/valid/3_min_5x5.txt < ./inputs/8_short_route_min_maze.in > out
if grep -q "Congratulations! You escaped the maze in 6 moves." out;
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "2. Testing longer route on smallest maze - "
./maze ./mazes/valid/3_min_5x5.txt < ./inputs/9_long_route_min_maze.in > out
if grep -q "Congratulations! You escaped the maze in 10 moves." out;
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "3. Testing medium size maze - "
./maze ./mazes/valid/4_nl_12x18.txt < ./inputs/10_med_maze.in > out
if grep -q "Congratulations! You escaped the maze in 47 moves." out;
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi

echo -n "4. Testing long route on largest maze - "
./maze ./mazes/valid/2_max_100x100.txt < ./inputs/11_long_route_max_maze.in > out
if grep -q "Congratulations! You escaped the maze in 56 moves." out;
then
    echo -e "\e[32mPASS\e[0m"
    let pass++
else
    echo -e "\e[31mFAIL\e[0m"
    let fail++
fi
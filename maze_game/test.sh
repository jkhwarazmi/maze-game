#!/bin/bash

# Allow test files to be executed
chmod +x ./tests/1_argument_tests.sh
chmod +x ./tests/2_file_handling_tests.sh
chmod +x ./tests/3_invalid_maze_tests.sh
chmod +x ./tests/4_valid_maze_tests.sh
chmod +x ./tests/5_input_tests.sh
chmod +x ./tests/6_maze_bounds_tests.sh
chmod +x ./tests/7_map_tests.sh
chmod +x ./tests/8_success_tests.sh

# Remove test results of incomplete tests
rm -f results

# Compile the maze game and run the tests
make

echo -e "\n~~ Maze Game Tests ~~"

./tests/1_argument_tests.sh | tee -a results
./tests/2_file_handling_tests.sh | tee -a results
./tests/3_invalid_maze_tests.sh | tee -a results
./tests/4_valid_maze_tests.sh | tee -a results
./tests/5_input_tests.sh | tee -a results
./tests/6_maze_bounds_tests.sh | tee -a results
./tests/7_map_tests.sh | tee -a results
./tests/8_success_tests.sh | tee -a results

# Count the number of passing and failing tests
pass=$(grep -o "PASS" results | wc -l)
fail=$(grep -o "FAIL" results | wc -l)
total=$((pass+fail))

echo -e "\n\n~~ Summary ~~\n"
echo -e "\e[32mPassing:\e[0m $pass ($((pass*100/total))%)"
echo -e "\e[31mFailing:\e[0m $fail ($((fail*100/total))%)\n"

# Clean up
rm -f out results
make clean

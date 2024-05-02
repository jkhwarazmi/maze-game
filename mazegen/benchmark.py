"""
File: benchmark.py
Author: Jamil Khwarazmi
Date: 01/05/2024

Description:
This Python script times the generation of mazes of different sizes using the
Maze class and outputs the average time taken to generate each maze to the 
command line in ms.

Usage:
python3 benchmark.py
"""

from time import time_ns
from maze import Maze


def benchmark() -> None:
    """
    Benchmarks the time taken to generate mazes of different sizes.
    """
    dimensions = [5, 10, 20, 50, 80, 100]
    iterations = 100

    for dimension in dimensions:
        total_time = 0

        for i in range(iterations):
            start = time_ns()
            maze = Maze(dimension, dimension)
            maze.generate_maze()
            end = time_ns()

            total_time += end - start

        print(
            f"Average time to generate {dimension}x{dimension}: {(total_time / (iterations * 1_000_000)):.3f} ms")


if __name__ == "__main__":
    benchmark()

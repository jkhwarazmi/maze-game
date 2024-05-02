"""
A comparison of the path length of the longest path in mazes of the same size w/ and w/out applying the BFS algorithm.
"""

from sys import argv
import time

import mazegen as v7

if __name__ == "__main__":

    # Getting path differences after 10 generations of 100x100 mazes
    times = []
    iterations = 10
    path_lengths = []
    differences = []
    percentage_differences = []

    # Generate the maze then get the path lengths of the longest path using DFS and DFS + BFS
    for i in range(iterations):
        rows, cols, filepath = v7.check_args()
        rows, cols = 100, 100
        maze = v7.Maze(rows, cols)
        path_lengths.append((maze.max_distance, maze.max_distance))

    try:
        with open(argv[1], "w") as file:
            file.write("Path Lengths of Longest Path in 100x100 Mazes using just DFS vs DFS and BFS\n")

            for i in range(iterations):
                differences.append(path_lengths[i][0] - path_lengths[i][1])
                percentage_differences.append(100 * differences[i] / path_lengths[i][1])
                file.write(f"Run {i + 1}: {differences[i]} difference ({percentage_differences[i]:.1f}%)\n")

            file.write(f"Avg difference: {sum(differences) / iterations} ({(sum(percentage_differences) / iterations):.1f}%)\n")

        print("Path differences written to", argv[1])
    except IOError:
        print("Error: Could not write to file")
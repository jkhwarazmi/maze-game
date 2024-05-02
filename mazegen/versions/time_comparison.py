"""
A comparison of the time taken to generate mazes of the same size using different versions of the maze generation algorithm.

Usage: python3 time_comparison.py <filepath> <rows> <cols>
"""

from sys import argv
import time

import maze_gen_v1 as v1
import maze_gen_v2 as v2
import maze_gen_v3 as v3
import maze_gen_v4 as v4
import maze_gen_v5 as v5
import maze_gen_v6 as v6
import maze_gen_v7 as v7

if __name__ == "__main__":

    # Timing 10 runs of each version for given command line dimensions
    times = []
    iterations = 10

    # Version 1
    times.append([time.time()])
    for i in range(iterations):
        v1.main()
    times[-1].append(time.time())

    # Version 2 - NOTE: Buggy
    times.append([time.time()])
    for i in range(iterations):
        v2.main()
    times[-1].append(time.time())

    # Version 3 - NOTE: Does not work above 45x45 and superceded by v4 so comment out for large tests
    # times.append([time.time()])
    # for i in range(iterations):
    #     rows, cols, filepath = v3.check_args()
    #     maze = v3.Maze(rows, cols)
    #     maze.output_maze(filepath)
    # times[-1].append(time.time())

    # Version 4
    times.append([time.time()])
    for i in range(iterations):
        rows, cols, filepath = v4.check_args()
        maze = v4.Maze(rows, cols)
        maze.output_maze(filepath)
    times[-1].append(time.time())

    # Version 5
    times.append([time.time()])
    for i in range(iterations):
        rows, cols, filepath = v5.check_args()
        maze = v5.Maze(rows, cols)
        maze.output_maze(filepath)
    times[-1].append(time.time())

    # Version 6
    times.append([time.time()])
    for i in range(iterations):
        rows, cols, filepath = v6.check_args()
        maze = v6.Maze(rows, cols)
        maze.output_maze(filepath)
    times[-1].append(time.time())

    # Version 7
    times.append([time.time()])
    for i in range(iterations):
        rows, cols, filepath = v7.check_args()
        maze = v7.Maze(rows, cols)
        maze.output_maze(filepath)
    times[-1].append(time.time())

    try:
        with open(argv[1], "w") as file:
            for i in range(len(times)):
                if i < 2 or len(times) > 6:
                    file.write(
                        f"Version {i + 1}: Time to generate {iterations} {rows}x{cols} mazes = {times[i][1] - times[i][0]} seconds\n")
                if len(times) == 6:
                    if i == 2:
                        file.write("Version 3: Does not work above 45x45\n")
                    if i >= 2:
                        file.write(
                            f"Version {i + 2}: Time to generate {iterations} {rows}x{cols} mazes = {times[i][1] - times[i][0]} seconds\n")
    except IOError:
        print("Error: Could not write to file")

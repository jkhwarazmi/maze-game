"""
File: mazegen.py
Author: Jamil Khwarazmi
Date: 01/05/2024

Description:
This Python script generates a maze of given size and outputs it to the given 
filepath. The script uses the Maze class from the maze.py module to generate the
maze.

Usage:
python3 mazegen.py <mazefile path> <rows> <columns>
"""

from sys import argv
from maze import Maze

def check_args() -> tuple[int, int, str]:
    """
    Ensures that arguments are valid and returns them as correct types if so.

    Returns:
        tuple[int, int, str]: Tuple of rows, columns and filepath if valid, 
                              otherwise (-1, -1, "")
    """
    if len(argv) != 4:
        print(f"Usage: python3 {argv[0]} <mazefile path> <rows> <columns>")
        return (-1, -1, "")

    try:
        rows = int(argv[2])
    except ValueError:
        print("Error: Number of rows must be an integer")
        return (-1, -1, "")

    try:
        cols = int(argv[3])
    except ValueError:
        print("Error: Number of columns must be an integer")
        return (-1, -1, "")

    if rows < 5 or rows > 100:
        print("Error: Number of rows must be between 5 and 100")
        return (-1, -1, "")

    if cols < 5 or cols > 100:
        print("Error: Number of columns must be between 5 and 100")
        return (-1, -1, "")

    try:
        with open(argv[1], "w"):
            pass
    except:
        print("Error: Could not write to file")
        return (-1, -1, "")

    return rows, cols, argv[1]


if __name__ == "__main__":
    rows, cols, filepath = check_args()

    if rows != -1:
        maze = Maze(rows, cols)
        maze.generate_maze()
        maze.output_maze(filepath)

"""
Maze Generator v1

- Generates a maze with a random start and end point w/ a distance apart of at least half the sum of the rows and columns
- Produces a path from start to end randomly moving in either x or y in the direction of end (a "semi-random" walk)
- For anything besides the path, randomly generates a wall or empty space w/ equal probability
- No research done on maze generation algorithms yet, just a basic idea

Issues:
- Only 1 guarenteed path and it can be pretty obvious since it isn't very random
- Solutions not very windy
- Optimal/only (typically) solution is always a fixed (albeit semi-random) path length

Improvements:
- Let's try moving in more random directions as opposed to just towards the end point next
"""


from sys import argv
from random import randint


def main():
    if len(argv) != 4:
        print(f"Usage: {argv[0]} <mazefile path> <rows> <columns>")
        return 0

    try:
        rows = int(argv[2])
    except ValueError:
        print("Error: Number of rows must be an integer")
        return 1

    try:
        cols = int(argv[3])
    except ValueError:
        print("Error: Number of columns must be an integer")
        return 1

    if rows < 5 or rows > 100:
        print("Error: Number of rows must be between 5 and 100")
        return 1

    if cols < 5 or cols > 100:
        print("Error: Number of columns must be between 5 and 100")
        return 1

    try:
        with open(argv[1], "w"):
            pass
    except:
        print("Error: Could not write to file")
        return 1

    start = [0, 0]
    end = [0, 0]

    while abs(start[0] - end[0]) + abs(start[1] - end[1]) < (rows + cols) / 2:
        start = [randint(0, rows - 1), randint(0, cols - 1)]
        end = [randint(0, rows - 1), randint(0, cols - 1)]

    maze = [["" for i in range(cols)] for i in range(rows)]
    maze[start[0]][start[1]] = 'S'
    maze[end[0]][end[1]] = 'E'

    pos = [start[0], start[1]]

    while pos != end:
        r = randint(1, 2)

        if r == 1 and pos[1] != end[1]:
            if pos[1] - end[1] < 0:
                pos[1] += 1
            else:
                pos[1] -= 1
        elif pos[0] != end[0]:
            if pos[0] - end[0] < 0:
                pos[0] += 1
            else:
                pos[0] -= 1

        if maze[pos[0]][pos[1]] != 'E':
            maze[pos[0]][pos[1]] = 'R'

    chars = ["#", " "]

    with open(argv[1], "w") as file:
        for line in maze:
            for char in line:
                if char == 'S' or char == 'E':
                    file.write(char)
                elif char == 'R':
                    file.write(" ")
                else:
                    file.write(chars[randint(0, 1)])
            file.write("\n")


if __name__ == "__main__":
    main()

"""
Maze Generator v3

- A basic implementation of depth first search recursive backtracking
- Based on the pseudocode from: https://courses.cs.washington.edu/courses/cse326/07su/prj2/kruskal.html (Depth First Search)

- Generates a maze with a random start and end point a reasonable distance apart
- Guarantees a path from start to end since any space can be reached from any other space (perfect maze)
- Works by first creating a maze with walls of width 1 surrounding single spaces
- Then uses depth first search to knock down walls between cells to create paths
- Paths are formed by randomly choosing a neighbour to visit and knocking down the wall between the current cell and the neighbour
- Paths are guaranteed to be valid since all neighbouring cells start with all walls up so by the end, all spaces must be connected

- Mazes are much more complex than previous versions

Issues:
- Recursive so relatively slow and will cause stack overflow for large mazes (breaks down above 45x45)
    - Must use iterative implementation in revision
- Start and end relatively predetermined
- Often very long corridors
- Mazes look relatively similar (i.e. not very random) especially compared to v1 and v2

Improvements:
- Make non-recursive
- Alleviate the fixed wall width/randomness issue by adding random spaces after generation
"""


from sys import argv
import random as r


class Maze:
    # Right, Left, Up, Down
    directions = [(0, 2), (0, -2), (2, 0), (-2, 0)]

    def __init__(self, rows, cols):
        # Creates map with walls of width 1 surrounding single spaces
        self.map = [[["#", " "][j % 2] if i % 2 == 1 else "#" for j in range(cols)] for i in range(rows)]
        self.rows = rows
        self.cols = cols

        # Set start to a random guaranteed space
        self.start = (2 * r.randint(0, (rows - 2) // 2) + 1, 2 * r.randint(0, (cols - 2) // 2) + 1)
        self.end = self.start

        # Always generates end a reasonable distance away from start
        while abs(self.start[0] - self.end[0]) + abs(self.start[1] - self.end[1]) < (rows + cols - 2) // 2:
            self.end = (2 * r.randint(0, (rows - 2) // 2) + 1, 2 * r.randint(0, (cols - 2) // 2) + 1)

        # Stack to keep track of visited cells
        self.stack = {self.start}

        self.dfs(self.start)

    def valid_node(self, y, x):
        if not (0 <= x < self.cols and 0 <= y < self.rows):
            return False

        # Check that all neighbouring cells are walls excluding cell itself and diagonals
        for i in range(max(0, y - 1), min(self.rows, y + 2)):
            for j in range(max(0, x - 1), min(self.cols, x + 2)):
                if abs(y - i) + abs(x - j) == 1 and self.map[i][j] == " ":
                    return False

        return True

    def dfs(self, current):
        # Pick a random neighbour to visit
        r.shuffle(self.directions)

        for direction in self.directions:
            new_y, new_x = current[0] + direction[0], current[1] + direction[1]

            # Check if the neighbour has all its walls up
            if self.valid_node(new_y, new_x):

                # Knock down the wall between current neighbour
                self.map[current[0] + direction[0] // 2][current[1] + direction[1] // 2] = " "

                # Push neighbour onto stack
                self.stack.add((new_y, new_x))

                # Recursively visit new current cell
                self.dfs((new_y, new_x))
        else:
            # If no valid move is found, pop from stack to backtrack
            if len(self.stack) > 0:
                self.dfs(self.stack.pop())

    def output_maze(self, filepath):
        self.map[self.start[0]][self.start[1]] = "S"
        self.map[self.end[0]][self.end[1]] = "E"

        with open(filepath, "w") as file:
            for row in self.map:
                file.write("".join(row) + "\n")

        print(f"Maze written to {filepath}")


def check_args():
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
        maze.output_maze(filepath)

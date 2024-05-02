"""
Maze Generator v4 - Modified

- A modified version of maze_gen_v4 that introduces random spaces uniformly throughout the maze
- Unfortunately, it makes the mazes far too easy to solve so will revert to the original version
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
        self.stack = [self.start]

        self.dfs()
        self.randomise()

    def valid_node(self, y, x):
        if not (0 <= x < self.cols and 0 <= y < self.rows):
            return False

        # Check that all neighbouring cells are walls excluding cell itself and diagonals
        for i in range(max(0, y - 1), min(self.rows, y + 2)):
            for j in range(max(0, x - 1), min(self.cols, x + 2)):
                if abs(y - i) + abs(x - j) == 1 and self.map[i][j] == " ":
                    return False

        return True

    def dfs(self):
        while len(self.stack) > 0:
            # Pop a cell from the stack and make it the current cell
            current = self.stack.pop()

            # Pick a random neighbour to visit
            r.shuffle(self.directions)

            for direction in self.directions:
                new_y, new_x = current[0] + direction[0], current[1] + direction[1]

                # Check if the neighbour has all its walls up
                if self.valid_node(new_y, new_x):

                    # Knock down the wall between current neighbour
                    self.map[current[0] + direction[0] // 2][current[1] + direction[1] // 2] = " "

                    # Push neighbour onto stack
                    self.stack.append((new_y, new_x))

    # Randomly add spaces to the maze to make it look more random
    def randomise(self):
        for i in range(self.rows):
            for j in range(self.cols):
                if self.map[i][j] == "#":
                        # 3/4 chance of being a wall to retain difficulty
                        self.map[i][j] = r.choice(["#", "#", "#", " "])

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

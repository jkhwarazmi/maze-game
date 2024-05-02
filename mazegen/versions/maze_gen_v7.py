"""
Maze Generator v7

- An iterative implementation of depth first search recursive backtracking
- Based on the pseudocode from: https://courses.cs.washington.edu/courses/cse326/07su/prj2/kruskal.html (Depth First Search)
- AND Wikipedia: https://en.wikipedia.org/wiki/Maze_generation_algorithm (Randomized depth-first search)
- Influenced by this StackExchange post: https://puzzling.stackexchange.com/questions/38/how-can-i-generate-mazes-that-often-have-multiple-forks-or-choices
- End point influenced by: https://www.altcademy.com/blog/compute-the-diameter-of-a-tree-solved/#:~:text=The%20diameter%20of%20a%20tree%20can%20be%20computed%20using%20depth,the%20diameter%20of%20the%20tree.
- BFS influenced by: https://www.geeksforgeeks.org/longest-path-undirected-tree/
- Proof of correctness for longest path: https://stackoverflow.com/questions/20010472/proof-of-correctness-algorithm-for-diameter-of-a-tree-in-graph-theory


- Adds a BFS to find the longest path in the maze and set final start and end positions
- Ensures that the maze is as long/difficult as possible while still being solvable

Issues:
- Still relatively long corridors but less so than previous versions
- Mazes still look structured (necessary tradeoff for difficulty?)
- Could add more spaces throughout the maze, but that would make them easier to solve (trade-off between difficulty and randomness)
- Was this necessary or was the DFS enough? Check difference in path length between v6 and v7 and compare timings

- Comparison reveals ~10% performance penalty for v7 over v6 for 100x100 mazes
- Average path length difference over 200% (i.e. triple) in favour of v7 for 100x100 mazes -> WELL WORTH IT!
"""


from sys import argv
import random as r


class Maze:
    # Right, Left, Up, Down
    directions = [(0, 2), (0, -2), (2, 0), (-2, 0)]

    def __init__(self, rows, cols):
        # Gets a random starting position
        self.start = (r.randint(0, rows - 1), r.randint(0, cols - 1))
        chars = [" ", "#"] if self.start[1] % 2 == 0 else ["#", " "]

        # Creates map with walls of width 1 surrounding single spaces where start is always a space
        self.map = [[chars[j % 2] if i % 2 == self.start[0] % 2 else "#" for j in range(cols)] for i in range(rows)]
        self.rows = rows
        self.cols = cols

        # Distance map for storing all distances from start
        self.distances = [[-1 for j in range(cols)] for i in range(rows)]
        self.distances[self.start[0]][self.start[1]] = 0
        
        # For comparison between v6 and v7
        self.max_distance_dfs = 0
        self.max_distance_bfs = 0
        
        # Placeholder for end
        self.end = self.start

        # Stack to keep track of visited cells
        self.stack = [self.start]

        # Probability of popping random cell from stack, increases with maze size
        self.probability = 2 * (rows + cols) / 1000

        # DFS generates maze and sets end to furthest node from start
        self.dfs()

        # A BFS is used to find the longest path in the maze and set final start and end positions
        self.bfs()

        # Randomly add spaces to the maze edges to make it appear more random
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
            # Pop the current or a random cell from the stack to decrease corridor length
            if r.random() <= self.probability:
                current = self.stack.pop(r.randint(0, len(self.stack) - 1))
            else:
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

                    # Update distance map
                    distance = self.distances[current[0]][current[1]] + 1
                    self.distances[new_y][new_x] = distance

                    # Set end to new furthest node
                    if distance > self.max_distance_dfs:
                        self.max_distance_dfs = distance
                        self.end = (new_y, new_x)

    def bfs(self):
        # Start BFS from the furthest node from start
        self.start = self.end
        queue = [self.start]

        # Reset distances
        self.distances = [[-1 for j in range(self.cols)] for i in range(self.rows)]
        self.distances[self.start[0]][self.start[1]] = 0

        # We have not visited any nodes yet
        visited = [[False for j in range(self.cols)] for i in range(self.rows)]
        visited[self.start[0]][self.start[1]] = True

        while len(queue) > 0:
            current = queue.pop(0)

            for direction in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                new_y, new_x = current[0] + direction[0], current[1] + direction[1]

                # Check within bounds and that cell is space then, if unvisited, visit
                if 0 <= new_x < self.cols and 0 <= new_y < self.rows and self.map[new_y][new_x] == " " and not visited[new_y][new_x]:
                    visited[new_y][new_x] = True
                    queue.append((new_y, new_x))
                    self.distances[new_y][new_x] = self.distances[current[0]][current[1]] + 1
                    
                    if self.distances[new_y][new_x] > self.max_distance_bfs:
                        self.max_distance_bfs = self.distances[new_y][new_x]
                        self.end = (new_y, new_x)


    # Randomly add spaces to the maze edges to make it look more random
    def randomise(self):
        for i in range(self.rows):
            for j in range(self.cols):
                if (j == 0 or j == self.cols - 1 or i == 0 or i == self.rows - 1) and self.map[i][j] == "#":
                        # 2/3 chance of being a wall to retain difficulty
                        self.map[i][j] = r.choice(["#", "#", " "])

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

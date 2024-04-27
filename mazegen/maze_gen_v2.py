from sys import argv
from random import randint

def main():
    if len(argv) != 4:
        print(f"Usage: python3 {argv[0]} <mazefile path> <rows> <columns>")
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
    

    start = [randint(0, rows - 1), randint(0, cols - 1)]

    # Use quadrants because otherwise random converges on same location, preferntially move in a direction
    quadrants = [[1, 2], 
                 [3, 4]]
    quadrant = quadrants[0 if start[0] < rows // 2 else 1][0 if start[1] < cols // 2 else 1]

    maze = [["" for i in range(cols)] for i in range(rows)]
    maze[start[0]][start[1]] = 'S'

    pos = [start[0], start[1]]

    higher = rows if rows < cols else cols
    moves = randint(10, higher)
    count = 0

    while count < moves:
        r = randint(1, 8)
        upper = quadrant < 3
        left = quadrant % 2 != 0

        # Move preferentially in diagonally opposite direction but allow deviation
        # Up/down
        if r < 4:
            if upper:
                pos[0] += 1
            else:
                pos[0] -= 1
            count += 1
        elif r < 5:
            if upper: 
                pos[0] -= 1
            else:
                pos[0] += 1
        
        # Left/right
        elif r < 8:
            if left:
                pos[1] += 1
            else:
                pos[1] -= 1
            count += 1
        else:
            if left: 
                pos[1] -= 1
            else:
                pos[1] += 1

        # Don't allow out of bounds
        if pos[0] < 0:
            pos[0] = 0
        
        if pos[0] >= rows:
            pos[0] = rows - 1

        if pos[1] < 0:
            pos[1] = 0

        if pos[1] >= cols:
            pos[1] = cols
        
        if maze[pos[0]][pos[1]] != 'S':
            maze[pos[0]][pos[1]] = 'R'

    maze[pos[0]][pos[1]] = 'E'

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
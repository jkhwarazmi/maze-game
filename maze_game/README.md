# Maze Game

This is my maze game written in C, in which a player navigates a maze loaded from a file from the start (`S`) to the end (`E`).

## Usage

1. Compile the program using `make`
2. Run a maze game with `./maze <mazefile path>`
3. Execute `make clean` to remove binaries and object files

### Outputs

The maze game will produce the following outputs:
- ``Usage: ./maze <mazefile path>`` for an invalid number of arguments
- ``Error: Could not open file`` for files that could not be read
- ``Error: Could not create maze`` for mazes that cannot be allocated
- ``Error: Could not create player`` for players that cannot be allocated
- ``Error: Maze cannot end in multiple newlines`` for mazes that end in multiple newlines
- ``Error: Maze must have minimum height of 5`` for mazes that have too few lines and a similar output for an inappropriate width 
- ``Error: Maze must have maximum height of 100`` for mazes that have too many lines and a similar output for inappropriate width
- ``Error: Maze must have constant width`` for mazes with non-constant height or width
- ``Error: Invalid characters in maze`` for invalid maze characters
- ``Error: Maze must have exactly one start`` for mazes without exactly 1 start and a similar output for an invalid number of ends
- ``Maze <mazefile> (hxw) successfully loaded`` for succesfully loading a maze with height, h and width, w
- ``Your move (WASD or M for the map):`` when it expects player input
- ``Please enter a valid direction (W, A, S or D to move or M to view the map)`` for invalid moves
- ``You cannot walk into walls`` if you try walking into walls
- ``You cannot walk out of bounds`` if you try walking outside of the map
- A printout of your map with X marked as your position if you input M or m
- ``You move up/down/left/right`` for allowed inputs of w/s/a/d respectively
- ``Congratulations! You completed the maze in x moves.`` for succesfully exiting the maze in x allowed moves made

The game will exit with the following status codes:
- 0 for successful completion
- 1 for invalid number of arguments
- 2 for invalid input file
- 3 for invalid maze
- 100 for other errors (e.g. memory allocation errors)

## Implementation

The maze game is implemented in C using the following files:
- `main.c` - The main file that contains the main function and invokes the maze game
- `maze.h` - The header file that contains the function prototypes and the struct definition for the maze itself (i.e. creating, validating and freeing a maze)
- `maze.c` - The file that contains the function definitions for the maze header
- `player.h` - The header file that contains the function prototypes and the struct definitions for the player (i.e. creating, moving and freeing a player)
- `player.c` - The file that contains the function definitions for the player header

## Testing

I rigorously tested the program against my original shell test script and it passed all 38 of my test cases. 

Additionally, I have tested it using valgrind to check for memory leaks on various succesful and unsuccesful invocations of the program and it has passed all my tests. I have also limited virtual memory with ulimit and tested the program and it has exited gracefully with the correct status codes.

I have tested with the provided mazes as well as my own valid and invalid ones of various file extensions. I have also checked for unusual inputs like very large inputs exceeding the buffer size, no input, '\n' or '\0' characters, space separated valid inputs, multiple valid inputs on the same line, as well as other edge cases and it has passed all my tests.

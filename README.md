# Maze Game & Mazegen

A terminal maze game written in C, along with a Python maze generator that produces mazes for it.

- [`maze_game`](maze_game) - The maze game itself. It loads and validates a maze from a file, then lets the player navigate from the start (`S`) to the end (`E`) using WASD, with M to view the map.
- [`mazegen`](mazegen) - A maze generator that writes valid maze files for the game. It uses an iterative recursive backtracker with start and end points placed at either end of the maze's diameter. Earlier iterations of the algorithm are kept in `mazegen/versions` so the progression can be followed.

Each directory has its own README with full details on usage, implementation and testing.

## Folder Structure

```
.
├── README.md
├── maze_game
│   ├── README.md
│   ├── main.c, maze.c, maze.h, player.c, player.h
│   ├── makefile
│   ├── test.sh       # Runs the full test suite
│   ├── tests         # Test scripts grouped by feature
│   ├── mazes         # Valid and invalid test mazes
│   ├── inputs        # Player input sequences
│   └── outputs       # Expected outputs
└── mazegen
    ├── README.md
    ├── mazegen.py    # Command line entry point
    ├── maze.py       # Maze class used to generate mazes
    ├── benchmark.py
    ├── maze_*.txt    # Sample generated mazes
    └── versions      # Previous iterations and comparison scripts
```

## Quick Start

Build and play the maze game:
```
cd maze_game
make
./maze <mazefile path>
```

Generate a maze and play it:
```
python3 mazegen/mazegen.py maze.txt 20 20
./maze_game/maze maze.txt
```

Run the maze game's test suite (written for Linux as it relies on GNU `timeout`):
```
cd maze_game
./test.sh
```

## Requirements

- `gcc` and `make` for the maze game
- Python 3 for the maze generator (standard library only)

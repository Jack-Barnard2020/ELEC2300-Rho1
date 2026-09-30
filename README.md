# ELEC2300 - Sudoku CLI Game

A Command-Line Interface (CLI) Sudoku game implemented in C++ for the ELEC2300 module at the University of Southampton. The application features CSV board loading, interactive terminal gameplay, fast bitmask validation, and configurable auto-solvers.

---

## Features

- **Interactive Gameplay**: Input moves on a 9x9 grid using Battleships-style terminal coordinates (`ROWCOL,VALUE` e.g. `A1,5`).
- **Dynamic CSV Loading**: Parses 9x9 grid data from external CSV files across six difficulty levels.
- **Configurable Auto-Solvers**: Includes Depth-First Search (DFS) backtracking and Constraint Propagation (using the Minimum Remaining Values heuristic). The active solver is selected at compile time.
- **In-Game Utilities**: Dedicated shortcuts to refresh the display or reset the puzzle to its starting layout.
- **Bitmask Win Validation**: Employs bitwise checks across rows, columns, and 3x3 subgrids for instant victory validation.

---

## Directory Structure

```text
.
├── main.cpp          # Main CLI application and auto-solver logic
├── generator.cpp     # Standalone utility for generating Sudoku puzzle CSV files
├── boards/           # Directory storing puzzle CSV files
│   ├── beginner1.csv ... beginner20.csv
│   ├── easy1.csv ... easy20.csv
│   ├── medium1.csv ... medium20.csv
│   ├── hard1.csv ... hard20.csv
│   ├── expert1.csv ... expert20.csv
│   └── impossible1.csv ... impossible20.csv
└── README.md         # Project documentation
```

---

## Controls & Usage

### Main Menu Options
Select a difficulty level (1–6) to launch a randomly chosen puzzle file from the `boards/` directory, or select option 7 to exit.

### Gameplay Commands
| Command | Input Example | Action |
| :--- | :--- | :--- |
| **Make Move** | `A1,5` | Places value `5` in row `A`, column `1`. |
| **Auto-Solve** | `a` or `auto` | Solves the board automatically using the pre-configured solver. |
| **Refresh Display** | `c` or `clear` | Clears and redraws the current board view. |
| **Reset Board** | `r` or `reset` | Restores the grid to its initial starting layout. |
| **Quit to Menu** | `q` or `quit` | Exits the active game and returns to the main menu. |

---

## Configuration

The active auto-solver algorithm is selected at compile time via the `SOLVER_MODE` preprocessor macro in `main.cpp`:

```cpp
#define SOLVER_MODE 1 // 1: Depth-First Backtracking
                      // 2: Constraint Propagation with MRV
```
# ELEC2300 - Sudoku CLI Game

A Command Line Interface (CLI) Sudoku game implemented in C++ featuring dynamic CSV board loading, interactive gameplay, and auto-solvers.

---

## Features

- **Interactive Gameplay**: Play full 9x9 Sudoku grids using standard terminal grid notation (`ROWCOL,VALUE` e.g., `A1,5`).
- **Dynamic Board Loading**: Loads randomized 9x9 puzzle grids based on the selected difficulty level from structured CSV files in the `boards/` directory.
- **Configurable Auto-Solver**: Integrates automated CSP solvers that can be triggered mid-game by entering `a` or `auto`. The solver algorithm is determined at compile time.
- **Board Utilities**: Mid-game shortcuts to clear/refresh the board view (`c`) or reset to the initial puzzle state (`r`).

---

## Directory Structure
```
├── main.cpp              # Primary CLI game source code
├── generator.cpp         # Standalone utility to generate unique Sudoku CSV files
├── boards/               # Directory containing puzzle CSV files
│   ├── easy1.csv ... easy20.csv
│   ├── medium1.csv ... medium20.csv
│   └── hard1.csv ... hard20.csv
└── README.md             # Project documentation
```
---

## Puzzle File Format

Puzzles are stored in the `boards/` folder as comma-separated value (`.csv`) files. Empty cells are explicitly represented using `0`.

---

## Auto-Solver Configuration

The program supports switching between CSP Auto-Solver algorithms using the `#define SOLVER_MODE` preprocessor macro at the top of `main.cpp`:

// Set to 1 for Depth-First Backtracking
// Set to 2 for Constraint Propagation with MRV
#define SOLVER_MODE 2

### Supported Algorithms

1. **Mode 1: Depth-First Backtracking**
   - Naive recursive depth-first search (DFS).
   - Sequentially scans for empty cells and tests valid candidates 1–9.
2. **Mode 2: Constraint Propagation with MRV Heuristic**
   - Applies the Minimum Remaining Values (MRV) heuristic.
   - Evaluates remaining valid candidates for every unassigned cell and branches on the cell with the smallest domain size, significantly pruning the search tree.

---

## In-Game Controls

| Command | Action |
| :--- | :--- |
| `A1,5` | Places digit `5` at row `A`, column `1` |
| `a` / `auto` | Runs the pre-configured Auto-Solver on the current board |
| `c` / `clear` | Clears terminal view and redraws current board |
| `r` / `reset` | Resets the board to its initial loaded puzzle state |
| `q` / `quit` | Quits the current puzzle and returns to the main menu |
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

* **Difficulty Selection:** Choose between Easy, Medium, or Hard difficulty levels from an interactive terminal main menu.
* **Randomized Board Loading:** Loads a randomly selected puzzle board file (`1` through `10`) for the chosen difficulty level on each game startup.
* **In-Game Commands:**
  * **Make Move:** Enter cell positions and values using `ROWCOL,Value` format (e.g., `A1,5`).
  * **Clear / Refresh Screen (`c` / `clear`):** Re-prints the current active board to clean up terminal clutter.
  * **Reset Board (`r` / `reset`):** Reloads the initial puzzle state from the CSV file.
  * **Quit (`q` / `quit`):** Exits the active game session and safely returns to the main menu.
* **Win Verification:** Fast bitmask calculation checks rows, columns, and 3x3 subgrids for completed, valid Sudoku solutions.

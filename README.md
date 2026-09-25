# ELEC2300 - Command Line Interface (CLI) Sudoku Game

A lightweight C++ Command Line Interface (CLI) Sudoku game developed for **ELEC2300: Programming** (Lab 1). ELEC2300 is a mandatory Year 2 module on the Electrical and Electronic Engineering (EEE) degree program and its associated variants.

The application dynamically loads random Sudoku puzzles from CSV files based on selected difficulty, supports custom user controls, and validates board completion using bitmask checking.

---

## Module Context

* **Module:** ELEC2300 - Programming
* **Course:** BEng / MEng Electrical and Electronic Engineering (and variants)
* **Year:** Year 2 (Mandatory)
* **Assignment:** Lab 1 - CLI Sudoku Game
* **Author:** Jack Barnard

---

## Features

* **Difficulty Selection:** Choose between Easy, Medium, or Hard difficulty levels from an interactive terminal main menu.
* **Randomized Board Loading:** Loads a randomly selected puzzle board file (`1` through `10`) for the chosen difficulty level on each game startup.
* **In-Game Commands:**
  * **Make Move:** Enter cell positions and values using `ROWCOL,Value` format (e.g., `A1,5`).
  * **Clear / Refresh Screen (`c` / `clear`):** Re-prints the current active board to clean up terminal clutter.
  * **Reset Board (`r` / `reset`):** Reloads the initial puzzle state from the CSV file.
  * **Quit (`q` / `quit`):** Exits the active game session and safely returns to the main menu.
* **Win Verification:** Fast bitmask calculation checks rows, columns, and 3x3 subgrids for completed, valid Sudoku solutions.

---

## File Structure & Naming Conventions

The application expects puzzle files formatted as standard 9x9 CSV matrices in the current working directory.

```text
├── main.cpp                  # Main C++ source code
├── README.md                 # Project documentation
├── easy1.csv ... easy10.csv  # Easy difficulty CSV puzzle boards
├── medium1.csv ... medium10.csv # Medium difficulty CSV puzzle boards
└── hard1.csv ... hard10.csv  # Hard difficulty CSV puzzle boards
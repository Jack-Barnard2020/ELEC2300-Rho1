/* =========== ELEC2300 - Rho1 =========== 
    Author: Jack Barnard 
    Date: 2026/09/21
    Description: A CLI sudoku game
    Change Log:
        2026/09/21 - First version
   ======================================= */

// =================================================
// Includes
// =================================================
#include <iostream> // Used for input and output
#include <vector>   // Used for storing the sudoku board
#include <fstream>  // Used for reading and writing to the sudoku board files
#include <sstream>  // Used for parsing CSV rows
#include <string>   // Used for string handling
#include <cctype>   // Used for toupper()

using namespace std; // Used to avoid having to type std:: before standard library functions

// =================================================
// Global Constants
// =================================================
const int BOARD_SIZE = 9; // The size of the sudoku board

// =================================================
// Function Declarations
// =================================================
bool LoadBoard(string fileName, int Board[BOARD_SIZE][BOARD_SIZE]);
void SaveBoard(string fileName, int Board[BOARD_SIZE][BOARD_SIZE]);
void PrintBoard(const int Board[BOARD_SIZE][BOARD_SIZE]);
string TrimString(const string& value);
bool IsWinner(int Board[BOARD_SIZE][BOARD_SIZE]);
int MakeMove(int Board[BOARD_SIZE][BOARD_SIZE], string position, int value);

// =================================================
// Main Function
// =================================================
int main() {
    int Board[BOARD_SIZE][BOARD_SIZE] = {}; // Initialize board to zero

    // Load the sudoku board from a CSV file
    if (!LoadBoard("board.csv", Board)) {
        cout << "Failed to load board.csv. Please ensure the file is in the current working directory." << endl;
        return 1;
    }

    // Print the initial sudoku board
    PrintBoard(Board);

    // Start a loop to allow the user to make moves until they win or quit
    while (true) {
        // Prompt the user for a move
        cout << "Enter your move (ROWCOL, Value ie. A1,5), 'r' to reset, or 'q' to quit: ";
        string input;
        getline(cin, input); // Get the user's input

        // Check if the user wants to quit
        if (input == "q" || input == "Q") {
            break;
        }

        // Check if the user wants to reset the board
        if (input == "r" || input == "R") {
            if (LoadBoard("board.csv", Board)) {
                cout << "\nBoard reset successfully.\n";
                PrintBoard(Board);
            }
            continue;
        }  

        // Parse the input
        size_t commaPos = input.find(',');
        if (commaPos == string::npos) {
            cout << "Error: Invalid input format. Use format ROWCOL,Value (e.g. A1,5)" << endl;
            continue;
        }

        string position = input.substr(0, commaPos);
        string valueStr = input.substr(commaPos + 1);

        int value;
        try {
            value = stoi(valueStr);
        } catch (const exception&) {
            cout << "Error: Invalid value number." << endl;
            continue;
        }

        // Make the move
        if (MakeMove(Board, position, value) == 0) {
            PrintBoard(Board);

            // Check for winning state
            if (IsWinner(Board)) {
                cout << "\n===============================\n";
                cout << " Congratulations! You won! \n";
                cout << "===============================\n\n";
                break;
            }
        }
    }

    // Save the modified sudoku board to a CSV file upon exit
    SaveBoard("sudoku_board_modified.csv", Board);

    return 0;
}

// =================================================
// Auxiliary Functions
// =================================================

// Function to load the sudoku board from a CSV file
bool LoadBoard(string fileName, int Board[BOARD_SIZE][BOARD_SIZE]) {
    ifstream file(fileName); // Create an input file stream to read the file
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        string line;
        if (!getline(file, line)) {
            cout << "Error: File " << fileName << " does not contain enough rows." << endl;
            return false;
        }

        stringstream row(line);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            string val;
            if (!getline(row, val, ',')) {
                cout << "Error: Row " << (i + 1) << " in file " << fileName << " does not contain " << BOARD_SIZE << " values." << endl;
                return false;
            }

            val = TrimString(val);
            if (val.empty()) {
                Board[i][j] = 0;
            } else {
                try {
                    Board[i][j] = stoi(val);
                } catch (const exception&) {
                    cout << "Error: Invalid value '" << val << "' in file " << fileName << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to save the sudoku board to a CSV file
void SaveBoard(string fileName, int Board[BOARD_SIZE][BOARD_SIZE]) {
    ofstream file(fileName); // Open the file for writing
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << " for writing." << endl;
        return;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            file << Board[i][j];
            if (j < BOARD_SIZE - 1) {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}

// Function to print the sudoku board to the console
void PrintBoard(const int Board[BOARD_SIZE][BOARD_SIZE]) {
    // Top column numbers header
    cout << " | 1 2 3 | 4 5 6 | 7 8 9 |\n";
    cout << "-|-------|-------|-------|\n";

    for (int i = 0; i < BOARD_SIZE; ++i) {
        // Row letter (A through I)
        char rowLetter = 'A' + i;
        cout << rowLetter << "| ";

        for (int j = 0; j < BOARD_SIZE; ++j) {
            // Print space for empty cells (0), otherwise print the number
            if (Board[i][j] == 0) {
                cout << "  ";
            } else {
                cout << Board[i][j] << " ";
            }

            // Vertical 3x3 block separator after columns 2 and 5 (0-indexed)
            if (j == 2 || j == 5) {
                cout << "| ";
            }
        }
        cout << "|\n";

        // Horizontal 3x3 block separator after rows 2, 5, and 8
        if (i == 2 || i == 5 || i == 8) {
            cout << "-|-------|-------|-------|\n";
        }
    }
}

// Function to trim whitespace from a string
string TrimString(const string& value) {
    size_t start = value.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }

    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

// Function to check if the sudoku board is a winning board
// Function to check if the sudoku board is a winning board
bool IsWinner(int Board[BOARD_SIZE][BOARD_SIZE]) {
    // 1. Check Rows
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int rowMask = 0;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int val = Board[i][j];
            if (val < 1 || val > 9 || (rowMask & (1 << val))) return false;
            rowMask |= (1 << val);
        }
    }

    // 2. Check Columns
    for (int j = 0; j < BOARD_SIZE; ++j) {
        int colMask = 0;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            int val = Board[i][j];
            if (val < 1 || val > 9 || (colMask & (1 << val))) return false;
            colMask |= (1 << val);
        }
    }

    // 3. Check 3x3 Subgrids
    for (int box = 0; box < BOARD_SIZE; ++box) {
        int boxMask = 0;
        int startRow = (box / 3) * 3;
        int startCol = (box % 3) * 3;

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                int val = Board[startRow + r][startCol + c];
                if (val < 1 || val > 9 || (boxMask & (1 << val))) return false;
                boxMask |= (1 << val);
            }
        }
    }

    return true; // All rows, columns, and 3x3 grids are complete and valid
}

// Function to make a move on the sudoku board
int MakeMove(int Board[BOARD_SIZE][BOARD_SIZE], string position, int value) {
    position = TrimString(position);

    if (position.length() < 2) {
        cout << "Error: Invalid position format." << endl;
        return 1;
    }

    // Convert row and column characters to indices
    char rowChar = toupper(position[0]);
    char colChar = position[1];

    int row = rowChar - 'A';
    int col = colChar - '1';

    // Check if the position is within grid boundaries
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Error: Row or column out of bounds." << endl;
        return 1; // Invalid move
    }

    // Check if the value is within Sudoku range
    if (value < 1 || value > 9) {
        cout << "Error: Value out of bounds (must be 1-9)." << endl;
        return 1; // Invalid move
    }

    // Make the move
    Board[row][col] = value;
    return 0; // Successful move
}
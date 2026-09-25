/* =========== ELEC2300 - Rho1 =========== 
    Author: Jack Barnard 
    Date: 2026/09/21
    Description: A CLI sudoku game
    Change Log:
        2026/09/21 - First version
        2026/09/22 - Removed save board function. Modified load board function to load a randomly selected board based on difficulty level. Added main menu interface.
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
#include <cstdlib>  // Used for rand() and srand()
#include <ctime>    // Used for time()
#include <limits>   // Used for numeric_limits

using namespace std; // Used to avoid having to type std:: before standard library functions

// =================================================
// Global Constants
// =================================================
const int BOARD_SIZE = 9; // The size of the sudoku board

// =================================================
// Function Declarations
// =================================================
bool LoadBoard(int difficulty, int Board[BOARD_SIZE][BOARD_SIZE]);
void PrintBoard(const int Board[BOARD_SIZE][BOARD_SIZE]);
string TrimString(const string& value);
bool IsWinner(int Board[BOARD_SIZE][BOARD_SIZE]);
int MakeMove(int Board[BOARD_SIZE][BOARD_SIZE], string position, int value);
int DisplayMenu();

// =================================================
// Main Function
// =================================================

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    while (true) {
        int choice = DisplayMenu();

        // Check if the user selected Quit from the main menu
        if (choice == 4) {
            cout << "\nThanks for playing! Goodbye.\n";
            break;
        }

        int Board[BOARD_SIZE][BOARD_SIZE] = {}; // Initialize board to zero

        // Load board based on difficulty level selected
        if (!LoadBoard(choice, Board)) {
            cout << "Error: Unable to start game due to missing board file.\n";
            continue;
        }

        // Print initial sudoku board
        PrintBoard(Board);

        // Gameplay loop
        while (true) {
            cout << "Enter move (e.g. A1,5), 'c' to clear/refresh, 'r' to reset board, or 'q' to quit: ";
            string input;
            getline(cin, input);

            input = TrimString(input);

            // Lowercase check helper
            string lowerInput = input;
            for (char &c : lowerInput) c = tolower(c);

            // Check for Quit back to menu
            if (lowerInput == "q" || lowerInput == "quit") {
                cout << "\nReturning to main menu...\n";
                break;
            }

            // Check for Clear (redraws screen)
            if (lowerInput == "c" || lowerInput == "clear") {
                cout << "\n--- Board Refreshed ---\n";
                PrintBoard(Board);
                continue;
            }

            // Check for Reset
            if (lowerInput == "r" || lowerInput == "reset") {
                if (LoadBoard(choice, Board)) {
                    cout << "\nBoard reset successfully.\n";
                    PrintBoard(Board);
                }
                continue;
            }

            // Parse input string
            size_t commaPos = input.find(',');
            if (commaPos == string::npos) {
                cout << "Error: Invalid format. Use format ROWCOL,Value (e.g. A1,5)\n";
                continue;
            }

            string position = input.substr(0, commaPos);
            string valueStr = input.substr(commaPos + 1);

            int value;
            try {
                value = stoi(valueStr);
            } catch (const exception&) {
                cout << "Error: Invalid value number.\n";
                continue;
            }

            // Apply move
            if (MakeMove(Board, position, value) == 0) {
                PrintBoard(Board);

                // Check for winning state
                if (IsWinner(Board)) {
                    cout << "\n===============================\n";
                    cout << " Congratulations! You won!    \n";
                    cout << "===============================\n\n";
                    break; // Return to main menu
                }
            }
        }
    }

    return 0;
}

// =================================================
// Auxiliary Functions
// =================================================

// Function to display the main menu and get the user's choice
int DisplayMenu() {
    cout << "\n===============================\n";
    cout << "        Sudoku Game Menu       \n";
    cout << "===============================\n";
    cout << "1. Easy Sudoku\n";
    cout << "2. Medium Sudoku\n";
    cout << "3. Hard Sudoku\n";
    cout << "4. Quit\n";
    cout << "Enter your choice (1-4): ";

    int choice; 
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid choice. Please enter a number between 1 and 4: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard extra input
            break; // Valid input, exit the loop
        }
    }
    return choice;
}

// Function to load the sudoku board from a CSV file
bool LoadBoard(int difficulty, int Board[BOARD_SIZE][BOARD_SIZE]) {
    string levelName;
    switch (difficulty) {
        case 1:
            levelName = "easy";
            break;
        case 2:
            levelName = "medium";
            break;
        case 3:
            levelName = "hard";
            break;
        default:
            cout << "Error: Invalid difficulty level." << endl;
            return false;
    }

    // Generate random number between 1 and 10 and construct filename
    int randomNum = rand() % 10 + 1;
    string fileName = levelName + to_string(randomNum) + ".csv";

    // Open the file from the folder "boards"
    ifstream file("boards/" + fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        string line;
        if (!getline(file, line)) {
            cout << "Error: Not enough rows in file " << fileName << endl;
            return false;
        }

        stringstream ss(line);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            string cell;
            if (!getline(ss, cell, ',')) {
                cout << "Error: Not enough columns in row " << i + 1 << " of file " << fileName << endl;
                return false;
            }

            cell = TrimString(cell);
            if (cell.empty()) {
                Board[i][j] = 0;
            } else {
                try {
                    Board[i][j] = stoi(cell);
                } catch (const exception&) {
                    cout << "Error: Invalid cell value '" << cell << "' in file " << fileName << endl;
                    return false;
                }
            }
        }
    }

    file.close();
    return true;
}

// Function to print the sudoku board to the console
void PrintBoard(const int Board[BOARD_SIZE][BOARD_SIZE]) {
    cout << " | 1 2 3 | 4 5 6 | 7 8 9 |\n";
    cout << "-|-------|-------|-------|\n";

    for (int i = 0; i < BOARD_SIZE; ++i) {
        char rowLetter = 'A' + i;
        cout << rowLetter << "| ";

        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (Board[i][j] == 0) {
                cout << "  ";
            } else {
                cout << Board[i][j] << " ";
            }

            if (j == 2 || j == 5) {
                cout << "| ";
            }
        }
        cout << "|\n";

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

    return true;
}

// Function to make a move on the sudoku board
int MakeMove(int Board[BOARD_SIZE][BOARD_SIZE], string position, int value) {
    position = TrimString(position);

    if (position.length() < 2) {
        cout << "Error: Invalid position format." << endl;
        return 1;
    }

    char rowChar = toupper(position[0]);
    char colChar = position[1];

    int row = rowChar - 'A';
    int col = colChar - '1';

    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Error: Row or column out of bounds." << endl;
        return 1;
    }

    if (value < 1 || value > 9) {
        cout << "Error: Value out of bounds (must be 1-9)." << endl;
        return 1;
    }

    Board[row][col] = value;
    return 0;
}
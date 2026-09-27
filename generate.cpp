#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>

using namespace std;

const int BOARD_SIZE = 9;

// Helper to verify placement validity
bool IsValid(const vector<vector<int>>& board, int row, int col, int val) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[row][i] == val || board[i][col] == val) return false;
    }
    int startRow = (row / 3) * 3, startCol = (col / 3) * 3;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[startRow + r][startCol + c] == val) return false;
        }
    }
    return true;
}

// Fills an empty grid with a complete valid solution using randomized backtracking
bool FillBoard(vector<vector<int>>& board, mt19937& rng) {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board[r][c] == 0) {
                vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                shuffle(nums.begin(), nums.end(), rng);

                for (int val : nums) {
                    if (IsValid(board, r, c, val)) {
                        board[r][c] = val;
                        if (FillBoard(board, rng)) return true;
                        board[r][c] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Counts up to 2 solutions to verify puzzle uniqueness
int CountSolutions(vector<vector<int>>& board, int& count) {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board[r][c] == 0) {
                for (int val = 1; val <= 9; ++val) {
                    if (IsValid(board, r, c, val)) {
                        board[r][c] = val;
                        CountSolutions(board, count);
                        board[r][c] = 0;
                        if (count >= 2) return count; // Early exit if not unique
                    }
                }
                return count;
            }
        }
    }
    count++;
    return count;
}

// Digs holes while ensuring uniqueness
vector<vector<int>> GenerateUniquePuzzle(int targetClues, mt19937& rng) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    FillBoard(board, rng);

    vector<pair<int, int>> cells;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end(), rng);

    int currentClues = 81;
    for (auto cell : cells) {
        if (currentClues <= targetClues) break;

        int r = cell.first;
        int c = cell.second;
        int temp = board[r][c];
        board[r][c] = 0;

        int solutionCount = 0;
        CountSolutions(board, solutionCount);

        // If removing value creates multiple solutions, revert cell
        if (solutionCount != 1) {
            board[r][c] = temp;
        } else {
            currentClues--;
        }
    }
    return board;
}

// Saves grid to standard CSV format using explicit 0s for empty cells
void SaveToCSV(const string& filename, const vector<vector<int>>& board) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            file << board[r][c];
            if (c < BOARD_SIZE - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // Target clues: Easy (75), Medium (55), Hard (28)
    vector<pair<string, int>> difficulties = {
        {"easy", 75},
        {"medium", 55},
        {"hard", 28}
    };

    cout << "Generating 20 unique boards per difficulty level (CSV with 0s)...\n";

    for (auto diff : difficulties) {
        string level = diff.first;
        int targetClues = diff.second;

        for (int i = 1; i <= 20; ++i) {
            vector<vector<int>> puzzle = GenerateUniquePuzzle(targetClues, rng);
            string filename = "boards/" + level + to_string(i) + ".csv";
            SaveToCSV(filename, puzzle);
            cout << "Generated: " << filename << endl;
        }
    }

    cout << "All 60 boards successfully generated!\n";
    return 0;
}                        board[r][c] = val;
                        if (FillBoard(board, rng)) return true;
                        board[r][c] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Counts up to 2 solutions to verify puzzle uniqueness
int CountSolutions(vector<vector<int>>& board, int& count) {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board[r][c] == 0) {
                for (int val = 1; val <= 9; ++val) {
                    if (IsValid(board, r, c, val)) {
                        board[r][c] = val;
                        CountSolutions(board, count);
                        board[r][c] = 0;
                        if (count >= 2) return count; // Early exit if not unique
                    }
                }
                return count;
            }
        }
    }
    count++;
    return count;
}

// Digs holes while ensuring uniqueness
vector<vector<int>> GenerateUniquePuzzle(int targetClues, mt19937& rng) {
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
    FillBoard(board, rng);

    vector<pair<int, int>> cells;
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end(), rng);

    int currentClues = 81;
    for (auto cell : cells) {
        if (currentClues <= targetClues) break;

        int r = cell.first;
        int c = cell.second;
        int temp = board[r][c];
        board[r][c] = 0;

        int solutionCount = 0;
        CountSolutions(board, solutionCount);

        // If removing value creates multiple solutions, revert cell
        if (solutionCount != 1) {
            board[r][c] = temp;
        } else {
            currentClues--;
        }
    }
    return board;
}

// Saves grid to standard CSV format using explicit 0s for empty cells
void SaveToCSV(const string& filename, const vector<vector<int>>& board) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            file << board[r][c];
            if (c < BOARD_SIZE - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    // Target clues: Easy (75), Medium (55), Hard (28)
    vector<pair<string, int>> difficulties = {
        {"easy", 75},
        {"medium", 55},
        {"hard", 28}
    };

    cout << "Generating 20 unique boards per difficulty level (CSV with 0s)...\n";

    for (auto diff : difficulties) {
        string level = diff.first;
        int targetClues = diff.second;

        for (int i = 1; i <= 20; ++i) {
            vector<vector<int>> puzzle = GenerateUniquePuzzle(targetClues, rng);
            string filename = "boards/" + level + to_string(i) + ".csv";
            SaveToCSV(filename, puzzle);
            cout << "Generated: " << filename << endl;
        }
    }

    cout << "All 60 boards successfully generated!\n";
    return 0;
}

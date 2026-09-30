/* =========== ELEC2300 - Rho1 =========== 
    Author: Jack Barnard 
    Date: 2026/09/21
    Description: Standalone Sudoku puzzle generator (CSV export)
    Change Log:
        2026/09/21 - Initial generator script.
        2026/09/22 - Added CSV file output targeting boards/ directory.
        2026/09/27 - Updated difficulty thresholds and added uniqueness checks.
        2026/09/30 - Fixed comment formatting and cleaned up file header.
   ======================================= */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>

using namespace std;

const int BOARD_SIZE = 9;

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

// Fills an empty 9x9 board with a randomized valid Sudoku solution
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

// DFS solution counter (exits early if >1 solution found to prove uniqueness)
int CountSolutions(vector<vector<int>>& board, int& count) {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            if (board[r][c] == 0) {
                for (int val = 1; val <= 9; ++val) {
                    if (IsValid(board, r, c, val)) {
                        board[r][c] = val;
                        CountSolutions(board, count);
                        board[r][c] = 0;
                        if (count >= 2) return count;
                    }
                }
                return count;
            }
        }
    }
    count++;
    return count;
}

// Removes numbers from a full board while maintaining a single unique solution
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

        // Revert cell if removal creates ambiguous solution states
        if (solutionCount != 1) {
            board[r][c] = temp;
        } else {
            currentClues--;
        }
    }
    return board;
}

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

    // Target remaining clue count per difficulty tier
    vector<pair<string, int>> difficulties = {
        {"beginner", 80},
        {"easy", 70},
        {"medium", 55},
        {"hard", 42},
        {"expert", 10},
        {"impossible", 1}
    };

    cout << "Generating 20 unique boards per difficulty level (CSV format)...\n";

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

    cout << "All 120 boards successfully generated!\n";
    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

class Sudoku {
public:
    Sudoku(string board_string);
    void solve();
    string board_to_string();

private:
    vector<vector<int>> board;
    bool solve_board(int row, int col);
    pair<int, int> next_position(int row, int col);
    bool valid_move(int row, int col, int num);
    vector<int> subgrid(int row, int col);
};

Sudoku::Sudoku(string board_string) {
    for (int i = 0; i < 81; i++) {
        int row = i / 9;
        int col = i % 9;
        if (board.size() <= row) {
            board.push_back(vector<int>());
        }
        board[row].push_back(board_string[i] - '0');
    }
}

void Sudoku::solve() {
    solve_board(0, 0);
}

bool Sudoku::solve_board(int row, int col) {
    if (row == 9) {
        return true;
    }

    pair<int, int> next_pos = next_position(row, col);
    int next_row = next_pos.first;
    int next_col = next_pos.second;

    if (board[row][col] != 0) {
        return solve_board(next_row, next_col);
    } else {
        for (int num = 1; num <= 9; num++) {
            if (valid_move(row, col, num)) {
                board[row][col] = num;
                if (solve_board(next_row, next_col)) {
                    return true;
                }
            }
        }
        board[row][col] = 0;
        return false;
    }
}

pair<int, int> Sudoku::next_position(int row, int col) {
    if (col == 8) {
        return { row + 1, 0 };
    } else {
        return { row, col + 1 };
    }
}

bool Sudoku::valid_move(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) {
            return false;
        }
        if (board[i][col] == num) {
            return false;
        }
    }
    for (int r : subgrid(row, col)) {
        if (r == num) {
            return false;
        }
    }
    return true;
}

vector<int> Sudoku::subgrid(int row, int col) {
    int subgrid_row = (row / 3) * 3;
    int subgrid_col = (col / 3) * 3;
    vector<int> result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.push_back(board[subgrid_row + i][subgrid_col + j]);
        }
    }
    return result;
}

string Sudoku::board_to_string() {
    string result;
    for (int i = 0; i < 81; i++) {
        int row = i / 9;
        int col = i % 9;
        result += to_string(board[row][col]);
    }
    return result;
}

int main() {
    string board_string = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    Sudoku sudoku(board_string);
   

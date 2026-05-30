#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

class sudoku_cracker {
private:
  uint16_t rows[9], cols[9], boxes[9];

  bool isvalid(int r, int c, int d) {
    uint16_t mask = 1 << (d - 1);
    return !(rows[r] & mask) && !(cols[c] & mask) &&
           !(boxes[(r / 3) * 3 + c / 3] & mask);
  }

  bool solve(vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') {
          int box = (i / 3) * 3 + j / 3;
          for (int d = 1; d <= 9; d++) {
            if (isvalid(i, j, d)) {
              uint16_t mask = 1 << (d - 1);
              board[i][j] = '0' + d;
              rows[i] |= mask;
              cols[j] |= mask;
              boxes[box] |= mask;

              if (solve(board))
                return true;

              board[i][j] = '.';
              rows[i] &= ~mask;
              cols[j] &= ~mask;
              boxes[box] &= ~mask;
            }
          }
          return false;
        }
      }
    }
    return true;
  }

public:
  bool solveSudoku(vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++)
      rows[i] = cols[i] = boxes[i] = 0;

    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
        if (board[i][j] != '.') {
          int d = board[i][j] - '0';
          uint16_t mask = 1 << (d - 1);
          rows[i] |= mask;
          cols[j] |= mask;
          boxes[(i / 3) * 3 + j / 3] |= mask;
        }

    return solve(board);
  }
};

void printBoard(const vector<vector<char>> &board) {
  for (auto &row : board) {
    for (auto &cell : row)
      cout << cell << " ";
    cout << "\n";
  }
}

void genRandomSudoku(vector<vector<char>> &board) {
  board = vector<vector<char>>(9, vector<char>(9, '.'));

  auto fillBox = [&](int row, int col) {
    vector<char> nums = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    random_shuffle(nums.begin(), nums.end());
    int idx = 0;
    for (int i = row; i < row + 3; ++i)
      for (int j = col; j < col + 3; ++j)
        board[i][j] = nums[idx++];
  };

  fillBox(0, 0);
  fillBox(3, 3);
  fillBox(6, 6);

  sudoku_cracker filler;
  filler.solveSudoku(board);

  int cells_to_remove = 50;
  while (cells_to_remove > 0) {
    int i = rand() % 9;
    int j = rand() % 9;
    if (board[i][j] != '.') {
      board[i][j] = '.';
      cells_to_remove--;
    }
  }
}

int main() {
  srand(time(0));

  vector<vector<char>> board;
  genRandomSudoku(board);

  cout << "Sudoku Puzzle:\n";
  printBoard(board);

  cout << "\nSolving...\n\n";
  cout << "the sudocraft\n\n";

  sudoku_cracker solver;
  if (solver.solveSudoku(board)) {
    cout << "Solved Sudoku:\n";
    printBoard(board);
  } else {
    cout << "Sudoku is unsolvable.\n";
  }

  return 0;
}

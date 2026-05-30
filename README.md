# SUDOCRAFT

A C++ command-line app that generates a random Sudoku puzzle and solves it using backtracking.

## How it works

- **Generator** — seeds three independent diagonal 3×3 boxes with shuffled digits, then completes the full board via the solver, then removes 50 cells to produce the puzzle.
- **Solver** — recursive backtracking with O(1) bitmask constraint checking (`uint16_t` arrays for rows, columns, and 3×3 boxes). Validity per candidate is a single bitwise AND instead of scanning 27 cells.

## Build & Run

```bash
g++ -o sudocraft sudoku.cpp && ./sudocraft
```

## Example output

```
Sudoku Puzzle:
. 8 . 2 . 3 6 5 9
. . . . . 9 . . .
5 1 9 . . . . . .
...

Solved Sudoku:
7 8 4 2 1 3 6 5 9
2 6 3 4 5 9 1 7 8
5 1 9 6 7 8 3 2 4
...
```

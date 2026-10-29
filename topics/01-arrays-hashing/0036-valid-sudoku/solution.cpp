/*
 * 0036. Valid Sudoku  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/valid-sudoku/
 *
 * Problem: Return true if the filled cells of a 9x9 board have no repeated
 *          digit in any row, column, or 3x3 box ('.' = empty).
 *
 * Examples (rows written as strings):
 *   LeetCode example 1                               -> true
 *   example 1 with top-left 5 changed to 8           -> false
 *   empty board                                      -> true
 *
 * Approaches:
 *   1. Three separate passes        O(81) time, O(9) space
 *   2. Single pass, 27 seen  ⭐      O(81) time, O(243) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

using Board = vector<string>;

// ---------- Approach 1: Three Separate Passes ----------
bool isValidSudokuThreePass(const Board& b) {
    for (int i = 0; i < 9; i++) {
        bool row[9] = {}, col[9] = {}, box[9] = {};
        for (int j = 0; j < 9; j++) {
            char r = b[i][j];                                           // row i
            char c = b[j][i];                                           // column i
            char x = b[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3];      // j-th cell of box i
            if (r != '.' && exchange(row[r - '1'], true)) return false;
            if (c != '.' && exchange(col[c - '1'], true)) return false;
            if (x != '.' && exchange(box[x - '1'], true)) return false;
        }
    }
    return true;
}

// ---------- Approach 2: Single Pass, 27 Seen-Arrays ⭐ ----------
bool isValidSudoku(const Board& b) {
    bool rows[9][9] = {}, cols[9][9] = {}, boxes[9][9] = {};
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++) {
            if (b[r][c] == '.') continue;
            int d = b[r][c] - '1';                          // '1'..'9' -> 0..8
            int k = (r / 3) * 3 + c / 3;                    // box index 0..8
            if (rows[r][d] || cols[c][d] || boxes[k][d]) return false;
            rows[r][d] = cols[c][d] = boxes[k][d] = true;
        }
    return true;
}

// ---------- Driver ----------
int main() {
    Board valid = {
        "53..7....", "6..195...", ".98....6.",
        "8...6...3", "4..8.3..1", "7...2...6",
        ".6....28.", "...419..5", "....8..79"
    };
    Board invalid = valid;
    invalid[0][0] = '8';
    Board empty(9, string(9, '.'));
    cout << boolalpha;
    for (auto* b : {&valid, &invalid, &empty}) {
        cout << "three pass : " << isValidSudokuThreePass(*b) << "\n";
        cout << "single pass: " << isValidSudoku(*b) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - bool a[9][9] = {} zero-initializes a 2-D array.
 * - exchange(x, true) sets x and returns its OLD value: "was it already seen?".
 * - Chained assignment a = b = c = true sets all three.
 * - string(9, '.') builds a string of 9 dots.
 */

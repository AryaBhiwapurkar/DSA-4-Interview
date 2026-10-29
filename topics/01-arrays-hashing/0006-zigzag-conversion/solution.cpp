/*
 * 0006. Zigzag Conversion  |  Medium  |  Arrays & Hashing
 * Link: https://leetcode.com/problems/zigzag-conversion/
 *
 * Problem: Write s in a zigzag over numRows rows (down, then diagonally
 *          up, repeat) and return the rows read left to right.
 *
 * Examples:
 *   "PAYPALISHIRING", 3  -> "PAHNAPLSIIGYIR"
 *   "PAYPALISHIRING", 4  -> "PINALSIGYAHRPI"
 *   "A", 1               -> "A"
 *   "AB", 5              -> "AB"
 *
 * Approaches:
 *   1. Direct index math     O(n) time, O(n) output
 *   2. Row buckets  ⭐        O(n) time, O(n) space   <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Direct Index Math ----------
string convertMath(const string& s, int numRows) {
    int n = s.size();
    if (numRows == 1 || numRows >= n) return s;
    int cycle = 2 * (numRows - 1);
    string out;
    for (int r = 0; r < numRows; r++)
        for (int k = r; k < n; k += cycle) {
            out += s[k];                                      // vertical column char
            int diag = k + cycle - 2 * r;                     // diagonal char between columns
            if (r != 0 && r != numRows - 1 && diag < n) out += s[diag];
        }
    return out;
}

// ---------- Approach 2: Row Buckets ⭐ ----------
string convert(const string& s, int numRows) {
    if (numRows == 1) return s;                               // otherwise the bounce never moves
    vector<string> rows(min(numRows, (int)s.size()));
    int r = 0, dir = 1;
    for (char c : s) {
        rows[r] += c;
        if (r == 0) dir = 1;
        else if (r == (int)rows.size() - 1) dir = -1;          // bounce at top and bottom
        r += dir;
    }
    string out;
    for (auto& row : rows) out += row;
    return out;
}

// ---------- Driver ----------
int main() {
    vector<pair<string, int>> tests = {{"PAYPALISHIRING", 3}, {"PAYPALISHIRING", 4}, {"A", 1}, {"AB", 5}};
    for (auto& [s, k] : tests) {
        cout << "math   : " << convertMath(s, k) << "\n";
        cout << "buckets: " << convert(s, k) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<string> rows(k) creates k empty strings.
 * - string += char appends one character (amortized O(1)).
 * - min(numRows, (int)s.size()): both args must be the same type.
 */

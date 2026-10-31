/*
 * 0052. N-Queens II  |  Hard  |  Backtracking
 * Link: https://leetcode.com/problems/n-queens-ii/
 *
 * Problem: Count the placements of n non-attacking queens on an n x n board.
 *
 * Examples:
 *   n 4  -> 2
 *   n 1  -> 1
 *   n 2  -> 0
 *   n 3  -> 0
 *   n 8  -> 92
 *   n 9  -> 352
 *
 * Approaches:
 *   1. Backtracking + col/diag sets  ⭐   O(n!) time, O(n) space   <- go-to
 *   2. Bitmask backtracking              O(n!) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Backtracking + Column/Diagonal Sets ⭐ ----------
int countFrom(int r, int n, vector<bool>& cols, vector<bool>& diag, vector<bool>& anti) {
    if (r == n) return 1;
    int total = 0;
    for (int c = 0; c < n; c++) {
        int d = r - c + n - 1, a = r + c;
        if (cols[c] || diag[d] || anti[a]) continue;
        cols[c] = diag[d] = anti[a] = true;
        total += countFrom(r + 1, n, cols, diag, anti);
        cols[c] = diag[d] = anti[a] = false;
    }
    return total;
}

int totalNQueens(int n) {
    vector<bool> cols(n), diag(2 * n - 1), anti(2 * n - 1);
    return countFrom(0, n, cols, diag, anti);
}

// ---------- Approach 2: Bitmask Backtracking ----------
int bits(int full, int cols, int d1, int d2) {
    if (cols == full) return 1;
    int total = 0;
    for (int avail = full & ~(cols | d1 | d2); avail; ) {
        int bit = avail & -avail;          // lowest free column
        avail -= bit;
        total += bits(full, cols | bit, ((d1 | bit) << 1) & full, (d2 | bit) >> 1);   // attacks shift one column per row
    }
    return total;
}

int totalNQueensBitmask(int n) {
    return bits((1 << n) - 1, 0, 0, 0);
}

// ---------- Driver ----------
int main() {
    for (int n : {4, 1, 2, 3, 8, 9}) {
        cout << "sets   : " << totalNQueens(n) << "\n";
        cout << "bitmask: " << totalNQueensBitmask(n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - x & -x isolates the lowest set bit (two's complement).
 * - (1 << n) - 1 is a mask of the low n bits.
 * - A for loop with an empty increment: `for (init; cond; )`.
 */

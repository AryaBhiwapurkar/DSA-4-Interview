/*
 * 0221. Maximal Square  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/maximal-square/
 *
 * Problem: Area of the largest all-'1' square in a grid of '0'/'1' chars.
 *
 * Examples:
 *   [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]] -> 4
 *   [["0","1"],["1","0"]]                    -> 1
 *   [["0"]]                                  -> 0
 *   [["1","1","1"],["1","1","1"],["1","1","1"]] -> 9
 *   [["1","1"],["1","0"]]                    -> 1
 *
 * Approaches:
 *   1. Brute-force expansion   O(m*n*min(m,n)^2) time, O(1) space
 *   2. 2-D DP  ⭐               O(m*n) time, O(m*n) space    <- go-to
 *   3. 1-D rolling row         O(m*n) time, O(n) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute-force Expansion ----------
int maximalSquareBrute(const vector<vector<char>>& g) {
    int m = g.size(), n = g[0].size(), best = 0;
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) {
            if (g[r][c] != '1') continue;
            int k = 1;                              // current side, top-left at (r, c)
            bool ok = true;
            while (ok && r + k < m && c + k < n) {
                for (int i = 0; i <= k && ok; i++)  // new bottom row and right column
                    if (g[r + k][c + i] != '1' || g[r + i][c + k] != '1') ok = false;
                if (ok) k++;
            }
            best = max(best, k);
        }
    return best * best;
}

// ---------- Approach 2: 2-D DP ⭐ ----------
int maximalSquare(const vector<vector<char>>& g) {
    int m = g.size(), n = g[0].size(), side = 0;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));   // padded: row 0 / col 0 are zeros
    for (int r = 1; r <= m; r++)
        for (int c = 1; c <= n; c++)
            if (g[r - 1][c - 1] == '1') {
                dp[r][c] = 1 + min({dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1]});
                side = max(side, dp[r][c]);
            }
    return side * side;
}

// ---------- Approach 3: 1-D Rolling Row ----------
int maximalSquareRow(const vector<vector<char>>& g) {
    int n = g[0].size(), side = 0;
    vector<int> row(n + 1, 0);
    for (auto& cells : g) {
        int diag = 0;                               // old row[c-1] = top-left
        for (int c = 1; c <= n; c++) {
            int top = row[c];
            row[c] = cells[c - 1] == '1' ? 1 + min({top, row[c - 1], diag}) : 0;
            diag = top;
            side = max(side, row[c]);
        }
    }
    return side * side;
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<char>>> tests = {
        {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}},
        {{'0', '1'}, {'1', '0'}},
        {{'0'}},
        {{'1', '1', '1'}, {'1', '1', '1'}, {'1', '1', '1'}},
        {{'1', '1'}, {'1', '0'}},
    };
    for (auto& g : tests) {
        cout << "brute: " << maximalSquareBrute(g) << "\n";
        cout << "dp   : " << maximalSquare(g) << "\n";
        cout << "row  : " << maximalSquareRow(g) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - min({a, b, c}) takes an initializer list for more than two values.
 * - Compare chars with '1', not 1.
 * - Padding the table by one row/column turns edge checks into reads of 0.
 */

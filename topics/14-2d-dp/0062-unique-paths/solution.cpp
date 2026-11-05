/*
 * 0062. Unique Paths  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/unique-paths/
 *
 * Problem: Count paths from the top-left to the bottom-right of an m x n grid
 *          moving only right or down.
 *
 * Examples:
 *   m=3, n=7     -> 28
 *   m=3, n=2     -> 3
 *   m=1, n=1     -> 1
 *   m=1, n=5     -> 1
 *   m=10, n=10   -> 48620
 *
 * Approaches:
 *   1. Memoized recursion   O(m*n) time, O(m*n) space
 *   2. 2-D table            O(m*n) time, O(m*n) space
 *   3. 1-D rolling row  ⭐   O(m*n) time, O(n) space     <- go-to
 *   4. Combinatorics        O(min(m,n)) time, O(1) space
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
int paths(int r, int c, vector<vector<int>>& memo) {
    if (r == 0 || c == 0) return 1;               // first row / column: one straight path
    if (memo[r][c]) return memo[r][c];
    return memo[r][c] = paths(r - 1, c, memo) + paths(r, c - 1, memo);
}

int uniquePathsMemo(int m, int n) {
    vector<vector<int>> memo(m, vector<int>(n, 0));
    return paths(m - 1, n - 1, memo);
}

// ---------- Approach 2: 2-D Table ----------
int uniquePathsTable(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));
    for (int r = 1; r < m; r++)
        for (int c = 1; c < n; c++)
            dp[r][c] = dp[r - 1][c] + dp[r][c - 1];   // from above + from the left
    return dp[m - 1][n - 1];
}

// ---------- Approach 3: 1-D Rolling Row ⭐ ----------
int uniquePaths(int m, int n) {
    vector<int> row(n, 1);
    for (int r = 1; r < m; r++)
        for (int c = 1; c < n; c++)
            row[c] += row[c - 1];                  // row[c] is still "above"
    return row[n - 1];
}

// ---------- Approach 4: Combinatorics ----------
int uniquePathsMath(int m, int n) {
    long long res = 1;                             // C(m+n-2, m-1), built incrementally
    for (int i = 1; i < m; i++) res = res * (n - 1 + i) / i;   // exact at every step
    return (int)res;
}

// ---------- Driver ----------
int main() {
    vector<pair<int, int>> tests = {{3, 7}, {3, 2}, {1, 1}, {1, 5}, {10, 10}};
    for (auto [m, n] : tests) {
        cout << "memo : " << uniquePathsMemo(m, n) << "\n";
        cout << "table: " << uniquePathsTable(m, n) << "\n";
        cout << "row  : " << uniquePaths(m, n) << "\n";
        cout << "math : " << uniquePathsMath(m, n) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - vector<vector<int>> dp(m, vector<int>(n, 1)) builds an m x n grid of 1s.
 * - `return memo[r][c] = ...` stores and returns in one line.
 * - res * (n-1+i) / i: multiply before dividing (exact), in long long to avoid overflow.
 */

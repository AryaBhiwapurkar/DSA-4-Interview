/*
 * 0063. Unique Paths II  |  Medium  |  2-D Dynamic Programming
 * Link: https://leetcode.com/problems/unique-paths-ii/
 *
 * Problem: Count right/down paths from top-left to bottom-right that avoid
 *          blocked cells (1 = blocked).
 *
 * Examples:
 *   [[0,0,0],[0,1,0],[0,0,0]]   -> 2
 *   [[0,1],[0,0]]               -> 1
 *   [[1]]                       -> 0  (start blocked)
 *   [[0,0],[0,1]]               -> 0  (end blocked)
 *   [[0],[1],[0]]               -> 0
 *
 * Approaches:
 *   1. Memoized recursion   O(m*n) time, O(m*n) space
 *   2. 2-D table            O(m*n) time, O(m*n) space
 *   3. 1-D rolling row  ⭐   O(m*n) time, O(n) space     <- go-to
 */

#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Memoized Recursion ----------
long long paths(const vector<vector<int>>& g, int r, int c, vector<vector<long long>>& memo) {
    if (r < 0 || c < 0 || g[r][c] == 1) return 0;
    if (r == 0 && c == 0) return 1;
    if (memo[r][c] != -1) return memo[r][c];
    return memo[r][c] = paths(g, r - 1, c, memo) + paths(g, r, c - 1, memo);
}

int uniquePathsWithObstaclesMemo(const vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<long long>> memo(m, vector<long long>(n, -1));
    return (int)paths(g, m - 1, n - 1, memo);
}

// ---------- Approach 2: 2-D Table ----------
int uniquePathsWithObstaclesTable(const vector<vector<int>>& g) {
    int m = g.size(), n = g[0].size();
    vector<vector<long long>> dp(m, vector<long long>(n, 0));
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) {
            if (g[r][c] == 1) continue;                    // blocked stays 0
            if (r == 0 && c == 0) { dp[r][c] = 1; continue; }
            dp[r][c] = (r > 0 ? dp[r - 1][c] : 0) + (c > 0 ? dp[r][c - 1] : 0);
        }
    return (int)dp[m - 1][n - 1];
}

// ---------- Approach 3: 1-D Rolling Row ⭐ ----------
int uniquePathsWithObstacles(const vector<vector<int>>& g) {
    int n = g[0].size();
    vector<long long> row(n, 0);
    row[0] = 1;                                            // a blocked start zeroes it below
    for (auto& cells : g)
        for (int c = 0; c < n; c++) {
            if (cells[c] == 1) row[c] = 0;
            else if (c > 0) row[c] += row[c - 1];          // above + left
        }
    return (int)row[n - 1];
}

// ---------- Driver ----------
int main() {
    vector<vector<vector<int>>> tests = {
        {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}, {{0, 1}, {0, 0}}, {{1}}, {{0, 0}, {0, 1}}, {{0}, {1}, {0}}
    };
    for (auto& g : tests) {
        cout << "memo : " << uniquePathsWithObstaclesMemo(g) << "\n";
        cout << "table: " << uniquePathsWithObstaclesTable(g) << "\n";
        cout << "row  : " << uniquePathsWithObstacles(g) << "\n";
        cout << "---\n";
    }
}

/*
 * Syntax notes (C++):
 * - `for (auto& cells : g)` walks rows by reference, no copy.
 * - (r > 0 ? dp[r-1][c] : 0) reads a neighbour only when it exists.
 * - memo of -1 means "not computed", since 0 is a valid path count.
 */
